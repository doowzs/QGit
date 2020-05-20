/**
 * Class QGit::Reference::Panel
 * Main widget of the repository's references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REFERENCE_PANEL_H_
#define QGIT_SRC_HEADERS_REFERENCE_PANEL_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

namespace QGit::Reference {
QT_FORWARD_DECLARE_CLASS(List)
QT_FORWARD_DECLARE_CLASS(Detail)

class Panel final : public QWidget {
  Q_OBJECT

 private: // Members
  const bool debug;
  const QString path;

 private: // Widgets
  QHBoxLayout *panelLayout{};
  List *listWidget{};
  Detail *detailWidget{};

 public: // Constructors
  Panel(bool debug, const QString &path, QWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_REFERENCE_PANEL_H_
