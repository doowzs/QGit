/**
 * Class QGit::FS
 * The file system class to read objects from .git folder.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_GITFS_H_
#define QGIT_SRC_GITFS_H_

#include <QtCore>

namespace QGit {
class FS {
 private: // Members
  const bool debug;
  const QString path;

 public: // Constructors
  FS(bool debug, const QString &path);

 private: // Internal Methods
  QByteArray readFromObject(const QString &hash);
  QByteArray readFromPackFile(const QString &hash);
  QByteArray readFromSinglePackFile(const QString &pack, const QString &hash);

 public: // Static Interfaces
  static QString convertBytesToHash(const QByteArray &bytes);
  static uint32_t convertBytesToLength(const QByteArray &bytes);

 public: // Interfaces
  QByteArray getObject(const QString &hash);
  QByteArray getDecompressedObject(const QString &hash);
  QTextStream getDecompressedStream(const QString &hash);
};
}

#endif//QGIT_SRC_GITFS_H_
