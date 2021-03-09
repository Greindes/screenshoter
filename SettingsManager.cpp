#include "SettingsManager.h"
#include <QSettings>


SettingsManager::SettingsManager(QObject *parent) :
    settings(new QSettings("PAG", "screenshoter", parent))
{
}

void SettingsManager::readSettings()
{
    settings->beginGroup("/Settings");
    //простой снимок
    scrSetting.simpleScrEnabled = settings->value("/simpleScrEnabled", false).toBool();
    scrSetting.simpleScrKey = settings->value("/simpleScrKey", 0).toInt();
    //снимок с вырезанием
    scrSetting.cutScrEnabled = settings->value("/cutScrEnabled", false).toBool();
    scrSetting.cutScrKey = settings->value("/cutScrKey", 0).toInt();
    //сохранение в файл
    scrSetting.savingEnabled = settings->value("/savingEnabled", false).toBool();
    //Пути сохранения
    for (int i = 0; i < 5; ++i)
        scrSetting.savePaths[i] = settings->value("/savePath_" + QString::number(i), "").toString();
    //уведомление
    scrSetting.notificationEnabled = settings->value("/notificationEnabled", false).toBool();
    //подкаталоги
    scrSetting.subDirectoryCreation = settings->value("/subDirectoryCreation", 0).toInt();

    settings->endGroup();
}

void SettingsManager::saveSettings()
{
    settings->beginGroup("/Settings");
    //простой снимок
    settings->setValue("/simpleScrEnabled", scrSetting.simpleScrEnabled);
    settings->setValue("/simpleScrKey", scrSetting.simpleScrKey);
    //снимок с вырезанием
    settings->setValue("/cutScrEnabled", scrSetting.cutScrEnabled);
    settings->setValue("/cutScrKey", scrSetting.cutScrKey);
    //сохранение в файл
    settings->setValue("/savingEnabled", scrSetting.savingEnabled);
    //Пути сохранения
    for (int i = 0; i < 5; ++i)
        settings->setValue("/savePath_" + QString::number(i), scrSetting.savePaths[i]);
    //уведомление
    settings->setValue("/notificationEnabled", scrSetting.notificationEnabled);
    //подкаталоги
    settings->setValue("/subDirectoryCreation", scrSetting.subDirectoryCreation);

    settings->endGroup();
}

SettingsManager::screenshotSettings SettingsManager::getScrSetting() const
{
    return scrSetting;
}

void SettingsManager::setScrSetting(const screenshotSettings &value)
{
    scrSetting = value;
}

