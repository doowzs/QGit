/**
 * Class QGit::Commit::List
 * Widget of a list of git commits.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/list.h"

#include "commit/item.h"
#include "gitfs.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a list widget.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
List::List(bool debug, const QString &path, const QString &hash, FS *fs, QWidget *parent)
    : QWidget(parent),
      debug(debug),
      path(path),
      hash(hash),
      fs(fs) {
  listLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setFont(QFont(nullptr, 25));
  titleLabel->setText("Commits");
  listLayout->addWidget(titleLabel);

  listWidget = new QListWidget(this);
  QStringList hashList = QStringList(hash);
  while (!hashList.isEmpty()) {
    QString cur = hashList.takeFirst();
    Item *item = new Item(debug, path, cur, fs, listWidget);
    items.push_back(item);
    listWidget->addItem(item);
    hashList += item->getParents();
  }
  listLayout->addWidget(listWidget);

  this->setLayout(listLayout);
  this->setMinimumWidth(400);
  this->setFixedHeight(600);
}
