/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_COMMIT_DETAIL_H_
#define QGIT_SRC_COMMIT_DETAIL_H_

#include <QtCore>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Tree {
QT_FORWARD_DECLARE_CLASS(List)
}

namespace Commit {
class Detail final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  const QString hash;
  const QString tree;
  const QStringList parents;
  const QString author;
  const QString title;
  const QString message;
  FS *fs;

 private:// Widgets
  QVBoxLayout *detailLayout{};
  QLabel *hashLabel{};
  QLabel *titleLabel{};
  QLabel *messageLabel{};
  QLabel *authorLabel{};
  Tree::List *treeListWidget{};

 public:// Constructors
  Detail(bool debug, const QString &hash, const QString &tree, const QStringList &parents,
         const QString &author, const QString &title, const QString &message, FS *fs, QWidget *parent);
};
}// namespace Commit
}// namespace QGit

#endif//QGIT_SRC_COMMIT_DETAIL_H_
