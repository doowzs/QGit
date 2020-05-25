/**
 * Class QGit::FS
 * The file system class to read objects from .git folder.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "gitfs.h"
using namespace QGit;

/**
 * Initialize a git FS object.
 * @param debug
 * @param path path to .git/object
 */
FS::FS(bool debug, const QString &path) : debug(debug),
                                          path(path) {}

/**
 * Convert a 20-byte array into a QString hash.
 * @param bytes
 * @return
 */
QString FS::convertBytesToHash(const QByteArray &bytes) {
  QString hash = QString();
  for (int i = 0; i < 20; ++i) {
    unsigned char byte = bytes[i];
    unsigned char u = (byte & 0xf0U) >> 4U;
    unsigned char l = byte & 0x0fU;
    hash += (QChar)((u > 0x9 ? 'a' - 0xa : '0') + u);
    hash += (QChar)((l > 0x9 ? 'a' - 0xa : '0') + l);
  }
  return hash;
}

/**
 * Read object data from an object file.
 * @param hash
 * @return object data | []
 */
QByteArray FS::readFromObject(const QString &hash) {
  QFile file = QFile(path + "/" + hash.mid(0, 2) + "/" + hash.mid(2));
  if (file.exists()) {
    try {
      file.open(QFile::ReadOnly);
      QByteArray data = file.readAll();
      file.close();
      return data;
    } catch (const QException &e) {
      return QByteArray();
    }
  } else {
    return QByteArray();
  }
}

/**
 * Read object data from .git/objects/pack folder.
 * @param hash
 * @return object data | []
 */
QByteArray FS::readFromPackFile(const QString &hash) {
  QDir folder = QDir(path + "/pack");
  QStringList packFileList = folder.entryList(QStringList("*.pack"), QDir::Files | QDir::NoDotAndDotDot);
  QByteArray data = QByteArray();
  for (const QString &packFile : packFileList) {
    if (debug) {
      qDebug() << "search object in" << packFile;
    }
    data = readFromSinglePackFile(packFile.mid(0, packFile.length() - 5), hash);
    if (!data.isEmpty()) {
      break;
    }
  }
  return data;
}

/**
 * Read object data from a single packed file.
 * @param pack pack file without suffix
 * @param hash
 * @return object data | []
 */
QByteArray FS::readFromSinglePackFile(const QString &pack, const QString &hash) {
  QFile idxFile = QFile(path + "/pack/" + pack + ".idx");
  QFile pakFile = QFile(path + "/pack/" + pack + ".pack");
  qDebug() << idxFile;
  qDebug() << pakFile;
  if (!idxFile.exists() or !pakFile.exists()) {
    return QByteArray();
  }
  // format of pack files: https://git-scm.com/docs/pack-format
  // find the offset in .idx file, and read data from .pack file.
  QByteArray data = QByteArray();
  idxFile.open(QFile::ReadOnly), pakFile.open(QFile::ReadOnly);

  int l = 0, r = 0; // binary search
  idxFile.seek(1028);
  QDataStream(idxFile.read(4)) >> r;
  while (l < r) {
    int m = (l + r) / 2;
    idxFile.seek(1032 + m * 20);
    QString cur = convertBytesToHash(idxFile.read(20));
    qDebug() << cur;
    if (cur == hash) {
      qDebug() << "found!";
      break;
    } else if (cur < hash) {
      r = m;
    } else {
      l = m + 1;
    }
  }

  idxFile.close(), pakFile.close();
  return data;
}

/**
 * Read object data from .git/objects folder.
 * @param hash
 * @return object data | []
 */
QByteArray FS::getObject(const QString &hash) {
  // object may be stored in object file or pack file.
  // we need to try both cases in order to get object data.
  QByteArray data = readFromObject(hash);
  if (data.isEmpty()) {
    if (debug) {
      qDebug() << "no data in object file";
    }
    data = readFromPackFile(hash);
  }
  return data;
}
