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

List::List(bool debug, const QString &hash, FS *fs, QWidget *parent) : QWidget(parent),
                                                                       debug(debug) {
  QTextStream stream = fs->getDecompressedStream(hash);
}
