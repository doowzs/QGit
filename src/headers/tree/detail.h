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

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Tree {
class Detail final : public QPlainTextEdit {
  Q_OBJECT

 private:// Members
  const bool debug;
  FS *fs;

 public:// Constructors
  Detail(bool debug, FS *fs, QWidget *parent);

 public:// Interfaces
  void loadBlobContent(uint32_t mode, const QString &name, const QString &hash);
};
}// namespace Tree
}// namespace QGit

#endif//QGIT_SRC_HEADERS_TREE_DETAIL_H_
