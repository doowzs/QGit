/**
 * Class QGit::Commit::List
 * Widget of a list of git commits.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_COMMIT_LIST_H_
#define QGIT_SRC_HEADERS_COMMIT_LIST_H_

#include <QtCore>
#include <QtWidgets/QListWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Commit {
QT_FORWARD_DECLARE_CLASS(Item)

class List final : public QListWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  FS *fs{};
  QVector<Item *> items;

 public:// Constructors
  List(bool debug, FS *fs, QWidget *parent);

 public Q_SLOTS: // Interfaces
  void loadCommits(const QString &hash);

 Q_SIGNALS:// Signals
  void commitSelected(const Item *item);
};
}// namespace Commit
}// namespace QGit

#endif//QGIT_SRC_HEADERS_COMMIT_LIST_H_
