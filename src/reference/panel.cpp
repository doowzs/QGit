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
  connect(listWidget, &List::referenceSelected, this, &Panel::referenceSelected);
  panelLayout->addWidget(listWidget);

  this->setLayout(panelLayout);
}

/**
 * Generate a detail widget when a git reference is selected.
 * @param hash
 */
void Panel::referenceSelected(const QString &name, const QString &hash) {
  if (detailWidget != nullptr) {
    panelLayout->removeWidget(detailWidget);
    detailWidget->deleteLater();
  }
  if (debug) {
    qDebug() << "selected ref:" << name;
    qDebug() << "ref's hash:" << hash;
  }
  detailWidget = new Detail(debug, path, hash, this);
  panelLayout->addWidget(detailWidget);
}
