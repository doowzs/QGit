/**
 * Class QGit::Repository
 * The root widget of a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "repository.h"

#include "commit/list.h"
#include "gitfs.h"
#include "reference/list.h"
using namespace QGit;

/**
 * Initialize a repository widget.
 * @param debug
 * @param path
 * @param parent
 */
Repository::Repository(bool debug, const QString &path, QWidget *parent)
    : QWidget(parent, Qt::Window),
      debug(debug),
      root(path),
      fs(new FS(debug, path + "/.git")) {
  repositoryLayout = new QHBoxLayout(this);

  referenceList = new Reference::List(debug, path + "/.git", this);
  repositoryLayout->addWidget(referenceList);

  commitList = new Commit::List(debug, fs, this);
  repositoryLayout->addWidget(commitList);

  connect(referenceList, &Reference::List::referenceSelected, this,
          [&](const QString &name, const QString &hash) -> void {
            commitList->loadCommits(hash);
          });
  connect(commitList, &Commit::List::commitSelected, this,
          [&])

  this->setWindowTitle("提交记录");
  this->setLayout(repositoryLayout);
}

/**
 * Destroy the repository widget and its fs member.
 */
Repository::~Repository() {
  delete this->fs;
}
