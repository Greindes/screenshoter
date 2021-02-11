#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QSystemTrayIcon;
class QMenu;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    QAction* settingsAction;
    QAction* quitAction;

    void createActions();
    void createTrayIcon();
};

#endif // DIALOG_H
