/**
 * Class QGit::Commit::Detail
 * Widget of details of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit-detail.h"

#include <QFontDatabase>

#include "IconFontCppHeaders/IconsFontAwesome5.h"
#include "commit-item.h"
#include "tree-panel.h"
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

  {
    auto hashWidget = new QWidget(this);
    auto hashLayout = new QHBoxLayout(hashWidget);
    hashLayout->setContentsMargins(0, 0, 0, 0);

    auto hashIcon = new QLabel(hashWidget);
    hashIcon->setFont(QFont(FONT_ICON_FAMILY));
    hashIcon->setText(ICON_FA_CODE);
    hashIcon->setFixedWidth(20);
    hashIcon->setAlignment(Qt::AlignCenter);
    hashLayout->addWidget(hashIcon);

    QFont hashFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    hashFont.setPointSize(15);
    hashLabel = new QLabel(this);
    hashLabel->setFont(hashFont);
    hashLayout->addWidget(hashLabel, 1);

    hashWidget->setLayout(hashLayout);
    detailLayout->addWidget(hashWidget);
  }

  {
    auto messageWidget = new QWidget(this);
    auto messageLayout = new QHBoxLayout(messageWidget);
    messageLayout->setContentsMargins(0, 0, 0, 0);

    auto messageIcon = new QLabel(messageWidget);
    messageIcon->setFont(QFont(FONT_ICON_FAMILY));
    messageIcon->setText(ICON_FA_EDIT);
    messageIcon->setFixedWidth(20);
    messageIcon->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    messageIcon->setContentsMargins(0, 5, 0, 0);
    messageLayout->addWidget(messageIcon);

    auto messageInnerWidget = new QWidget(this);
    auto messageInnerLayout = new QVBoxLayout(messageInnerWidget);
    messageInnerLayout->setContentsMargins(0, 0, 0, 0);
    {
      QFont titleFont = QFontDatabase::systemFont(QFontDatabase::TitleFont);
      titleFont.setPointSize(15);
      titleFont.setBold(true);
      titleLabel = new QLabel(this);
      titleLabel->setFont(titleFont);
      messageInnerLayout->addWidget(titleLabel);

      messageLabel = new QLabel(this);
      messageInnerLayout->addWidget(messageLabel);
    }
    messageInnerWidget->setLayout(messageInnerLayout);
    messageLayout->addWidget(messageInnerWidget);

    messageWidget->setLayout(messageLayout);
    detailLayout->addWidget(messageWidget);
  }

  {
    auto parentWidget = new QWidget(this);
    auto parentLayout = new QHBoxLayout(parentWidget);
    parentLayout->setContentsMargins(0, 0, 0, 0);

    auto parentIcon = new QLabel(parentWidget);
    parentIcon->setFont(QFont(FONT_ICON_FAMILY));
    parentIcon->setText(ICON_FA_CODE_BRANCH);
    parentIcon->setFixedWidth(20);
    parentIcon->setAlignment(Qt::AlignCenter);
    parentLayout->addWidget(parentIcon);

    parentsLabel = new QLabel(this);
    parentsLabel->setTextFormat(Qt::RichText);
    parentLayout->addWidget(parentsLabel);

    parentWidget->setLayout(parentLayout);
    detailLayout->addWidget(parentWidget);
  }

  {
    auto authorWidget = new QWidget(this);
    auto authorLayout = new QHBoxLayout(authorWidget);
    authorLayout->setContentsMargins(0, 0, 0, 0);

    auto authorIcon = new QLabel(authorWidget);
    authorIcon->setFont(QFont(FONT_ICON_FAMILY));
    authorIcon->setText(ICON_FA_USER);
    authorIcon->setFixedWidth(20);
    authorIcon->setAlignment(Qt::AlignCenter);
    authorLayout->addWidget(authorIcon);

    authorLabel = new QLabel(this);
    authorLayout->addWidget(authorLabel);

    authorWidget->setLayout(authorLayout);
    detailLayout->addWidget(authorWidget);
  }

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

  QString parentString = "Child commit of";
  QStringList parents = item->getParents();
  for (int i = 0; i < parents.length(); ++i) {
    parentString += "&nbsp;<code>" + parents[i].mid(0, 8) + "</code>";
    if (i != parents.length() - 1) {
      parentString += ",";
    }
  }
  parentsLabel->setText(parentString);

  messageLabel->setText(item->getMessage());
}
