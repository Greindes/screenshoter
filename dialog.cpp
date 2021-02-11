#include "dialog.h"
#include "ui_dialog.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //инициализация иконки в трее
    createActions();
    createTrayIcon();
    trayIcon->show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::createActions()
{
    settingsAction = new QAction("Настройки", this);
    connect(settingsAction, &QAction::triggered, this, &QWidget::show);
    quitAction = new QAction("Выход", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Dialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(settingsAction);

    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(QIcon("D:/CPP/MineSweeper/icons/3.png"));
    trayIcon->setContextMenu(trayIconMenu);
}
