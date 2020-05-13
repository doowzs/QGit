/**
 * Class QGit::Root
 * Show welcome message and open a repository.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#ifndef QGIT_SRC_HEADERS_WELCOME_H_
#define QGIT_SRC_HEADERS_WELCOME_H_

#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>

namespace QGit {
class Welcome final : public QWidget {
 Q_OBJECT

 private: // Members
  const bool debug;

 private: // Widgets
  QVBoxLayout *welcomeLayout{};
  QLabel *titleLabel{};
  QPushButton *openButton{};
  QPushButton *exitButton{};
  QLabel *versionLabel{};
  QLabel *authorLabel{};

 Q_SIGNALS: // Signals
  void repositoryOpened(const QString &path);

 public: // Constructors
  Welcome(bool debug, QWidget *parent);
};
}

#endif //QGIT_SRC_HEADERS_WELCOME_H_
