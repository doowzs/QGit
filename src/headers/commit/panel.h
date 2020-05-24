/**
 * Class QGit::Commit::Panel
 * Main widget of a repository's commit tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_COMMIT_PANEL_H_
#define QGIT_SRC_HEADERS_COMMIT_PANEL_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

namespace QGit::Commit {
QT_FORWARD_DECLARE_CLASS(List)

class Panel final : public QWidget {
  Q_OBJECT

 private: // Members
  const bool debug;
  const QString path;
  const QString hash;

 private: // Widgets
  QHBoxLayout *panelLayout{};
  List *listWidget{};

 public: // Constructors
  Panel(bool debug, const QString &path, const QString &hash, QWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_COMMIT_PANEL_H_
