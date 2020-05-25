/**
 * Class QGit::Commit::Panel
 * Main widget of a repository's commit tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/panel.h"
#include "commit/list.h"
#include "commit/detail.h"
#include "gitfs.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a panel widget.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
Panel::Panel(bool debug, const QString &path, const QString &hash, QWidget *parent)
    : QWidget(parent),
      debug(debug),
      path(path),
      hash(hash),
      fs(new FS(debug, path + "/.git/objects")) {
  panelLayout = new QHBoxLayout(this);

  listWidget = new List(debug, path + "/.git/objects", hash, fs, this);
  connect(listWidget, &List::commitSelected, this, &Panel::commitSelected);
  panelLayout->addWidget(listWidget);

  this->setLayout(panelLayout);
}

/**
 * When a commit is selected, open a new window to show its details.
 * @param hash
 * @param tree
 * @param parents
 * @param author
 * @param title
 * @param message
 */
void Panel::commitSelected(const QString &_hash, const QString &tree, const QStringList &parents,
                           const QString &author, const QString &title, const QString &message) {
  if (detailWindow != nullptr) {
    detailWindow->deleteLater();
  }
  detailWindow = new Detail(debug, _hash, tree, parents, author, title, message, fs, this);
  detailWindow->show();
}
