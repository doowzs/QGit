/**
 * Class QGit::Commit::List
 * Widget of a list of git commits.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/list.h"

#include <QFontDatabase>

#include "commit/item.h"
#include "gitfs.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a list widget.
 * @param debug
 * @param fs
 * @param parent
 */
List::List(bool debug, FS *fs, QWidget *parent)
    : QListWidget(parent),
      debug(debug),
      fs(fs) {
  QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  font.setPointSize(12);
  this->setFont(font);
  this->setMinimumWidth(400);
  this->setFixedHeight(600);

  connect(this, &QListWidget::itemDoubleClicked, this, [&](QListWidgetItem *_item) -> void {
    emit commitSelected(dynamic_cast<const Item *>(_item));
  });
}

void List::loadCommits(const QString &hash) {
  for (Item *item : items) {
    this->removeItemWidget(item);
  }
  qDeleteAll(items);
  items.clear();

  QStringList hashList = QStringList(hash);
  while (!hashList.isEmpty()) {
    QString cur = hashList.takeFirst();
    if (!cur.isEmpty()) {
      Item *item = new Item(debug, cur, fs, this);
      items.push_back(item);
      this->addItem(item);
      hashList += item->getParents();
    }
  }
}
