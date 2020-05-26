/**
 * Class QGit::Tree::Panel
 * Main widget of a commit's object tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/panel.h"
#include "tree/list.h"
#include "tree/detail.h"
using namespace QGit::Tree;

Panel::Panel(bool debug, const QString &hash, FS *fs, QWidget *parent) : QWidget(parent),
                                                                         debug(debug),
                                                                         hash(hash),
                                                                         fs(fs) {
  panelLayout = new QHBoxLayout(this);

  listWidget = new List(debug, hash, fs, this);
  panelLayout->addWidget(listWidget);

  detailWidget = new Detail(debug, fs, this);
  panelLayout->addWidget(detailWidget);

  this->setLayout(panelLayout);
}