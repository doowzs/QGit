/**
 * Class QGit::Reference::Detail
 * Widget of a detailed git reference.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/detail.h"
#include "commit/panel.h"
using namespace QGit;
using namespace QGit::Reference;

/**
 * Initialize a detail widget;
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
Detail::Detail(bool debug, const QString &path, const QString &hash, QWidget *parent)
    : QWidget(parent), debug(debug), path(path), hash(hash) {
  detailLayout = new QHBoxLayout(this);

  commitPanel = new Commit::Panel(debug, path, hash, this);
  detailLayout->addWidget(commitPanel);

  this->setLayout(detailLayout);
}
