/**
 * Class QGit::Tree::Panel
 * Main widget of a git commit's object tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/panel.h"

#include "commit/item.h"
#include "tree/detail.h"
#include "tree/list.h"
#include "tree/item.h"
using namespace QGit;
using namespace QGit::Tree;

/**
 * Initialize a panel of git commit's object tree.
 * @param debug
 * @param hash
 * @param fs
 * @param parent
 */
Panel::Panel(bool debug, FS *fs, QWidget *parent) : QWidget(parent),
                                                    debug(debug),
                                                    fs(fs) {
  panelLayout = new QHBoxLayout(this);
  panelLayout->setContentsMargins(0, 9, 0, 0);

  listWidget = new List(debug, fs, this);
  panelLayout->addWidget(listWidget, 1);

  detailWidget = new Detail(debug, fs, this);
  panelLayout->addWidget(detailWidget, 4);

  connect(listWidget, &List::objectSelected, this, &Panel::objectSelected);

  this->setLayout(panelLayout);
}

/**
 * Slot: When a commit is selected, refresh the panel's content.
 * @param item
 */
void Panel::commitSelected(const Commit::Item *item) {
  listWidget->commitSelected(item);
}

/**
 * Slot: When an object is selected, load its content from blob file.
 * @param item
 */
void Panel::objectSelected(const Item *item) {
  if (item == nullptr) {
    detailWidget->setPlainText(nullptr);
  } else {
    detailWidget->loadBlobContent(item->getMode(), item->getName(), item->getHash());
  }
}
