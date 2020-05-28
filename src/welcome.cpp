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
Welcome::Welcome(bool debug, const QStringList &recentList, QWidget *parent) : QWidget(parent),
                                                                               debug(debug) {
  welcomeLayout = new QHBoxLayout(this);

  {
    recentWidget = new QWidget(this);
    recentLayout = new QVBoxLayout(recentWidget);

    recentListWidget = new QListWidget(recentWidget);
    for (const QString &recent : recentList) {
      auto *item = new QListWidgetItem(recent);
      item->setText(recent);
      recentListWidget->addItem(recent);
    }
    connect(recentListWidget, &QListWidget::itemDoubleClicked, this,
            [&](QListWidgetItem *item) -> void {
              emit repositorySelected(item->text());
            });
    recentListWidget->setMinimumWidth(150);
    recentListWidget->setMinimumHeight(200);
    recentLayout->addWidget(recentListWidget);

    recentWidget->setLayout(recentLayout);
    welcomeLayout->addWidget(recentWidget);
  }

  {
    menuWidget = new QWidget(this);
    menuLayout = new QVBoxLayout(menuWidget);

    titleLabel = new QLabel(menuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont(nullptr, 30));
    titleLabel->setText(Constants::Application::name);
    menuLayout->addWidget(titleLabel);

    openButton = new QPushButton(menuWidget);
    openButton->setText("打开仓库");
    connect(openButton, &QPushButton::released, this, &Welcome::selectRepository);
    menuLayout->addWidget(openButton);

    exitButton = new QPushButton(menuWidget);
    exitButton->setText("退出程序");
    connect(exitButton, &QPushButton::released, this, &Welcome::closeApplication);
    menuLayout->addWidget(exitButton);

    versionLabel = new QLabel(menuWidget);
    versionLabel->setAlignment(Qt::AlignRight);
    versionLabel->setText("Version " + Constants::Application::version.toString() + ", Qt " + QT_VERSION_STR);
    menuLayout->addWidget(versionLabel);

    authorLabel = new QLabel(menuWidget);
    authorLabel->setAlignment(Qt::AlignRight);
    authorLabel->setText("(C) " + QString::number(Constants::Application::year) + " " + Constants::Application::author);
    menuLayout->addWidget(authorLabel);

    menuWidget->setLayout(menuLayout);
    welcomeLayout->addWidget(menuWidget);
  }

  this->parentWidget()->setWindowTitle("欢迎使用");
  this->setLayout(welcomeLayout);
}

/**
 * Slot: when open button is clicked, use a dialog to let user select a repository.
 * After choosing a repository, emit signal for root to handle the selected path.
 */
void Welcome::selectRepository() {
  emit repositorySelected(QFileDialog::getExistingDirectory(this, "选择仓库目录"));
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
