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
 * Read object data from an object file.
 * @param hash
 * @return object data | []
 */
QByteArray FS::readDataFromObjectFile(const QString &hash) {
  QFile file = QFile(path + "/objects/" + hash.mid(0, 2) + "/" + hash.mid(2));
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
QByteArray FS::readDataFromPackFiles(const QString &hash) {
  QDir folder = QDir(path + "/objects/pack");
  QStringList packFileList = folder.entryList(QStringList("*.pack"), QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &packFile : packFileList) {
    QString pack = packFile.mid(0, packFile.length() - 5);
    uint32_t offset = readOffsetFromPackIndexFile(pack, hash);
    if (offset != 0U) {
      QByteArray data = readDataFromPackDataFile(pack, offset);
      if (!data.isEmpty()) {
        return data;
      }
    }
  }
  return QByteArray();
}


/**
 * Read object offset from a packed index file (v2).
 * Format of pack files: https://git-scm.com/docs/pack-format
 * @param pack file without suffix
 * @param hash
 * @return offset | 0
 */
uint32_t FS::readOffsetFromPackIndexFile(const QString &pack, const QString &hash) {
  QFile file = QFile(path + "/objects/pack/" + pack + ".idx");
  if (!file.exists()) {
    return 0;
  }
  file.open(QFile::ReadOnly);

  int l = 0, r = 0, nr = 0;// binary search
  uint32_t offset = 0U;    // offset of data in pack file
  file.seek(1028);
  QDataStream(file.read(4)) >> nr, r = nr - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    file.seek(1032 + m * 20);
    QString cur = convertBytesToHash(file.read(20));
    if (cur == hash) {
      file.seek(1032 + nr * 24 + m * 4);
      QDataStream(file.read(4)) >> offset;
      break;
    } else if (cur < hash) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  file.close();
  return 0U;
}

/**
 * Read object data from a packed data file.
 * Format of pack files: https://git-scm.com/docs/pack-format
 * @param pack file without suffix
 * @param hash
 * @return object data | []
 */
QByteArray FS::readDataFromPackDataFile(const QString &pack, uint32_t offset) {
  QFile file = QFile(path + "/objects/pack/" + pack + ".pack");
  QByteArray data = QByteArray();

  if (offset != 0U) {
    file.seek(offset);
    QByteArray lengthBytes = QByteArray();
    QByteArray buffer = QByteArray();
    do {
      buffer = file.read(1);
      lengthBytes.push_back(buffer);
    } while ((uint32_t) buffer[0] & 0x8000U);
    uint32_t size = convertBytesToLength(lengthBytes);
    data = file.read(size);
  }

  file.close();
  return data;
}

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
 * Read object data from .git/objects folder.
 * @param hash
 * @return object data | []
 */
QByteArray FS::getObject(const QString &hash) {
  // object may be stored in object file or pack file.
  // we need to try both cases in order to get object data.
  QByteArray data = readDataFromObjectFile(hash);
  if (data.isEmpty()) {
    data = readDataFromPackFiles(hash);
  }
  if (data.isEmpty()) {
    qDebug() << "object" << hash << "not found";
  }
  return data;
}

/**
 * Get decompressed data from a git object.
 * @param hash
 * @return decompressed data | []
 */
QByteArray FS::getDecompressedObject(const QString &hash) {
  QByteArray compressedData = getObject(hash);
  if (compressedData.isEmpty()) {
    return QByteArray();
  }

  // inflate commit data with zlib
  uLong uncompressedLength = 4096;
  QByteArray uncompressedData = QByteArray(uncompressedLength, ' ');
  while (true) {
    int result = uncompress((Bytef *) uncompressedData.data(),
                            &uncompressedLength,
                            (const Bytef *) compressedData.constData(),
                            (uLong) compressedData.length() + 1);
    if (result == Z_OK) {
      break;// uncompress OK
    } else if (result == Z_BUF_ERROR) {
      // buffer is not large enough
      uncompressedLength *= 2;
      uncompressedData = QByteArray(uncompressedLength, ' ');
    } else {
      // fatal error occurred, abort the program
      qDebug() << "uncompress failed with code" << result;
      return QByteArray();
    }
  }
  return uncompressedData.trimmed();
}

/**
 * Get a text stream from zlib compressed object.
 * @param hash
 * @return text stream
 */
QTextStream FS::getDecompressedStream(const QString &hash) {
  QByteArray data = getDecompressedObject(hash);
  for (int pos = 0; pos < data.length(); ++pos) {
    if (data.data()[pos] == '\0') {
      data.data()[pos] = '\n';// replace the first '\0' with '\n'
      break;
    }
  }
  return QTextStream(data, QIODevice::ReadOnly);
}
