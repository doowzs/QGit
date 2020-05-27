/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REPOSITORY_H_
#define QGIT_SRC_HEADERS_REPOSITORY_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Reference {
QT_FORWARD_DECLARE_CLASS(List)
}

namespace Commit {
QT_FORWARD_DECLARE_CLASS(List)
}

class Repository final : public QWidget {
 Q_OBJECT

 private: // Members
  const bool debug;
  QString root;
  FS *fs;

 private: // Widgets
  QHBoxLayout *repositoryLayout{};
  Reference::List *referenceList{};
  Commit::List *commitList{};

 public: // Constructors
  Repository(bool debug, const QString &path, QWidget *parent);
  ~Repository() override;
};
}

#endif //QGIT_SRC_HEADERS_REPOSITORY_H_
