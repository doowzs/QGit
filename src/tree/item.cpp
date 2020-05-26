/**
 * Class QGit::Tree::Item
 * Widget of a blob object as a list item.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/item.h"

#include <QFontDatabase>
using namespace QGit::Tree;

/**
 * Initialize a blob object item.
 * @param mode
 * @param name
 * @param hash
 */
Item::Item(uint32_t mode, const QString &name, const QString &hash) : mode(mode),
                                                                      name(name),
                                                                      hash(hash) {
  if (mode == 0x040000U) {
    /* treat sub-tree as a folder */
    this->setText(name + "/");
  } else {
    /* regular files and executables */
    this->setText(name);
  }
}

/**
 * Get the mode of the blob object.
 * @return mode
 */
uint32_t Item::getMode() const { return mode; }

/**
 * Get the name of the blob object.
 * @return name
 */
const QString Item::getName() const { return name; }

/**
 * Get the hash of the blob object.
 * @return hash
 */
const QString Item::getHash() const { return hash; }
