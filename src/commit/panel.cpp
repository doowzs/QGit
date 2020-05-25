/**
 * Class QGit::Commit::Panel
 * Main widget of a repository's commit tree.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/panel.h"

#include "commit/list.h"
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
  panelLayout->addWidget(listWidget);

  this->setLayout(panelLayout);
}
