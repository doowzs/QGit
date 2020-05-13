/**
 * Namespace QGit::Constants
 * Define constants across the project.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_CONSTANTS_H_
#define QGIT_SRC_HEADERS_CONSTANTS_H_

#include <QtCore>

namespace QGit {
namespace Constants {
namespace Application {
const int year = 2020;
const QString name = "QGit";
const QString description = "QGit: A Qt based Git browser.";
const QString author = "Tianyun Zhang";
const QVersionNumber version(CMAKE_VERSION_MAJOR, CMAKE_VERSION_MINOR, CMAKE_VERSION_PATCH);
}// namespace Application
}// namespace Constants
}// namespace QGit

#endif//QGIT_SRC_HEADERS_CONSTANTS_H_
