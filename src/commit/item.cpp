/**
 * Class QGit::Commit::Item
 * Widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include <zlib.h>

#include "commit/item.h"
using namespace QGit::Commit;

/**
 * Initialize a git commit item.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
Item::Item(bool debug, const QString &path, const QString &hash, QListWidget *list)
    : QListWidgetItem(list), debug(debug), hash(hash) {
  QFile commitFile = QFile(path + "/" + hash.mid(0, 2) + "/" + hash.mid(2));
  commitFile.open(QFile::ReadOnly);
  QByteArray compressedData = commitFile.readAll();
  commitFile.close();

  // inflate commit data with zlib
  bool inflated = false;
  uLong uncompressedLength = 4096;
  QByteArray uncompressedData = QByteArray(uncompressedLength, '\0');
  while (not inflated) {
    int result = uncompress((Bytef *) uncompressedData.data(),
                            &uncompressedLength,
                            (const Bytef *) compressedData.constData(),
                            (uLong) compressedData.length() + 1);
    if (result == Z_OK) {
      inflated = true;
    } else if (result == Z_BUF_ERROR) {
      uncompressedLength *= 2;
      uncompressedData = QByteArray(uncompressedLength, '\0');
    } else {
      qDebug() << "uncompress failed with code" << result;
      exit(-1);
    }
  }
  QTextStream stream = QTextStream(uncompressedData, QIODevice::ReadOnly);

  // read header of the commit
  stream.readLine(); // COMMIT SIZE \0
  parent = stream.readLine().mid(7);
  author = stream.readLine().mid(7);
  committer = stream.readLine().mid(10);

  // skip gpg signature of the commit
  if (stream.readLine().mid(0, 6) == QString("gpgsig")) {
    while (!stream.atEnd() and stream.readLine() != QString(" -----END PGP SIGNATURE-----")) continue;
  }
  stream.readLine(); // skip the blank line

  // read title and message of the commit
  title = stream.readLine();
  message = stream.readAll();

  this->setText(hash.mid(0, 8) + " " + title);
}
