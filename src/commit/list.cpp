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
  titleLabel->setFont(QFont(nullptr, 25));
  titleLabel->setText("Commits");
  listLayout->addWidget(titleLabel);

  listWidget = new QListWidget(this);
  {
    QString cur = hash;
    while (!cur.isEmpty()) {
      Item *item = new Item(debug, path, cur, listWidget);
      items.push_back(item);
      listWidget->addItem(item);
      cur = item->getParent();
    }
  }
  listLayout->addWidget(listWidget);

  this->setLayout(listLayout);
  this->setMinimumWidth(400);
  this->setFixedHeight(600);
}
