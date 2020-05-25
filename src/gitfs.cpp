/**
 * Class QGit::FS
 * The file system class to read objects from .git folder.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "gitfs.h"

#include <zlib.h>
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
    uint32_t byte = bytes[i];
    uint32_t hi = (byte & 0xf0U) >> 4U;
    uint32_t lo = byte & 0x0fU;
    hash += (QChar)((hi > 0x9 ? 'a' - 0xa : '0') + hi);
    hash += (QChar)((lo > 0x9 ? 'a' - 0xa : '0') + lo);
  }
  return hash;
}

/**
 * Convert a N-byte array into a length integer.
 * @param bytes
 * @return unsigned int of length
 */
uint32_t FS::convertBytesToLength(const QByteArray &bytes) {
  auto length = (uint32_t) bytes[0] & 0x0fU;
  for (int i = 1; i < bytes.length(); ++i) {
    length |= ((uint32_t) bytes[i] & 0x7fU) << (7U * i - 3U);
  }
  return compressBound(length);// bytes in file is size before compress
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
  if (!idxFile.exists() or !pakFile.exists()) {
    return QByteArray();
  }
  // format of pack files: https://git-scm.com/docs/pack-format
  // find the offset in .idx file, and read data from .pack file.
  QByteArray data = QByteArray();
  idxFile.open(QFile::ReadOnly), pakFile.open(QFile::ReadOnly);

  int l = 0, r = 0, nr = 0;// binary search
  uint32_t offset = 0U;    // offset of data in pack file
  idxFile.seek(1028);
  QDataStream(idxFile.read(4)) >> nr, r = nr - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    idxFile.seek(1032 + m * 20);
    QString cur = convertBytesToHash(idxFile.read(20));
    if (cur == hash) {
      idxFile.seek(1032 + nr * 24 + m * 4);
      offset = 0x0c; /* IDE cannot analyze the next line */
      QDataStream(idxFile.read(4)) >> offset;
      break;
    } else if (cur < hash) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  if (offset != 0U) {
    pakFile.seek(offset);
    QByteArray lengthBytes = QByteArray();
    QByteArray buffer = QByteArray();
    do {
      buffer = pakFile.read(1);
      lengthBytes.push_back(buffer);
    } while ((uint32_t) buffer[0] & 0x8000U);
    uint32_t size = convertBytesToLength(lengthBytes);
    data = pakFile.read(size);
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
    data = readFromPackFile(hash);
  }
  if (data.isEmpty()) {
    qDebug() << "object" << hash << "not found";
  }
  return data;
}
