/**
 * Class QGit::Root
 * The root / main window of the application.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "root.h"

#include "repository.h"
#include "welcome.h"
using namespace QGit;

/**
 * Initialize a root / main window with path to git repository.
 * @param debug
 * @param path
 * @param parent
 */
Root::Root(bool debug, const QString &path, QWidget *parent) : QMainWindow(parent),
                                                               debug(debug) {
  QFile recentFile = QFile("recent.json");
  if (recentFile.exists()) {
    recentFile.open(QFile::ReadOnly);
    if (recentFile.isOpen()) {
      QJsonDocument recentDocument = QJsonDocument::fromJson(recentFile.readAll());
      QJsonArray recentArray = recentDocument.array();
      for (auto recentObject : recentArray) {
        recentList.append(recentObject.toString());
      }
      recentFile.close();
    }
  }

  welcomeWidget = new Welcome(debug, recentList, this);
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
void Root::openRepository(const QString &_path) {
  if (debug) {
    qDebug() << "path:" << _path;
  }

  // Bare repository does not have .git folder.
  QString path = _path;
  if (QDir(path + "/.git").exists()) {
    path += "/.git";
  }

  // Check for refs and objects folder, they are important.
  if (QDir(path + "/refs").exists() and QDir(path + "/objects").exists()) {
    if (!recentList.contains(path)) {
      recentList.push_front(path);
    }
    if (recentList.size() > 10) {
      recentList.pop_back();
    }
    QFile recentFile = QFile("recent.json");
    recentFile.open(QFile::WriteOnly);
    if (recentFile.isOpen()) {
      QJsonArray recentArray = QJsonArray::fromStringList(recentList);
      QJsonDocument recentDocument = QJsonDocument(recentArray);
      recentFile.write(recentDocument.toJson());
      recentFile.close();
    }

    repositoryWidget = new Repository(debug, path, this);
    connect(repositoryWidget, &Repository::repositoryClosed, this, &Root::closeRepository);
    repositoryWidget->show();
    welcomeWidget->deleteLater();
    this->hide();
  } else {
    QMessageBox::about(this, "错误", "打开的目录不是Git仓库");
  }
}

/**
 * Slot: if the repository window is closed, open the root window again.
 */
void Root::closeRepository() {
  welcomeWidget = new Welcome(debug, recentList, this);
  connect(welcomeWidget, &Welcome::repositorySelected, this, &Root::openRepository);
  this->setCentralWidget(welcomeWidget);
  this->show();
  repositoryWidget->deleteLater();
}
