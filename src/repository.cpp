/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "repository.h"
using namespace QGit;

/**
 * Initialize a repository widget.
 * @param debug
 * @param path
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent), debug(debug), root(path + "/.git") {
  QDir headsDir = QDir(root + "/refs/heads");
  QStringList headsList = headsDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    QFile headFile = QFile(root + "/refs/heads/" + head);
    try {
      headFile.open(QFile::ReadOnly);
      QString hash = QString(headFile.read(40));
      headFile.close();
      heads[head] = hash;
      if (debug) {
        qDebug() << "ref" << head << hash;
      }
    } catch (QException e) {
      qDebug() << "error:" << e.what() << "when reading ref" << head;
    }
  }
}
