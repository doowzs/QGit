/**
 * Class QGit::Tree::Item
 * Widget of a blob object as a list item.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_TREE_ITEM_H_
#define QGIT_SRC_HEADERS_TREE_ITEM_H_

#include <QtCore>
#include <QtWidgets/QListWidgetItem>

namespace QGit::Tree {
class Item final : public QListWidgetItem {
 private:// Members
  const uint32_t mode;
  const QString name;
  const QString hash;

 public:// Constructors
  Item(uint32_t mode, const QString &name, const QString &hash);

 public:// Interfaces
  [[nodiscard]] uint32_t getMode() const;
  [[nodiscard]] const QString getName() const;
  [[nodiscard]] const QString getHash() const;
};
}// namespace QGit::Tree

#endif//QGIT_SRC_HEADERS_TREE_ITEM_H_
