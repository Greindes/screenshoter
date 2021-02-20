#include "buffersaver.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QImage>
#include <QFile>
#include <QDir>
#include <ctime>

#include <QDebug>

static const QString months[] = {"Januray", "February", "March", "April", "May",
                                   "June", "July", "August", "September",
                                   "October", "Novermber", "December"};

BufferSaver::BufferSaver() : setting(NONE)
{

}

BufferSaver::~BufferSaver()
{

}

//НУЖНА ПРОВЕРКА СУЩЕСТВОВАНИЯ ПОДКАТАЛОГОВ И ИХ СОЗДАНИЕ

bool BufferSaver::saveScreenshot(const std::string &path, const std::string &name)
{
    QClipboard * clipboard = QGuiApplication::clipboard();
    QImage screen = clipboard->image();

    QString fullPath = QString::fromStdString(path);

    if (setting >= YEAR) {
        std::time_t t = std::time(nullptr);
        std::tm * curDate = std::localtime(&t);

        int year = curDate->tm_year + 1900;
        fullPath += QString::number(year) + "/";
        if (setting >= MONTH) {
            fullPath += months[curDate->tm_mon] + "/";

            if (setting >= DAY) {
                fullPath += QString::number(curDate->tm_mday) + "/";
            }
        }
    }
    qDebug() << "Path: " << fullPath << '\n';
    QDir dir(fullPath);
    dir.mkpath(fullPath);
    QFile file(fullPath + QString::fromStdString(name) + ".png");
    if (file.open(QIODevice::WriteOnly))
        return screen.save(&file, "PNG");
    return false;
}

BufferSaver::SubDirSettings BufferSaver::getSetting() const
{
    return setting;
}

void BufferSaver::setSetting(const SubDirSettings &value)
{
    setting = value;
}
