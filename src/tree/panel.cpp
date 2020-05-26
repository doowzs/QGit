/**
 * Class QGit::Tree::Panel
 * Main widget of a git commit's object tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/panel.h"
#include "tree/list.h"
#include "tree/detail.h"
using namespace QGit::Tree;

/**
 * Initialize a panel of git commit's object tree.
 * @param debug
 * @param hash
 * @param fs
 * @param parent
 */
Panel::Panel(bool debug, const QString &root, FS *fs, QWidget *parent) : QWidget(parent),
                                                                         debug(debug),
                                                                         root(root),
                                                                         fs(fs) {
  panelLayout = new QHBoxLayout(this);
  panelLayout->setContentsMargins(0, 9, 0, 0);

  listWidget = new List(debug, root, fs, this);
  panelLayout->addWidget(listWidget, 1);

  detailWidget = new Detail(debug, fs, this);
  panelLayout->addWidget(detailWidget, 4);

  connect(listWidget, &List::objectSelected, this, &Panel::objectSelected);

  this->setLayout(panelLayout);
}

/**
 * Slot: When an object is selected, load its content from blob file.
 * @param mode
 * @param name
 * @param hash
 */
void Panel::objectSelected(uint32_t mode, const QString &name, const QString &hash) {
  detailWidget->loadBlobContent(mode, name, hash);
}
