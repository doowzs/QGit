/**
 * Class QGit::FS
 * The file system class to read objects from .git folder.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_GITFS_H_
#define QGIT_SRC_GITFS_H_

#include <QtCore>

// see https://git-scm.com/docs/pack-format
#define OBJ_COMMIT 0x1
#define OBJ_TREE 0x2
#define OBJ_BLOB 0x3
#define OBJ_TAG 0x4
#define OBJ_OFS_DELTA 0x6
#define OBJ_REF_DELTA 0x7

namespace QGit {
class FS {
 private:// Members
  const bool debug;
  const QString path;

 public:// Constructors
  FS(bool debug, const QString &path);

 private:// Internal Methods
  QByteArray readDataFromObjectFile(const QString &hash);
  QByteArray readDataFromPackFiles(const QString &hash);
  uint32_t readOffsetFromPackIndexFile(const QString &pack, const QString &hash);
  QByteArray readDataFromPackDataFile(const QString &pack, uint32_t offset);

 public:// Static Interfaces
  static uint32_t convertBytesToLength(const QByteArray &bytes);
  static QByteArray inflateCompressedData(const QByteArray &data, uint32_t size);
  static QByteArray patchDeltifiedData(const QByteArray &base, const QByteArray &delta);

 public:// Interfaces
  QByteArray getObject(const QString &hash);
  QTextStream getStream(const QString &hash);
};
}// namespace QGit

#endif//QGIT_SRC_GITFS_H_
