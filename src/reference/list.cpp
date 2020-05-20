/**
 * Class QGit::Reference::List
 * Widget of a list of git references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/item.h"
#include "reference/list.h"
using namespace QGit::Reference;

/**
 * Initialize a list of git references.
 * @param debug
 * @param path
 * @param parent
 */
List::List(bool debug, const QString &path, QWidget *parent) : QWidget(parent), debug(debug), path(path) {
  listLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setFont(QFont(nullptr, 25));
  titleLabel->setText("Refs");
  listLayout->addWidget(titleLabel);

  listWidget = new QListWidget(this);
  updateReferenceItems();
  listLayout->addWidget(listWidget);

  this->setLayout(listLayout);
}

/**
 * Clear list widget and reload refs from disk.
 */
void List::updateReferenceItems() {
  for (auto &item : items) {
    listWidget->removeItemWidget(item);
  }
  qDeleteAll(items);
  items.clear();

  searchHeads();
  searchRemotes();
  searchTags();
}

/**
 * Search references in .git/refs/heads folder.
 */
void List::searchHeads() {
  QDir headsFolder = QDir(path + "/heads");
  QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    try {
      if (debug) {
        qDebug() << "ref:" << head;
      }
      Item *item = new Item(debug, head, path + "/heads/" + head, listWidget);
      items.push_back(item);
      listWidget->addItem(item);
    } catch (const QException &e) {
      qDebug() << "error:" << e.what();
    }
  }
}


/**
 * Search references in .git/refs/remotes folder.
 */
void List::searchRemotes() {
  QDir remotesFolder = QDir(path + "/remotes");
  QStringList remotesList = remotesFolder.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  for (const QString &remote : remotesList) {
    QDir headsFolder = QDir(path + "/remotes/" + remote);
    QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QString &head : headsList) {
      try {
        if (debug) {
          qDebug() << "ref:" << remote + "/" + head;
        }
        Item *item = new Item(debug, remote + "/" + head, path + "/remotes/" + remote + "/" + head, listWidget);
        items.push_back(item);
        listWidget->addItem(item);
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
  QDir headsFolder = QDir(path + "/tags");
  QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    try {
      if (debug) {
        qDebug() << "ref:" << head;
      }
      Item *item = new Item(debug, "tags/" + head, path + "/tags/" + head, listWidget);
      items.push_back(item);
      listWidget->addItem(item);
    } catch (const QException &e) {
      qDebug() << "error:" << e.what();
    }
  }
}
