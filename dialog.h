#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "buffersaver.h"
#include "settingsmanager.h"

class QSystemTrayIcon;
class QMenu;
class QHotkey;
class Screenshot;

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
private:
    Ui::Dialog *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    QAction* settingsAction;
    QAction* quitAction;

    QHotkey* simpleScrShortcut;
    QHotkey* cutScrShortcut;

    Screenshot* simpleScr;
    Screenshot* cutScr;

    SettingsManager settingsManager;
    void createActions();
    void createTrayIcon();
    void createAndConnectShortcuts();
    void createScreenshoters();
    void changeSaverSetting(BufferSaver::SubDirSettings sett);
    void setDefaultSavePath();

    void loadSettings();
    void updateSettings();
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_simpleKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence);
    void on_cutKeySequenceEdit_keySequenceChanged(const QKeySequence &keySequence);
    void on_simpleCheckBox_stateChanged(int arg1);
    void on_cutCheckBox_stateChanged(int arg1);
    void on_noneRadioButton_pressed();
    void on_saveFolderPushButton_clicked();
    void on_saveFolderComboBox_currentTextChanged(const QString &arg1);
    void on_simpleCheckBox_clicked(bool checked);
    void on_cutCheckBox_clicked(bool checked);
    void on_dayRadioButton_pressed();
    void on_monthRadioButton_pressed();
    void on_yearRadioButton_pressed();
};

#endif // DIALOG_H
