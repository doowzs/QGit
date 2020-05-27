/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/detail.h"

#include <QFontDatabase>

#include "commit/item.h"
#include "tree/panel.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a widget of a git commit.
 * @param debug
 * @param parent
 */
Detail::Detail(bool debug, QWidget *parent) : QWidget(parent),
                                              debug(debug) {
  detailLayout = new QVBoxLayout(this);

  QFont hashFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  hashFont.setPointSize(15);
  hashLabel = new QLabel(this);
  hashLabel->setFont(hashFont);
  detailLayout->addWidget(hashLabel);

  QFont titleFont = QFontDatabase::systemFont(QFontDatabase::TitleFont);
  titleFont.setPointSize(15);
  titleFont.setBold(true);
  titleLabel = new QLabel(this);
  titleLabel->setFont(titleFont);
  detailLayout->addWidget(titleLabel);

  messageLabel = new QLabel(this);
  detailLayout->addWidget(messageLabel);

  parentsLabel = new QLabel(this);
  parentsLabel->setTextFormat(Qt::RichText);
  detailLayout->addWidget(parentsLabel);

  authorLabel = new QLabel(this);
  detailLayout->addWidget(authorLabel);

  this->setLayout(detailLayout);
}

/**
 * Slot: load commit info from an item.
 * @param hash
 * @param tree
 * @param parents
 * @param author
 * @param title
 * @param message
 */
void Detail::loadCommit(const Item *item) {
  hashLabel->setText(item->getHash());
  authorLabel->setText(item->getAuthor());
  titleLabel->setText(item->getTitle());

  QString parentString = "Child commit of ";
  for (const QString &parent : item->getParents()) {
    parentString += "<code>" + parent.mid(0, 8) + "</code>";
  }
  parentsLabel->setText(parentString);

  messageLabel->setText(item->getMessage());
}
