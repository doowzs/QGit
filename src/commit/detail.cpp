/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/detail.h"
using namespace QGit::Commit;

Detail::Detail(bool debug, const QString &hash, const QString &tree, const QStringList &parents,
               const QString &author, const QString &title, const QString &message, QWidget *parent) : QWidget(parent, Qt::Window),
                                                                                                       debug(debug),
                                                                                                       hash(hash),
                                                                                                       tree(tree),
                                                                                                       parents(parents),
                                                                                                       author(author),
                                                                                                       title(title),
                                                                                                       message(message) {
  detailLayout = new QVBoxLayout(this);

  hashLabel = new QLabel(this);
  hashLabel->setFont(QFont("JetBrains Mono", 15));
  hashLabel->setText(hash);
  detailLayout->addWidget(hashLabel);

  this->setWindowTitle("提交详情");
  this->setLayout(detailLayout);
}
