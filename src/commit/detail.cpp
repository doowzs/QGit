/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/detail.h"
#include "tree/panel.h"
using namespace QGit;
using namespace QGit::Commit;

Detail::Detail(bool debug, const QString &hash, const QString &tree, const QStringList &parents,
               const QString &author, const QString &title, const QString &message, FS *fs,
               QWidget *parent) : QWidget(parent, Qt::Window),
                                  debug(debug),
                                  hash(hash),
                                  tree(tree),
                                  parents(parents),
                                  author(author),
                                  title(title),
                                  message(message),
                                  fs(fs) {
  detailLayout = new QVBoxLayout(this);

  hashLabel = new QLabel(this);
  hashLabel->setFont(QFont("JetBrains Mono", 15));
  hashLabel->setText(hash);
  detailLayout->addWidget(hashLabel);

  titleLabel = new QLabel(this);
  titleLabel->setText(title);
  detailLayout->addWidget(titleLabel);

  messageLabel = new QLabel(this);
  messageLabel->setText(message);
  detailLayout->addWidget(messageLabel);

  authorLabel = new QLabel(this);
  authorLabel->setText(author);
  detailLayout->addWidget(authorLabel);

  treePanel = new Tree::Panel(debug, hash, fs, this);
  detailLayout->addWidget(treePanel);

  this->setWindowTitle("提交详情");
  this->setLayout(detailLayout);
}
