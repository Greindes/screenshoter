#include "dialog.h"
#include "ui_dialog.h"
#include "simplescreenshot.h"
#include "buffersaver.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include <QShortcut>
#include <QKeySequence>

#include <QDebug>
#include <QKeyEvent>

#include <QFileDialog>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //инициализация иконки в трее
    qDebug() << "Startu";
    createActions();
    createTrayIcon();
    createShortcuts();
    qDebug() << "Middlu";
    createScreenshoters();
    on_noneRadioButton_pressed();
    qDebug() << "here";
    trayIcon->show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::takeSimpleScreenshot()
{
    qDebug() << "making screenshot!\n";

    if (ui->savingGroupBox->isChecked()) {
        simpleScr->takeAndSaveScreenshot();
    } else
        simpleScr->takeScreenshot();
}

void Dialog::takeCutScreenshot()
{
    //do something here
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

    trayIcon = new QSystemTrayIcon(QIcon("D:/CPP/MineSweeper/icons/3.png"), this);
    trayIcon->setContextMenu(trayIconMenu);
}


void Dialog::createShortcuts()
{
    QKeySequence seq = ui->simpleKeySequenceEdit->keySequence();
    simpleScrShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(takeSimpleScreenshot()));
    seq = ui->cutKeySequenceEdit->keySequence();
    cutScrShortcut = new QShortcut(QKeySequence(seq), this, SLOT(takeCutScreenshot()), nullptr, Qt::ApplicationShortcut);
}

void Dialog::createScreenshoters()
{
    simpleScr = new SimpleScreenshot;
    simpleScr->setSaver(std::make_shared<BufferSaver>(BufferSaver()));
    qDebug() << "changing shortcut";
    //cutScr = new...
}

//вызывается при использовании переключателя выбора создания подкаталогов
void Dialog::changeSaverSetting(BufferSaver::SubDirSettings sett)
{
    simpleScr->getSaver().get()->setSetting(sett);
}


//нужно убрать
void Dialog::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key() << ' ' << event->text();
}

void Dialog::on_simpleKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence)
{
    qDebug() << "Setting key to " << keySequence.count();
    qDebug() << "Count for  " << ui->simpleKeySequenceEdit->keySequence().count();
    simpleScrShortcut->setKey(keySequence);
}

void Dialog::on_cutKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence)
{
    cutScrShortcut->setKey(keySequence);
}

void Dialog::on_simpleCheckBox_stateChanged(int arg1)
{
    if (arg1)
        qDebug() << "Screenshoter enabled!\n";
    else
        qDebug() << "Screenshoter disabled!\n";
    simpleScrShortcut->setEnabled(arg1);
}

void Dialog::on_cutCheckBox_stateChanged(int arg1)
{
    cutScrShortcut->setEnabled(arg1);
}


//Выбор каталога сохранения снимков
void Dialog::on_saveFolderPushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Выберите каталог");
    if (path == "")
        return;
    qDebug() << path << " selected!\n";
    if (path.back() != '/')
        path += '/';
    for (int i = ui->comboBox->count() - 1; i >= 0; --i) {
        if (ui->comboBox->itemText(i) == path)
            return;
    }
    ui->comboBox->addItem(path);
    ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
}

void Dialog::on_comboBox_currentTextChanged(const QString &path)
{
    std::string s = path.toStdString();
    simpleScr->setPath(s);
    //cutScr->setPath(s);
}

void Dialog::on_simpleCheckBox_clicked(bool checked)
{
    ui->simpleKeySequenceEdit->setEnabled(checked);
}

void Dialog::on_cutCheckBox_clicked(bool checked)
{
    ui->cutKeySequenceEdit->setEnabled(checked);
}

void Dialog::on_noneRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::NONE);
}

void Dialog::on_dayRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::DAY);
}

void Dialog::on_MonthRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::MONTH);
}

void Dialog::on_YearRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::YEAR);
}
