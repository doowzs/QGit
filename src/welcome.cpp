/**
 * Class QGit::Welcome
 * Show welcome message and open a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "welcome.h"

#include "IconFontCppHeaders/IconsFontAwesome5.h"
#include "constants.h"
#include <QFontDatabase>
using namespace QGit;

/**
 * Initialize a welcome widget.
 */
Welcome::Welcome(bool debug, const QStringList &recentList, QWidget *parent) : QWidget(parent),
                                                                               debug(debug) {
  welcomeLayout = new QHBoxLayout(this);

  if (!recentList.isEmpty()) {
    recentScrollArea = new QScrollArea(recentWidget);
    recentWidget = new QWidget(this);
    recentLayout = new QVBoxLayout(recentWidget);
    recentLayout->setAlignment(Qt::AlignTop);

    QFont fileFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fileFont.setPointSize(12);
    for (const QString &recent : recentList) {
      auto recentItem = new QPushButton(recentWidget);
      auto recentItemLayout = new QVBoxLayout(recentItem);

      auto recentNameLabel = new QLabel(recentItem);
      recentNameLabel->setText(recent.mid(recent.lastIndexOf("/")));
      recentItemLayout->addWidget(recentNameLabel);

      auto recentFileLabel = new QLabel(recentItem);
      recentFileLabel->setFont(fileFont);
      recentFileLabel->setText(recent);
      recentItemLayout->addWidget(recentFileLabel);

      recentItem->setLayout(recentItemLayout);
      recentLayout->addWidget(recentItem);
      recentItems.push_back(recentItem);
    }

    recentWidget->setLayout(recentLayout);
    recentWidget->setMinimumWidth(150);
    recentWidget->setMinimumHeight(200);
    recentScrollArea->setWidget(recentWidget);
    welcomeLayout->addWidget(recentScrollArea, 3);
  }

  {
    menuWidget = new QWidget(this);
    menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->addWidget(new QWidget(menuWidget), 1);

    iconLabel = new QLabel(menuWidget);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setFont(QFont(FONT_ICON_FAMILY, 50, QFont::Thin));
    iconLabel->setText(ICON_FA_LAPTOP_CODE);
    menuLayout->addWidget(iconLabel);

    titleLabel = new QLabel(menuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont(nullptr, 30));
    titleLabel->setText(Constants::Application::name);
    menuLayout->addWidget(titleLabel);
    menuLayout->addWidget(new QWidget(menuWidget), 1);

    openButton = new QPushButton(menuWidget);
    openButton->setFont(QFont(FONT_ICON_FAMILY));
    openButton->setText(QString(ICON_FA_FOLDER_OPEN) + QString(" 打开仓库"));
    connect(openButton, &QPushButton::released, this, &Welcome::selectRepository);
    menuLayout->addWidget(openButton);

    exitButton = new QPushButton(menuWidget);
    exitButton->setFont(QFont(FONT_ICON_FAMILY));
    exitButton->setText(QString(ICON_FA_DOOR_OPEN) + QString(" 退出程序"));
    connect(exitButton, &QPushButton::released, this, &Welcome::closeApplication);
    menuLayout->addWidget(exitButton);
    menuLayout->addWidget(new QWidget(menuWidget), 1);

    versionLabel = new QLabel(menuWidget);
    versionLabel->setAlignment(Qt::AlignRight);
    versionLabel->setText("Version " + Constants::Application::version.toString() + ", Qt " + QT_VERSION_STR);
    menuLayout->addWidget(versionLabel);

    authorLabel = new QLabel(menuWidget);
    authorLabel->setAlignment(Qt::AlignRight);
    authorLabel->setText("(C) " + QString::number(Constants::Application::year) + " " + Constants::Application::author);
    menuLayout->addWidget(authorLabel);

    menuWidget->setLayout(menuLayout);
    welcomeLayout->addWidget(menuWidget, 2);
  }

  this->parentWidget()->setWindowTitle("欢迎使用");
  this->setLayout(welcomeLayout);
}

/**
 * Slot: when open button is clicked, use a dialog to let user select a repository.
 * After choosing a repository, emit signal for root to handle the selected path.
 */
void Welcome::selectRepository() {
  QString path = QFileDialog::getExistingDirectory(this, "选择仓库目录");
  if (!path.isEmpty()) {
    emit repositorySelected(path);
  }
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
