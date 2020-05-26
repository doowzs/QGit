/**
 * Class QGit::Tree::List
 * Widget of a list of tree objects.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_TREE_LIST_H_
#define QGIT_SRC_HEADERS_TREE_LIST_H_

#include <QtCore>
#include <QtWidgets/QListWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Tree {
class List final : public QListWidget {
  Q_OBJECT

 private:// Members
  const bool debug;

 public:// Constructors
  List(bool debug, const QString &root, FS *fs, QWidget *parent);
};
}// namespace Tree
}// namespace QGit

#endif//QGIT_SRC_HEADERS_TREE_LIST_H_
