/**
 * Class QGit::Reference::Detail
 * Widget of a detailed git blob file.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_TREE_DETAIL_H_
#define QGIT_SRC_HEADERS_TREE_DETAIL_H_

#include <QtCore>
#include <QtWidgets/QPlainTextEdit>

namespace QGit::Tree {
class Detail final : public QPlainTextEdit {
 Q_OBJECT

 private:// Members
  const bool debug;

 public:// Constructors
  Item(bool debug, QWidget *parent);

 public: // Interfaces
  void loadBlob(uint32_t mode, const QString &name, const QString &hash);
};
}// namespace QGit::Tree

#endif//QGIT_SRC_HEADERS_TREE_DETAIL_H_
