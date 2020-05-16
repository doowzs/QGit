/**
 * Class QGit::Reference::List
 * Widget of a list of git references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REFERENCE_LIST_H_
#define QGIT_SRC_HEADERS_REFERENCE_LIST_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

namespace QGit::Reference {
QT_FORWARD_DECLARE_CLASS(Item)

class List final : public QWidget {
 Q_OBJECT

 private: // Members
  const bool debug;

 private: // Widgets
  QVBoxLayout *listLayout{};
  QLabel *titleLabel{};
  QVector<Item *> itemWidgets;

 public: // Constructors
  List(bool debug, const QString &path, QWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_REFERENCE_LIST_H_
