/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/detail.h"

#include <QFontDatabase>

#include "tree/panel.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a widget of a git commit.
 * @param debug
 * @param hash
 * @param tree
 * @param parents
 * @param author
 * @param title
 * @param message
 * @param fs
 * @param parent
 */
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

  QFont hashFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  hashFont.setPointSize(15);
  hashLabel = new QLabel(this);
  hashLabel->setFont(hashFont);
  hashLabel->setText(hash);
  detailLayout->addWidget(hashLabel);

  QFont titleFont = QFontDatabase::systemFont(QFontDatabase::TitleFont);
  titleFont.setPointSize(15);
  titleFont.setBold(true);
  titleLabel = new QLabel(this);
  titleLabel->setFont(titleFont);
  titleLabel->setText(title);
  detailLayout->addWidget(titleLabel);

  messageLabel = new QLabel(this);
  messageLabel->setText(message);
  detailLayout->addWidget(messageLabel);

  authorLabel = new QLabel(this);
  authorLabel->setText(author);
  detailLayout->addWidget(authorLabel);

  treePanel = new Tree::Panel(debug, tree, fs, this);
  detailLayout->addWidget(treePanel);

  this->setWindowTitle("提交详情");
  this->setLayout(detailLayout);
}
