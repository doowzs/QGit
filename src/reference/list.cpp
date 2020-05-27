/**
 * Class QGit::Reference::List
 * Widget of a list of git references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/list.h"

#include <QFontDatabase>

#include "reference/item.h"
using namespace QGit::Reference;

/**
 * Initialize a list of git references.
 * @param debug
 * @param path
 * @param parent
 */
List::List(bool debug, const QString &path, QWidget *parent) : QListWidget(parent),
                                                               debug(debug),
                                                               path(path) {
  QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  font.setPointSize(12);
  this->setFont(font);
  this->setFixedWidth(200);
  this->setFixedHeight(600);

  connect(this, &QListWidget::itemDoubleClicked, this, [&](QListWidgetItem *_item) -> void {
    auto item = dynamic_cast<Item *>(_item);
    emit referenceSelected(item->getName(), item->getHash());
  });
  updateReferenceItems();
}

/**
 * Clear list widget and reload refs from disk.
 */
void List::updateReferenceItems() {
  for (auto &item : items) {
    this->removeItemWidget(item);
  }
  qDeleteAll(items);
  items.clear();

  searchHeads();
  searchRemotes();
  searchTags();
  searchPackedRefs();
}

void List::searchPackedRefs() {
  QFile file = QFile(path + "/packed-refs");
  if (!file.exists()) {
    return;
  }

  try {
    file.open(QFile::ReadOnly);
    file.readLine();// skip the first line
    while (!file.atEnd()) {
      QString line = QString(file.readLine());
      Item *item = new Item(debug, line, this);
      items.push_back(item);
      this->addItem(item);
    }
  } catch (const QException &e) {
    qDebug() << "error:" << e.what();
  }
}

/**
 * Search references in .git/refs/heads folder.
 */
void List::searchHeads() {
  QDir headsFolder = QDir(path + "/refs/heads");
  QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    try {
      Item *item = new Item(debug, head, path + "/refs/heads/" + head, this);
      items.push_back(item);
      this->addItem(item);
    } catch (const QException &e) {
      qDebug() << "error:" << e.what();
    }
  }
}

/**
 * Search references in .git/refs/remotes folder.
 */
void List::searchRemotes() {
  QDir remotesFolder = QDir(path + "/refs/remotes");
  QStringList remotesList = remotesFolder.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  for (const QString &remote : remotesList) {
    QDir headsFolder = QDir(path + "/refs/remotes/" + remote);
    QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QString &head : headsList) {
      try {
        Item *item = new Item(debug, remote + "/" + head, path + "/refs/remotes/" + remote + "/" + head, this);
        items.push_back(item);
        this->addItem(item);
      } catch (const QException &e) {
        qDebug() << "error:" << e.what();
      }
    }
  }
}

/**
 * Search references in .git/refs/tags folder.
 */
void List::searchTags() {
  QDir headsFolder = QDir(path + "/refs/tags");
  QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    try {
      Item *item = new Item(debug, "tags/" + head, path + "/refs/tags/" + head, this);
      items.push_back(item);
      this->addItem(item);
    } catch (const QException &e) {
      qDebug() << "error:" << e.what();
    }
  }
}
