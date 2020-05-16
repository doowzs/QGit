/**
 * Class QGit::Reference::List
 * Widget of a list of git references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/item.h"
#include "reference/list.h"
using namespace QGit::Reference;

/**
 * Initialize a list of git references.
 * @param debug
 * @param path
 * @param parent
 */
List::List(bool debug, const QString &path, QWidget *parent) : QWidget(parent), debug(debug) {
  listLayout = new QVBoxLayout(this);

  titleLabel = new QLabel(this);
  titleLabel->setFont(QFont(nullptr, 25));
  titleLabel->setText("Refs");
  listLayout->addWidget(titleLabel);

  QDir headsFolder = QDir(path);
  QStringList headsList = headsFolder.entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (const QString &head : headsList) {
    try {
      if (debug) {
        qDebug() << "ref:" << head;
      }
      Item *itemWidget = new Item(debug, head, path + "/" + head, this);
      itemWidgets.push_back(itemWidget);
      listLayout->addWidget(itemWidget);
    } catch (const QException &e) {
      qDebug() << "error:" << e.what();
    }
  }

  this->setLayout(listLayout);
}
