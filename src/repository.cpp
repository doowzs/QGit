/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "repository.h"
#include "reference/list.h"
using namespace QGit;

/**
 * Initialize a repository widget.
 * @param debug
 * @param path
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent), debug(debug), root(path + "/.git") {
  repositoryLayout = new QHBoxLayout(this);

  referenceListWidget = new Reference::List(debug, root + "/refs/heads", this);
  repositoryLayout->addWidget(referenceListWidget);

  this->setLayout(repositoryLayout);
}
