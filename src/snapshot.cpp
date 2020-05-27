/**
 * Class QGit::Snapshot
 * The root widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "snapshot.h"

#include "commit/detail.h"
#include "commit/item.h"
#include "gitfs.h"
#include "tree/panel.h"
using namespace QGit;

/**
 * Initialize a snapshot window.
 * @param debug
 * @param fs
 * @param parent
 */
Snapshot::Snapshot(bool debug, FS *fs, QWidget *parent) : QWidget(parent, Qt::Window),
                                                          debug(debug),
                                                          fs(fs) {
  snapshotLayout = new QVBoxLayout(this);

  commitDetailWidget = new Commit::Detail(debug, this);
  snapshotLayout->addWidget(commitDetailWidget);

  treePanelWidget = new Tree::Panel(debug, fs, this);
  snapshotLayout->addWidget(treePanelWidget);

  this->setWindowTitle("提交详情");
  this->setLayout(snapshotLayout);
}

/**
 * Load and show contents of a git commit.
 * @param item
 */
void Snapshot::loadCommit(const Commit::Item *item) {
  commitDetailWidget->loadCommit(item);
  treePanelWidget->commitSelected(item);
}
