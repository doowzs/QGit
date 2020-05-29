/**
 * Class QGit::Reference::Detail
 * Widget of a detailed git blob file.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree-detail.h"

#include "gitfs.h"
using namespace QGit;
using namespace QGit::Tree;

Detail::Detail(bool debug, FS *fs, QWidget *parent) : QPlainTextEdit(parent),
                                                      debug(debug),
                                                      fs(fs) {
  QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  font.setPointSize(12);
  this->setFont(font);
  this->setReadOnly(true);
  this->setMinimumWidth(600);
  this->setMinimumHeight(600);
}

void Detail::loadBlobContent(uint32_t mode, const QString &name, const QString &hash) {
  switch (mode) {
    case 0x100644: {
      /* file */
      QByteArray data = fs->getObject(hash);
      data = data.mid(data.indexOf('\0') + 1);
      this->setPlainText(QString(data));
      break;
    }
    case 0x100755: {
      /* executable */
      this->setPlainText("This file is an executable binary.");
      break;
    }
    case 0x120000: {
      /* symbolic link */
      this->setPlainText("This file is a symbolic link.");
      break;
    }
    default: {
      this->setPlainText("Unknown file mode " + QString::number(mode, 16));
      qDebug() << "unknown file mode" << mode;
      break;
    }
  }
}
