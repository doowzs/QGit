/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_COMMIT_DETAIL_H_
#define QGIT_SRC_COMMIT_DETAIL_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

namespace QGit::Commit {
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

 private:// Widgets
  QVBoxLayout *detailLayout{};
  QLabel *hashLabel{};

 public:// Constructors
  Detail(bool debug, const QString &hash, const QString &tree, const QStringList &parents,
         const QString &author, const QString &title, const QString &message, QWidget *parent);
};
}// namespace QGit::Commit

#endif//QGIT_SRC_COMMIT_DETAIL_H_
