/**
 * Class QGit::Tree::List
 * Widget of a list of tree objects.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/list.h"

#include <QFontDatabase>

#include "gitfs.h"
#include "tree/item.h"
using namespace QGit;
using namespace QGit::Tree;

/**
 * Initialize a list blob object in a git tree.
 * @param debug
 * @param root
 * @param fs
 * @param parent
 */
List::List(bool debug, const QString &root, FS *fs, QWidget *parent) : QListWidget(parent),
                                                                       debug(debug),
                                                                       fs(fs) {
  goBackItem = new QListWidgetItem(this);
  goBackItem->setText("../");
  this->addItem(goBackItem);
  this->setMinimumWidth(100);

  /* use monospaced font for file list */
  QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  font.setPointSize(12);
  this->setFont(font);

  current = root;
  this->loadCurrentTree();

  connect(this, &QListWidget::itemDoubleClicked, this, [&](QListWidgetItem *_item) -> void {
    if (_item == goBackItem) {
      if (!parents.isEmpty()) {
        current = parents.takeLast();
      }
      this->loadCurrentTree();
    } else {
      Item *item = dynamic_cast<Item *>(_item);
      if (item->getMode() != 0x040000U) {
        emit objectSelected(item->getMode(), item->getName(), item->getHash());
      } else {
        parents.push_back(current);
        current = item->getHash();
        this->loadCurrentTree();
      }
    }
  });
}

/**
 * Load current tree to the list widget.
 */
void List::loadCurrentTree() {
  goBackItem->setHidden(parents.isEmpty());
  for (QListWidgetItem *item : items) {
    this->removeItemWidget(item);
  }
  qDeleteAll(items);
  items.clear();

  if (!current.isEmpty()) {
    QByteArray data = fs->getDecompressedObject(current);
    auto byte = data.constBegin() + data.indexOf('\0') + 1;
    while (byte < data.constEnd() - 20) {
      uint32_t mode = 0x000000;
      QString name = QString(), hash = QString();
      QString modeString = QString();
      QByteArray hashBytes = QByteArray();
      while (*byte != ' ') {
        modeString += *(byte++);
      }
      ++byte;// skip the space between MODE and NAME
      while (*byte != '\0') {
        name += *(byte++);
      }
      ++byte;// skip the null between NAME and HASH
      for (int i = 0; i < 20; ++i) {
        hashBytes += *(byte++);
      }
      mode = modeString.toUInt(nullptr, 16);
      hash = FS::convertBytesToHash(hashBytes);

      Item *item = new Item(mode, name, hash);
      this->addItem(item);
      items.push_back(item);
    }
  }
}
