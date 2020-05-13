/**
 * Class QGit::Root
 * The root / main window of the application.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "root.h"
#include "welcome.h"
using namespace QGit;

/**
 * Initialize a root / main window with path to git repository.
 */
Root::Root(bool debug, QString path, QWidget *parent) : QMainWindow(parent), debug(debug), path(std::move(path)) {
  welcomeWidget = new Welcome(debug, this);

  this->setCentralWidget(welcomeWidget);
}
