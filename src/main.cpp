#include "constants.h"
#include "root.h"
#include <QApplication>
using namespace QGit;

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

  // start the root / main window
  Root root(debug, nullptr, nullptr);
  root.show();

  return QApplication::exec();
}
