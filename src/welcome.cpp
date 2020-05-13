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
  welcomeLayout->addWidget(openButton);

  exitButton = new QPushButton(this);
  exitButton->setText("退出程序");
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
