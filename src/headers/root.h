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
class Root final : public QMainWindow {
 Q_OBJECT

 private:// Members
  const bool debug;
  QString path;

 public:// Constructors
  Root(bool debug, QString path, QWidget *parent = nullptr);
};
}// namespace QGit

#endif//QGIT_SRC_HEADERS_ROOT_H_
