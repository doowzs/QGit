/**
 * Class QGit::Reference::Panel
 * Main widget of the repository's references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/panel.h"
#include "reference/list.h"
#include "reference/detail.h"
using namespace QGit::Reference;

Panel::Panel(bool debug, const QString &path, QWidget *parent) : QWidget(parent), debug(debug), path(path) {
  panelLayout = new QHBoxLayout(this);

  listWidget = new List(debug, path + "/.git/refs", this);
  panelLayout->addWidget(listWidget);

  this->setLayout(panelLayout);
}
