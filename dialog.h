#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QSystemTrayIcon;
class QMenu;
class QShortcut;
class Screenshot;
class BufferSaver;

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

    QShortcut* simpleScrShortcut;
    QShortcut* cutScrShortcut;

    Screenshot* simpleScr;
    Screenshot* cutScr;
    void createActions();
    void createTrayIcon();
    void createShortcuts();
    void createScreenshoters();
    void changeSaver(BufferSaver* s);

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
    void on_comboBox_currentTextChanged(const QString &arg1);
};

#endif // DIALOG_H
