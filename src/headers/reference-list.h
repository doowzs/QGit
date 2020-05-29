/**
 * Class QGit::Reference::List
 * Widget of a list of git references.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_REFERENCE_LIST_H_
#define QGIT_SRC_HEADERS_REFERENCE_LIST_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>

namespace QGit::Reference {
QT_FORWARD_DECLARE_CLASS(Item)

class List final : public QListWidget {
 Q_OBJECT

 private: // Members
  const bool debug;
  const QString path; // path to .git/heads
  QVector<Item *> items;

 public: // Constructors
  List(bool debug, const QString &path, QWidget *parent);

 private: // Methods
  void updateReferenceItems();
  void searchHeads();
  void searchRemotes();
  void searchTags();
  void searchPackedRefs();

 Q_SIGNALS: // Signals
  void referenceSelected(const QString &name, const QString &hash);
};
}

#endif //QGIT_SRC_HEADERS_REFERENCE_LIST_H_
