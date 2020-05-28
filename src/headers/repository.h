/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REPOSITORY_H_
#define QGIT_SRC_HEADERS_REPOSITORY_H_

#include <QCloseEvent>
#include <QtCore>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)
QT_FORWARD_DECLARE_CLASS(Snapshot)

namespace Reference {
QT_FORWARD_DECLARE_CLASS(List)
}

namespace Commit {
QT_FORWARD_DECLARE_CLASS(List)
}

class Repository final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  QString root;
  FS *fs;

 private:// Widgets
  QVBoxLayout *repositoryLayout{};
  QLabel *titleLabel{};
  QLabel *helpLabel{};
  QWidget *contentWidget{};
  QHBoxLayout *contentLayout{};
  Reference::List *referenceList{};
  Commit::List *commitList{};
  Snapshot *snapshotWindow{};

 public:// Constructors
  Repository(bool debug, const QString &path, QWidget *parent);
  ~Repository() override;

 public:// Override Methods
  void closeEvent(QCloseEvent *event) override;

 Q_SIGNALS:// Signals
  void repositoryClosed();
};
}// namespace QGit

#endif//QGIT_SRC_HEADERS_REPOSITORY_H_
