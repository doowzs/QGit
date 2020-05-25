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
  QTextStream stream = fs->getDecompressedStream(root);

  stream.readLine(); // skip first line: TREE SIZE \0
  while (!stream.atEnd()) {
    QChar temp;
    QByteArray bytes;
    QString mode, name, hash;
    stream >> mode;
    do {
      stream >> temp;
      if (temp != '\0') {
        name += temp;
      }
    } while (temp != '\0');
    for (int i = 0; i < 20; ++i) {
      stream >> temp;
      bytes.append(temp);
    }
    hash = FS::convertBytesToHash(bytes);
    qDebug() << mode << name << hash;
  }
}
