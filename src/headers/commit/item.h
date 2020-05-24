/**
 * Class QGit::Commit::Item
 * Widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_COMMIT_ITEM_H_
#define QGIT_SRC_HEADERS_COMMIT_ITEM_H_

#include <QtCore>
#include <QtWidgets/QListWidgetItem>

namespace QGit::Commit {
class Item final : public QListWidgetItem {
 private: // Members
  const bool debug;
  QString hash;
  QString parent;
  QString commit;
  QString author;
  QString committer;
  QString title;
  QString message;

 public: // Constructors
  Item(bool debug, const QString &path, const QString &hash, QListWidget *list);

 public: // Interfaces
  QString getParent() const;
};
}

#endif //QGIT_SRC_HEADERS_COMMIT_ITEM_H_
