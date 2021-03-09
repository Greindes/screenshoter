#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <string>
#include <memory>
class BufferSaver;

class Screenshot
{
public:
    Screenshot(std::string savePath = "");
    virtual ~Screenshot();

    //генерирует имя для скриншота
    std::string getScreenshotNameFromDate();
    /*вызывает создание скриншота и возвращает false в случае неудачи
    (если скриншот не был сделан из-за преждевременного выхода пользователем)*/
    virtual bool takeScreenshot() = 0;
    virtual bool takeAndSaveScreenshot(std::string name = "");
    virtual void saveScreenshot(std::string name = "");

    std::string getPath() const;
    void setPath(const std::string &value);

    std::shared_ptr<BufferSaver> getSaver() const;
    void setSaver(const std::shared_ptr<BufferSaver> &value);

private:
    //путь сохранения скриншотов
    std::string path;
    //отвечает за сохранение буфера в файле
    std::shared_ptr<BufferSaver> saver;

};

#endif // SCREENSHOT_H
