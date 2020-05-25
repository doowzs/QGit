/**
 * Class QGit::Reference::Item
 * Widget of a git reference as a button.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/item.h"
using namespace QGit::Reference;

/**
 * Initialize a button of a git reference.
 * May throw error when reading the ref file.
 * @param debug
 * @param path
 * @param parent
 */
Item::Item(bool debug, const QString &packed, QListWidget *parent) : QListWidgetItem(parent), debug(debug) {
  QStringList list = packed.split(" ");
  hash = list.takeFirst().trimmed();
  name = "*" + list.takeFirst().trimmed();

  this->setText(name);
}

/**
 * Initialize a button of a git reference.
 * May throw error when reading the ref file.
 * @param debug
 * @param path
 * @param parent
 */
Item::Item(bool debug, const QString &name, const QString &path, QListWidget *list)
    : QListWidgetItem(list), debug(debug), name(name) {
  QFile headFile = QFile(path);
  headFile.open(QFile::ReadOnly);
  hash = QString(headFile.read(40));
  headFile.close();

  this->setText(name);
}

/**
 * Get name of the reference item.
 * @return QString name
 */
QString Item::getName() {
  return name;
}

/**
 * Get hash of the reference item.
 * @return QString hash
 */
QString Item::getHash() {
  return hash;
}
