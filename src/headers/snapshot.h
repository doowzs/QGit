/**
 * Class QGit::Snapshot
 * The root widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_SNAPSHOT_H_
#define QGIT_SRC_HEADERS_SNAPSHOT_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Commit {
QT_FORWARD_DECLARE_CLASS(Item)
QT_FORWARD_DECLARE_CLASS(Detail)
}

namespace Tree {
QT_FORWARD_DECLARE_CLASS(Panel)
}

class Snapshot final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  FS *fs;

 private: // Widgets
  QVBoxLayout *snapshotLayout{};
  Commit::Detail *commitDetailWidget{};
  Tree::Panel *treePanelWidget{};

 public:// Constructors
  Snapshot(bool debug, FS *fs, QWidget *parent);

 public Q_SLOTS: // Slots
  void loadCommit(const Commit::Item *item);
};
}// namespace QGit

#endif//QGIT_SRC_HEADERS_SNAPSHOT_H_
