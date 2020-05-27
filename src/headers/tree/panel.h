/**
 * Class QGit::Tree::Panel
 * Main widget of a commit's object tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_TREE_PANEL_H_
#define QGIT_SRC_HEADERS_TREE_PANEL_H_

#include <QtCore>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Commit {
QT_FORWARD_DECLARE_CLASS(Item)
}

namespace Tree {
QT_FORWARD_DECLARE_CLASS(List)
QT_FORWARD_DECLARE_CLASS(Detail)
QT_FORWARD_DECLARE_CLASS(Item)

class Panel final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  FS *fs;

 private:// Widgets
  QHBoxLayout *panelLayout{};
  List *listWidget{};
  Detail *detailWidget{};

 public:// Constructors
  Panel(bool debug, FS *fs, QWidget *parent);

 public Q_SLOTS:// Public Slots
  void commitSelected(const Commit::Item *item);

 private Q_SLOTS:// Private Slots
  void objectSelected(const Item *item);
};
}// namespace Tree
}// namespace QGit

#endif//QGIT_SRC_HEADERS_TREE_PANEL_H_
