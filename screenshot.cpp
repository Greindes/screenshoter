#include "screenshot.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include "buffersaver.h"

Screenshot::Screenshot(std::string savePath) : path(savePath)
{

}

Screenshot::~Screenshot()
{

}

bool Screenshot::takeAndSaveScreenshot(std::string name)
{
    if (!takeScreenshot())
        return false;
    saveScreenshot(name);
    return true;
}

void Screenshot::saveScreenshot(std::string name)
{
    if (name == "")
        name = getScreenshotNameFromDate();
    //передай сохранение BufferSaver с именем файла и пути
    if (saver)
        saver->saveScreenshot(path, name);
}



std::string Screenshot::getPath() const
{
    return path;
}

void Screenshot::setPath(const std::string &value)
{
    path = value;
}

BufferSaver *Screenshot::getSaver() const
{
    return saver;
}

void Screenshot::setSaver(BufferSaver *value)
{
    saver = value;
}

//Генерирует строку в формате YYYY-MM-DD HH MM SS
std::string Screenshot::getScreenshotNameFromDate()
{
    std::string name;
    std::time_t t = std::time(nullptr);
    std::tm * curDate = std::localtime(&t);
    std::stringstream ss;
    ss << std::setfill('0');
    ss << (curDate->tm_year + 1900) << '-' << std::setw(2) << curDate->tm_mon << '-'
          << std::setw(2) << curDate->tm_mday << " " << std::setw(2) << curDate->tm_hour
          << ' ' << std::setw(2) << curDate->tm_min << ' ' << std::setw(2) << curDate->tm_sec;
    name = ss.str();
    return name;
}
