/**
 * Class QGit::Commit::List
 * Widget of a list of git commits.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/list.h"
#include "commit/item.h"
using namespace QGit::Commit;

/**
 * Initialize a list widget.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
List::List(bool debug, const QString &path, const QString &hash, QWidget *parent)
    : QWidget(parent), debug(debug), path(path), hash(hash) {
  listLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setText("Commits");
  listLayout->addWidget(titleLabel);

  listWidget = new QListWidget(this);
  Item *item = new Item(debug, path, hash, listWidget);
  items.push_back(item);
  listWidget->addItem(item);
  listLayout->addWidget(listWidget);

  this->setLayout(listLayout);
}
