/**
 * Class QGit::Commit::Item
 * Widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit/item.h"
#include "gitfs.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a git commit item.
 * @param debug
 * @param path
 * @param hash
 * @param parent
 */
Item::Item(bool debug, const QString &path, const QString &hash, FS *fs, QListWidget *list)
    : QListWidgetItem(list), debug(debug), hash(hash) {
  QTextStream stream = fs->getDecompressedStream(hash);

  // read header of the commit
  QString buffer;
  stream.readLine(); // skip first line: COMMIT SIZE \0
  while (true) {
    buffer = stream.readLine().trimmed();
    if (buffer.isEmpty()) {
      break; // stop reading when an empty line is met
    } else {
      QString type = buffer.mid(0, 3);
      if (type == "tre" /* tree */) {
        tree = buffer.mid(5);
      } else if (type == "par" /* parent */) {
        parents.append(buffer.mid(7));
      } else if (type == "aut" /* author */) {
        author = buffer.mid(7);
      } else if (type == "com" /* committer */) {
        committer = buffer.mid(10);
      } else if (type == "gpg" /* gpg signature */) {
        while (!stream.atEnd() and !buffer.contains("-----END PGP SIGNATURE-----")) {
          buffer = stream.readLine();
        }
      }
    }
  }

  // read title and message of the commit
  title = stream.readLine().trimmed();
  message = stream.atEnd() ? "" : stream.readAll().trimmed();

  this->setText(hash.mid(0, 8) + " " + title);
}

/**
 * Get the hash of the commit.
 * @return hash
 */
QString Item::getHash() const { return hash; }

/**
 * Get the hash of tree of the commit.
 * @return tree
 */
QString Item::getTree() const { return tree; }

/**
 * Get the hash of parent commits.
 * @return parent
 */
QStringList Item::getParents() const { return parents; }

/**
 * Get the author of the commit.
 * @return author
 */
QString Item::getAuthor() const { return author; }

/**
 * Get the title of the commit.
 * @return title
 */
QString Item::getTitle() const { return title; }

/**
 * Get the message of the commit.
 * @return message
 */
QString Item::getMessage() const { return message; }
