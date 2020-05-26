/**
 * Class QGit::Tree::List
 * Widget of a list of tree objects.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "tree/list.h"
#include "tree/item.h"

#include "gitfs.h"
using namespace QGit;
using namespace QGit::Tree;

/**
 * Initialize a list blob object in a git tree.
 * @param debug
 * @param root
 * @param fs
 * @param parent
 */
List::List(bool debug, const QString &root, FS *fs, QWidget *parent) : QListWidget(parent),
                                                                       debug(debug) {
  QStringList list = QStringList({root});
  while (!list.isEmpty()) {
    QString cur = list.takeFirst();
    if (!cur.isEmpty()) {
      QByteArray data = fs->getDecompressedObject(cur);
      auto byte = data.constBegin() + data.indexOf('\0') + 1;
      while (byte < data.constEnd() - 20) {
        uint32_t mode = 0x000000;
        QString name = QString(), hash = QString();
        QString modeString = QString();
        QByteArray hashBytes = QByteArray();
        while (*byte != ' ') {
          modeString += *(byte++);
        }
        ++byte;// skip the space between MODE and NAME
        while (*byte != '\0') {
          name += *(byte++);
        }
        ++byte;// skip the null between NAME and HASH
        for (int i = 0; i < 20; ++i) {
          hashBytes += *(byte++);
        }
        mode = modeString.toUInt(nullptr, 16);
        hash = FS::convertBytesToHash(hashBytes);
        qDebug() << hex << mode << name << hash;
        switch (mode) {
          case 0x040000U: {
            /* another file tree */
            list.append(hash);
            break;
          }
          case 0x100644U:
          case 0x100755U:
          case 0x120000U: {
            /* file, executable and symbolic link */
            Item *item = new Item(mode, name, hash);
            this->addItem(item);
            break;
          }
          default:
            qDebug() << "unknown object mode" << mode;
        }
      }
    }
  }
}
