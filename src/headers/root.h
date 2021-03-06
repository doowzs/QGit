/**
 * Class QGit::Root
 * The root / main window of the application.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_ROOT_H_
#define QGIT_SRC_HEADERS_ROOT_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

namespace QGit {
QT_FORWARD_DECLARE_CLASS(Welcome)
QT_FORWARD_DECLARE_CLASS(Repository)

class Root final : public QMainWindow {
 Q_OBJECT

 private: // Members
  const bool debug;
  QStringList recentList;

 private: // Widgets
  Welcome *welcomeWidget{};
  Repository *repositoryWidget{};

 public: // Constructors
  Root(bool debug, const QString &path, QWidget *parent);

 Q_SIGNALS: // Signals

 private Q_SLOTS: // Slots
  void openRepository(const QString &_path);
  void closeRepository();
};
}// namespace QGit

#endif//QGIT_SRC_HEADERS_ROOT_H_
