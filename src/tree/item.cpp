/**
 * Class QGit::Tree::Item
 * Widget of a blob object as a list item.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/item.h"

#include "gitfs.h"
using namespace QGit::Tree;

Item::Item(bool debug, QWidget *parent) : QPlainTextEdit(parent),
                                          debug(debug) {
  this->setEnabled(false);
}

void Item::loadBlob(uint32_t mode, const QString &name, const QString &hash) {
  switch (mode) {
    case 0x100644: { /* file */

    }
    case 0x100755: { /* executable */
      this->setPlainText("This is a binary executable file.");
      break;
    }
    case 0x120000: { /* symbolic link */
      this->setPlainText("This is a symbolic link.");
      break;
    }
    default:
      qDebug() << "unknown object mode" << mode;
  }
}
