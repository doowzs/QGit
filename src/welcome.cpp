/**
 * Class QGit::Welcome
 * Show welcome message and open a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "welcome.h"
using namespace QGit;

/**
 * Initialize a welcome widget.
 */
Welcome::Welcome(bool debug, QWidget *parent) : QWidget(parent), debug(debug) {}
