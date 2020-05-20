/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "repository.h"
#include "reference/panel.h"
using namespace QGit;

/**
 * Initialize a repository widget.
 * @param debug
 * @param path
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent), debug(debug), root(path) {
  repositoryLayout = new QHBoxLayout(this);

  referencePanel = new Reference::Panel(debug, path, this);
  repositoryLayout->addWidget(referencePanel);

  this->setLayout(repositoryLayout);
}
