#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "BufferSaver.h"
#include "SettingsManager.h"

class QSystemTrayIcon;
class QMenu;
class QHotkey;
class Screenshot;
class CutScreenshot;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void takeSimpleScreenshot();
    void takeCutScreenshot();
    void on_screenshotTaken();
private:
    Ui::Dialog *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    QAction* settingsAction;
    QAction* quitAction;

    QHotkey* simpleScrShortcut;
    QHotkey* cutScrShortcut;

    Screenshot* simpleScr;
    CutScreenshot* cutScr;

    SettingsManager settingsManager;
    void createActions();
    void createTrayIcon();
    void createAndConnectShortcuts();
    void createScreenshoters();
    void changeSaverSetting(BufferSaver::SubDirSettings sett);
    void setDefaultSavePath();

    void loadSettings();
    void updateSettings();
private slots:
    void on_simpleKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence);
    void on_cutKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence);
    void on_noneRadioButton_pressed();
    void on_saveFolderPushButton_clicked();
    void on_saveFolderComboBox_currentTextChanged(const QString &arg1);
    void on_simpleCheckBox_clicked(bool checked);
    void on_cutCheckBox_clicked(bool checked);
    void on_dayRadioButton_pressed();
    void on_monthRadioButton_pressed();
    void on_yearRadioButton_pressed();
    void on_removeFolderPushButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // DIALOG_H
