/**
 * Class QGit::Reference::Detail
 * Widget of a detailed git reference.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REFERENCE_DETAIL_H_
#define QGIT_SRC_HEADERS_REFERENCE_DETAIL_H_

#include <QtCore>
#include <QtWidgets/QWidget>

namespace QGit::Reference {
class Detail final : public QWidget {
  Q_OBJECT

 private: // Members
  const bool debug;
  const QString hash;

 public: // Constructors
  Detail(bool debug, const QString &hash, QWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_REFERENCE_DETAIL_H_
