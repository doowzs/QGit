#include <QApplication>
#include <QFontDatabase>

#include "IconFontCppHeaders/IconsFontAwesome5.h"
#include "IconFontCppHeaders/IconsFontAwesome5Brands.h"
#include "constants.h"
#include "root.h"
using namespace QGit;

void loadFontAwesome();

/**
 * Main entry of the Qt application.
 * @param argc
 * @param argv
 * @return 0 on normal exit
 */
int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QApplication::setOrganizationName(Constants::Application::author);
  QApplication::setApplicationName(Constants::Application::description);
  QApplication::setApplicationVersion(Constants::Application::version.toString());

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption debugOption(QStringList({"d", "debug"}),
                                 QString("Turn on debug mode"));
  parser.addOption(debugOption);

  // parse arguments and set variables.
  parser.process(application);
  bool debug = parser.isSet(debugOption);

  // load font-awesome icons
  loadFontAwesome();

  // start the root / main window
  Root root(debug, nullptr, nullptr);
  root.show();

  return QApplication::exec();
}

/**
 * Load icons in Font Awesome 5.
 */
void loadFontAwesome() {
  if (QFontDatabase::addApplicationFont(FONT_ICON_FILE_NAME_FAS) < 0) {
    qWarning() << "cannot load font awesome solid";
  }
  /*
  if (QFontDatabase::addApplicationFont(FONT_ICON_FILE_NAME_FAR) < 0) {
    qWarning() << "cannot load font awesome regular";
  }
  */
  if (QFontDatabase::addApplicationFont(FONT_ICON_FILE_NAME_FAB) < 0) {
    qWarning() << "cannot load font awesome brands";
  }
}
