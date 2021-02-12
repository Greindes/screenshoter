#include "buffersaver.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QImage>
#include <QFile>

BufferSaver::BufferSaver()
{

}

BufferSaver::~BufferSaver()
{

}

bool BufferSaver::saveScreenshot(const std::string &path, const std::string &name)
{
    QClipboard * clipboard = QGuiApplication::clipboard();
    QImage screen = clipboard->image();
    QFile file(QString::fromStdString(path) + QString::fromStdString(name) + ".png");
    if (file.open(QIODevice::WriteOnly))
        return screen.save(&file, "PNG");
    return false;
}
