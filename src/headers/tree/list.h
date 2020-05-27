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

namespace Commit {
QT_FORWARD_DECLARE_CLASS(Item)
}

namespace Tree {
QT_FORWARD_DECLARE_CLASS(Item)

class List final : public QListWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  QString commit;
  QString current;
  QStack<QString> parents;
  QVector<QListWidgetItem *> items;
  FS *fs;

 private:// Widgets
  QListWidgetItem *goBackItem{};

 public:// Constructors
  List(bool debug, FS *fs, QWidget *parent);

 private:// Methods
  void loadCurrentTree();

 public Q_SLOTS:// Slots
  void commitSelected(const Commit::Item *item);

 Q_SIGNALS:// Signals
  void objectSelected(const Item *item);
};
}// namespace Tree
}// namespace QGit

#endif//QGIT_SRC_HEADERS_TREE_LIST_H_
