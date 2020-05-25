/**
 * Class QGit::Commit::Panel
 * Main widget of a repository's commit tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_COMMIT_PANEL_H_
#define QGIT_SRC_HEADERS_COMMIT_PANEL_H_

#include <QtCore>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(FS)

namespace Commit {
QT_FORWARD_DECLARE_CLASS(List)
QT_FORWARD_DECLARE_CLASS(Detail)

class Panel final : public QWidget {
  Q_OBJECT

 private:// Members
  const bool debug;
  const QString path;
  const QString hash;
  FS *fs{};

 private:// Widgets
  QHBoxLayout *panelLayout{};
  List *listWidget{};
  Detail *detailWindow{};

 public:// Constructors
  Panel(bool debug, const QString &path, const QString &hash, QWidget *parent);

 private Q_SLOTS:// Slots
  void commitSelected(const QString &_hash, const QString &tree, const QStringList &parents,
                      const QString &author, const QString &title, const QString &message);
};
}// namespace Commit
}// namespace QGit

#endif//QGIT_SRC_HEADERS_COMMIT_PANEL_H_
