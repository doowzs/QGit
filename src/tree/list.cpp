/**
 * Class QGit::Tree::List
 * Widget of a list of tree objects.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/list.h"

#include "gitfs.h"
using namespace QGit;
using namespace QGit::Tree;

List::List(bool debug, const QString &root, FS *fs, QWidget *parent) : QWidget(parent),
                                                                       debug(debug) {
  if (debug) {
    qDebug() << "tree root:" << root;
  }
  QByteArray data = fs->getDecompressedObject(root);
  auto byte = data.constBegin() + data.indexOf('\0') + 1;
  while (byte < data.constEnd() - 20) {
    QString mode, name, hash;
    QByteArray hashBytes;
    while (*byte != ' ') {
      mode += *(byte++);
    }
    ++byte; // skip the space between MODE and NAME
    while (*byte != '\0') {
      name += *(byte++);
    }
    ++ byte; // skip the null between NAME and HASH
    for (int i = 0; i < 20; ++i) {
      hashBytes += *(byte++);
    }
    hash = FS::convertBytesToHash(hashBytes);
    qDebug() << mode << name << hash;
  }
}
