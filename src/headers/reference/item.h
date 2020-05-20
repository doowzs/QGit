/**
 * Class QGit::Reference::Item
 * Widget of a git reference as a button.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REFERENCE_ITEM_H_
#define QGIT_SRC_HEADERS_REFERENCE_ITEM_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>

namespace QGit::Reference {
class Item final : public QListWidgetItem {
 private: // Members
  const bool debug;
  QString name;
  QString hash;

 public: // Constructors
  Item(bool debug, const QString &name, const QString &path, QListWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_REFERENCE_ITEM_H_
