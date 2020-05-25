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
  QString convertBytesToHash(const QByteArray &bytes);
  QByteArray readFromObject(const QString &hash);
  QByteArray readFromPackFile(const QString &hash);
  QByteArray readFromSinglePackFile(const QString &pack, const QString &hash);

 public: // Interfaces
  QByteArray getObject(const QString &hash);
};
}

#endif//QGIT_SRC_GITFS_H_
