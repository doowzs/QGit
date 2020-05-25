/**
 * Class QGit::Commit::List
 * Widget of a list of git commits.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_COMMIT_LIST_H_
#define QGIT_SRC_HEADERS_COMMIT_LIST_H_

#include <QtCore>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Commit {
QT_FORWARD_DECLARE_CLASS(Item)

class List final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  const QString path;
  const QString hash;
  QVector<Item *> items;
  FS *fs{};

 private:// Widgets
  QVBoxLayout *listLayout{};
  QLabel *titleLabel{};
  QListWidget *listWidget{};

 public:// Constructors
  List(bool debug, const QString &path, const QString &hash, FS *fs, QWidget *parent);
};
}// namespace Commit
}// namespace QGit

#endif//QGIT_SRC_HEADERS_COMMIT_LIST_H_
