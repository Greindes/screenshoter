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

#include <QStandardPaths>

#include <QHotkey>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //инициализация иконки в трее
    qDebug() << "Initializing";
    createActions();
    createTrayIcon();
    createAndConnectShortcuts();
    qDebug() << "After shortcuts";
    createScreenshoters();
    on_noneRadioButton_pressed();
    qDebug() << "here";
    setDefaultSavePath();
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


void Dialog::createAndConnectShortcuts()
{
    //Снимок всего экрана
    QKeySequence seq = ui->simpleKeySequenceEdit->keySequence();
    simpleScrShortcut = new QHotkey(seq, false, this);
    //on/of
    connect(ui->simpleCheckBox, &QCheckBox::toggled,
            simpleScrShortcut, &QHotkey::setRegistered);
    //pressed
    connect(simpleScrShortcut, &QHotkey::activated,
            this, &Dialog::takeSimpleScreenshot);

    //снимок с вырезанием
    seq = ui->cutKeySequenceEdit->keySequence();
    cutScrShortcut = new QHotkey(seq, false, this);
    //on/of
    connect(ui->cutCheckBox, &QCheckBox::toggled,
            cutScrShortcut, &QHotkey::setRegistered);
    //pressed
    connect(cutScrShortcut, &QHotkey::activated,
            this, &Dialog::takeCutScreenshot);
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

void Dialog::setDefaultSavePath()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    qDebug() << "Path to images: " << path;
    ui->saveFolderComboBox->addItem(path + "/Screens/");
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
    simpleScrShortcut->setShortcut(keySequence, true);
}

void Dialog::on_cutKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence)
{
    cutScrShortcut->setShortcut(keySequence, true);
}

void Dialog::on_simpleCheckBox_stateChanged(int arg1)
{
    if (arg1)
        qDebug() << "Screenshoter enabled!\n";
    else
        qDebug() << "Screenshoter disabled!\n";
}

void Dialog::on_cutCheckBox_stateChanged(int arg1)
{
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
    for (int i = ui->saveFolderComboBox->count() - 1; i >= 0; --i) {
        if (ui->saveFolderComboBox->itemText(i) == path)
            return;
    }
    ui->saveFolderComboBox->addItem(path);
    ui->saveFolderComboBox->setCurrentIndex(ui->saveFolderComboBox->count() - 1);
}

void Dialog::on_saveFolderComboBox_currentTextChanged(const QString &path)
{
    std::string s = path.toStdString();
    simpleScr->setPath(s);
    qDebug() << "changing screenshot path!";
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
