/**
 * Class QGit::Root
 * The root / main window of the application.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "root.h"

namespace QGit {

/**
 * Initialize a root / main window with path to git repository.
 */
Root::Root(bool debug, QString path, QWidget *parent) : QMainWindow(parent), debug(debug), path(std::move(path)) {}

}// namespace QGit
