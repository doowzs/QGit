/**
 * QGit::Constants
 * Define constants across the project.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */
#include <QtCore>

namespace QGit {
namespace Constants {
namespace Application {
const QString name = "QGit: A Qt based Git browser.";
const QString author = "Tianyun Zhang";
const QVersionNumber version(CMAKE_VERSION_MAJOR, CMAKE_VERSION_MINOR, CMAKE_VERSION_PATCH);
}// namespace Application
};// namespace Constants
}// namespace QGit
