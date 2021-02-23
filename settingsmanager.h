#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>

class QSettings;
class QObject;

class SettingsManager
{
public:
    struct screenshotSettings {
        //включено ли захват снимков по нажатию и код ключей
        bool simpleScrEnabled = false;
        int simpleScrKey = 0;
        bool cutScrEnabled = false;
        int cutScrKey = 0;
        //включено ли сохранение в файл и пути сохранения
        bool savingEnabled = false;
        QString savePaths[5] = {"", "", "", "", ""};
        //включено ли уведомление о снимке
        bool notificationEnabled = false;
        //как создаются подкаталоги по датам
        int subDirectoryCreation = 0;
    };

    SettingsManager(QObject * parent = nullptr);
    void readSettings();
    void saveSettings();

    screenshotSettings getScrSetting() const;
    void setScrSetting(const screenshotSettings &value);

private:
    QSettings * settings;
    screenshotSettings scrSetting;
};

#endif // SETTINGSMANAGER_H
