/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "repository.h"

#include "commit/item.h"
#include "commit/list.h"
#include "gitfs.h"
#include "reference/list.h"
#include "snapshot.h"
#include "IconFontCppHeaders/IconsFontAwesome5.h"
using namespace QGit;

/**
 * Initialize a repository widget.
 * @param debug
 * @param path
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent, Qt::Window),
      debug(debug),
      root(path),
      fs(new FS(debug, path)) {
  repositoryLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setTextFormat(Qt::RichText);
  titleLabel->setFont(QFont(FONT_ICON_FAMILY));
  titleLabel->setText(QString(ICON_FA_FOLDER) + "&nbsp;当前仓库： <code>" + path + "</code>");
  repositoryLayout->addWidget(titleLabel);

  helpLabel = new QLabel(this);
  helpLabel->setTextFormat(Qt::RichText);
  helpLabel->setFont(QFont(FONT_ICON_FAMILY));
  helpLabel->setText(QString(ICON_FA_INFO_CIRCLE) + "&nbsp;双击左侧项目选择分支，双击右侧项目选择提交查看快照。");
  repositoryLayout->addWidget(helpLabel);

  {
    contentWidget = new QWidget(this);
    contentLayout = new QHBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 9, 0, 0);

    referenceList = new Reference::List(debug, path, this);
    contentLayout->addWidget(referenceList);

    commitList = new Commit::List(debug, fs, this);
    contentLayout->addWidget(commitList);

    snapshotWindow = new Snapshot(debug, fs, this);
    connect(referenceList, &Reference::List::referenceSelected, this,
            [&](const QString &name, const QString &hash) -> void {
              commitList->loadCommits(hash);
            });
    connect(commitList, &Commit::List::commitSelected, this,
            [&](const Commit::Item *item) -> void {
              snapshotWindow->loadCommit(item);
              snapshotWindow->show();
            });

    contentWidget->setLayout(contentLayout);
    repositoryLayout->addWidget(contentWidget);
  }

  this->setWindowTitle("提交记录");
  this->setLayout(repositoryLayout);
}

/**
 * Destroy the repository widget and its fs member.
 */
Repository::~Repository() {
  delete this->fs;
}

void Repository::closeEvent(QCloseEvent *event) {
  event->ignore();
  emit repositoryClosed();
}
