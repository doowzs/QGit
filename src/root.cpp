/**
 * Class QGit::Root
 * The root / main window of the application.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "root.h"
#include "welcome.h"
using namespace QGit;

/**
 * Initialize a root / main window with path to git repository.
 */
Root::Root(bool debug, const QString &path, QWidget *parent) : QMainWindow(parent), debug(debug) {
  welcomeWidget = new Welcome(debug, this);
  connect(welcomeWidget, &Welcome::repositorySelected, this, &Root::openRepository);

  if (path.isEmpty()) {
    this->setCentralWidget(welcomeWidget);
  } else {
    this->openRepository(path);
  }
}

/**
 * Slot: a repository is selected, check the path is a git directory or not.
 * If the directory is a git repository, then open it using a Repository widget.
 */
void Root::openRepository(const QString &path) {
  if (debug) {
    qDebug() << "path:" << path;
  }
  if (QDir(path + "/.git").exists()) {
    // TODO: open the repository.
  } else {
    if (debug) {
      qDebug() << "error:" << path << "does not contain .git folder";
    }
    QMessageBox::about(this, "错误", "打开的目录不是Git仓库");
    this->setCentralWidget(welcomeWidget);
  }
}
