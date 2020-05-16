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
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent), debug(debug), root(path + "/.git") {
  QDir headsDir = QDir(root + "/refs/heads");
  QStringList headsList = headsDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
  foreach (QString head, headsList) {
    QFile headFile = QFile(root + "/refs/heads/" + head);
    QString hash = QString(headFile.readAll());
    heads[head] = hash;
    if (debug) {
      qDebug() << "ref" << head << hash;
    }
  }
}
