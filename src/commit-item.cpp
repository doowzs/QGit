/**
 * Class QGit::Commit::Item
 * Widget of a git commit.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "commit-item.h"
#include "gitfs.h"
using namespace QGit;
using namespace QGit::Commit;

/**
 * Initialize a git commit item.
 * @param debug
 * @param hash
 * @param parent
 */
Item::Item(bool debug, const QString &hash, FS *fs, QListWidget *list)
    : QListWidgetItem(list), debug(debug), hash(hash) {
  QTextStream stream(fs->getObject(hash), QIODevice::ReadOnly);

  // read header of the commit
  QString buffer;
  while (true) {
    buffer = stream.readLine();
    if (buffer.isEmpty()) {
      break; // stop reading when an empty line is met
    } else {
      QString type = buffer.mid(0, 3);
      if (type == "tre" /* tree */) {
        tree = buffer.mid(5);
      } else if (type == "par" /* parent */) {
        parents.append(buffer.mid(7));
      } else if (type == "aut" /* author */) {
        // extract commit date from the string
        QString line = buffer.mid(7);
        int offset = line.indexOf("> ") + 2;
        author = line.mid(0, offset);
        timestamp = line.mid(offset);
        date.setTime_t((timestamp.split(' ').takeFirst()).toUInt());
        author += date.toString();
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
  title = stream.readLine();
  message = stream.atEnd() ? "" : stream.readAll();

  this->setText(hash.mid(0, 8) + " " + title);
}

/**
 * Compare two commit object by commit date.
 * @param rhs
 * @return earlier?
 */
bool Item::operator<(const Item &rhs) const {
  return date < rhs.date;
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
