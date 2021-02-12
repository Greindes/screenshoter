#include "simplescreenshot.h"
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QClipboard>

SimpleScreenshot::SimpleScreenshot(std::string savePath) : Screenshot(savePath)
{

}


bool SimpleScreenshot::takeScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        return false;
    QPixmap screenshot = screen->grabWindow(0);
    QGuiApplication::clipboard()->setPixmap(screenshot);
    return true;
}
