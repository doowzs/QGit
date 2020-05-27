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

namespace QGit::Commit {
QT_FORWARD_DECLARE_CLASS(Item)

class Detail final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;

 private:// Widgets
  QVBoxLayout *detailLayout{};
  QLabel *hashLabel{};
  QLabel *titleLabel{};
  QLabel *messageLabel{};
  QLabel *authorLabel{};

 public:// Constructors
  Detail(bool debug, QWidget *parent);

 public Q_SLOTS:// Slots
  void loadCommit(const Item *item);
};
}// namespace QGit::Commit

#endif//QGIT_SRC_COMMIT_DETAIL_H_
