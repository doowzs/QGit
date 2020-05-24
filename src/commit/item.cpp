/**
 * Class QGit::Commit::Item
 * Widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/item.h"
using namespace QGit::Commit;

/**
 * Initialize a git commit item.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
Item::Item(bool debug, const QString &path, const QString &hash, QListWidget *parent)
    : QListWidgetItem(parent), debug(debug), hash(hash) {
  QFile commitFile = QFile(path + "/" + hash.mid(0, 2) + "/" + hash.mid(2));
  commitFile.open(QFile::ReadOnly);
  qDebug() << commitFile.readAll();
  commitFile.close();
}
