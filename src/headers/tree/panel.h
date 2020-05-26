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

namespace Tree {
QT_FORWARD_DECLARE_CLASS(List)
QT_FORWARD_DECLARE_CLASS(Detail)

class Panel final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  const QString root;
  FS *fs;

 private:// Widgets
  QHBoxLayout *panelLayout{};
  List *listWidget{};
  Detail *detailWidget{};

 public:// Constructors
  Panel(bool debug, const QString &root, FS *fs, QWidget *parent);

 private Q_SLOTS:// Slots
  void objectSelected(uint32_t mode, const QString &name, const QString &hash);
};
}// namespace Tree
}// namespace QGit

#endif//QGIT_SRC_HEADERS_TREE_PANEL_H_
