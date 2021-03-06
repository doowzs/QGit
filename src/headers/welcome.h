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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

namespace QGit {
class Welcome final : public QWidget {
 Q_OBJECT

 private: // Members
  const bool debug;

 private: // Widgets
  QHBoxLayout *welcomeLayout{};
  QWidget *recentWidget{};
  QVBoxLayout *recentLayout{};
  QScrollArea *recentScrollArea{};
  QVector<QWidget *> recentItems{};
  QWidget *menuWidget{};
  QVBoxLayout *menuLayout{};
  QLabel *iconLabel{};
  QLabel *titleLabel{};
  QPushButton *openButton{};
  QPushButton *exitButton{};
  QLabel *versionLabel{};
  QLabel *authorLabel{};

 public: // Constructors
  Welcome(bool debug, const QStringList &recentList, QWidget *parent);

 Q_SIGNALS: // Signals
  void repositorySelected(const QString &path);

 private Q_SLOTS: // Slots
  void selectRepository();
  void closeApplication();
};
}

#endif //QGIT_SRC_HEADERS_WELCOME_H_
