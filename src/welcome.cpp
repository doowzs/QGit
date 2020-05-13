/**
 * Class QGit::Welcome
 * Show welcome message and open a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "welcome.h"
#include "constants.h"
using namespace QGit;

/**
 * Initialize a welcome widget.
 */
Welcome::Welcome(bool debug, QWidget *parent) : QWidget(parent), debug(debug) {
  welcomeLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setAlignment(Qt::AlignCenter);
  titleLabel->setFont(QFont(nullptr, 30));
  titleLabel->setText(Constants::Application::name);
  welcomeLayout->addWidget(titleLabel);

  openButton = new QPushButton(this);
  openButton->setText("打开仓库");
  connect(openButton, SIGNAL(released()), this, SLOT(openRepository()));
  welcomeLayout->addWidget(openButton);

  exitButton = new QPushButton(this);
  exitButton->setText("退出程序");
  connect(exitButton, SIGNAL(released()), this, SLOT(closeApplication()));
  welcomeLayout->addWidget(exitButton);

  versionLabel = new QLabel(this);
  versionLabel->setAlignment(Qt::AlignRight);
  versionLabel->setText("Version " + Constants::Application::version.toString() + ", Qt " + QT_VERSION_STR);
  welcomeLayout->addWidget(versionLabel);

  authorLabel = new QLabel(this);
  authorLabel->setAlignment(Qt::AlignRight);
  authorLabel->setText("(C) " + QString::number(Constants::Application::year) + " " + Constants::Application::author);
  welcomeLayout->addWidget(authorLabel);

  this->parentWidget()->setWindowTitle("欢迎使用");
  this->setLayout(welcomeLayout);
}

/**
 * Slot: when open button is clicked, use a dialog to let user choose a repository.
 * After choosing a repository, check its data and emit signal for root to handle.
 */
void Welcome::openRepository() {
  QString path = QFileDialog::getExistingDirectory(this, "选择仓库目录");
  if (debug) {
    qDebug() << "open directory" << path;
  }
  // TODO: check the folder is a repository
  emit repositoryOpened(path);
}

/**
 * Slot: when exit button is clicked, close the root window and exit.
 */
void Welcome::closeApplication() {
  if (debug) {
    qDebug() << "exited from welcome widget";
  }
  // Exit the application by directly closing the root window.
  this->parentWidget()->close();
}
