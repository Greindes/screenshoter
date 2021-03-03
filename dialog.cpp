#include "dialog.h"
#include "ui_dialog.h"
#include "simplescreenshot.h"
#include "cutscreenshot.h"
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
    loadSettings();
    setDefaultSavePath();
    qDebug() << "finished loading settings";
    trayIcon->show();
}

Dialog::~Dialog()
{
    updateSettings();
    delete ui;
}

void Dialog::takeSimpleScreenshot()
{
    qDebug() << "making screenshot!\n";

    bool isTaken;
    if (ui->savingGroupBox->isChecked())
        isTaken = simpleScr->takeAndSaveScreenshot();
    else
        isTaken = simpleScr->takeScreenshot();
    if (isTaken)
        on_screenshotTaken();
}

void Dialog::takeCutScreenshot()
{
    //do something here
    if (ui->savingGroupBox->isChecked())
        cutScr->takeAndSaveScreenshot();
    else
        cutScr->takeScreenshot();
}

void Dialog::on_screenshotTaken()
{
    if (ui->notificationCheckBox->isChecked())
        trayIcon->showMessage("Уведомление", "Снимок сделан", QSystemTrayIcon::Information, 3000);
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

    trayIcon = new QSystemTrayIcon(QIcon(":/icons/camera.png"), this);
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
    cutScr = new CutScreenshot;
    cutScr->setSaver(simpleScr->getSaver());
    connect(cutScr, &CutScreenshot::screenshotTaken, this, &Dialog::on_screenshotTaken);
}

//вызывается при использовании переключателя выбора создания подкаталогов
void Dialog::changeSaverSetting(BufferSaver::SubDirSettings sett)
{
    simpleScr->getSaver().get()->setSetting(sett);
}

void Dialog::setDefaultSavePath()
{
    //не создавать если путь уже существует
    if (ui->saveFolderComboBox->count() > 0)
        return;
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    qDebug() << "Path to images: " << path;
    ui->saveFolderComboBox->addItem(path + "/Screens/");
}

void Dialog::loadSettings()
{
    settingsManager.readSettings();
    auto settings = settingsManager.getScrSetting();
    //простой снимок
    ui->simpleCheckBox->setChecked(settings.simpleScrEnabled);
    ui->simpleKeySequenceEdit->setEnabled(settings.simpleScrEnabled);
    ui->simpleKeySequenceEdit->setKeySequence(QKeySequence(settings.simpleScrKey));
    //снимок с вырезанием
    ui->cutCheckBox->setChecked(settings.cutScrEnabled);
    ui->cutKeySequenceEdit->setEnabled(settings.cutScrEnabled);
    ui->cutKeySequenceEdit->setKeySequence(QKeySequence(settings.cutScrKey));
    //сохранение в файл
    ui->savingGroupBox->setChecked(settings.savingEnabled);
    //пути сохранения
    ui->saveFolderComboBox->clear();
    for (int i = 0; i < 5; ++i) {
        QString path = settings.savePaths[i];
        if (path != "")
            ui->saveFolderComboBox->addItem(path);
    }
    //уведомления
    ui->notificationCheckBox->setChecked(settings.notificationEnabled);
    //подкаталоги
    switch (settings.subDirectoryCreation) {
    case 0:
        ui->noneRadioButton->setChecked(true); break;
    case 1:
        ui->yearRadioButton->setChecked(true); break;
    case 2:
        ui->monthRadioButton->setChecked(true); break;
    case 3:
        ui->dayRadioButton->setChecked(true);
    }
}

void Dialog::updateSettings()
{
    SettingsManager::screenshotSettings settings;
    //простой снимок
    settings.simpleScrEnabled = ui->simpleCheckBox->isChecked();
    if (ui->simpleKeySequenceEdit->keySequence().count() > 0)
        settings.simpleScrKey = ui->simpleKeySequenceEdit->keySequence()[0];
    //снимок с вырезанием
    settings.cutScrEnabled = ui->cutCheckBox->isChecked();
    if (ui->cutKeySequenceEdit->keySequence().count() > 0)
        settings.cutScrKey = ui->cutKeySequenceEdit->keySequence()[0];
    //сохранение в файл
    settings.savingEnabled = ui->savingGroupBox->isChecked();
    //пути сохранения
    int size = std::min(5, ui->saveFolderComboBox->count());
    for (int i = 0; i < size; ++i)
        settings.savePaths[i] = ui->saveFolderComboBox->itemText(i);
    //уведомления
    settings.notificationEnabled = ui->notificationCheckBox->isChecked();
    //подкаталоги
    if (ui->yearRadioButton->isChecked())
        settings.subDirectoryCreation = 1;
    else if (ui->monthRadioButton->isChecked())
        settings.subDirectoryCreation = 2;
    else if (ui->dayRadioButton->isChecked())
        settings.subDirectoryCreation = 3;
    else
        settings.subDirectoryCreation = 0;

    settingsManager.setScrSetting(settings);
    settingsManager.saveSettings();
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
    while (ui->saveFolderComboBox->count() > 5)
        ui->saveFolderComboBox->removeItem(0);
}

void Dialog::on_removeFolderPushButton_clicked()
{
    if (ui->saveFolderComboBox->count() > 0)
        ui->saveFolderComboBox->removeItem(ui->saveFolderComboBox->currentIndex());
}

void Dialog::on_saveFolderComboBox_currentTextChanged(const QString &path)
{
    std::string s = path.toStdString();
    simpleScr->setPath(s);
    qDebug() << "changing screenshot path!";
    cutScr->setPath(s);
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

void Dialog::on_monthRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::MONTH);
}

void Dialog::on_yearRadioButton_pressed()
{
    changeSaverSetting(BufferSaver::YEAR);
}



void Dialog::on_okButton_clicked()
{
    updateSettings();
    close();
}

void Dialog::on_cancelButton_clicked()
{
    loadSettings();
    close();
}
