#include "constants.h"
#include <QCoreApplication>
using namespace QGit;

int main(int argc, char *argv[]) {
  QCoreApplication application(argc, argv);

  QCoreApplication::setOrganizationName(Constants::Application::author);
  QCoreApplication::setApplicationName(Constants::Application::name);
  QCoreApplication::setApplicationVersion(Constants::Application::version.toString());

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

  return QCoreApplication::exec();
}
