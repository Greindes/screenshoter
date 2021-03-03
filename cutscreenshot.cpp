#include "cutscreenshot.h"
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QClipboard>
#include <QGraphicsView>
#include "scene.h"


#include <QDebug>

CutScreenshot::CutScreenshot(std::string savePath) : Screenshot(savePath)
{
    scene = new Scene(this);
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    connect(scene, &Scene::screenshotTaken, view, &QWidget::close);
}

CutScreenshot::~CutScreenshot()
{
    delete view;
}

bool CutScreenshot::startTakingScreenshot()
{
    if (takingScreenshot)
        return false;
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        return false;
    takingScreenshot = true;
    QPixmap screenshot = screen->grabWindow(0);
    scene->setImg(screenshot);
    return true;
}


bool CutScreenshot::takeScreenshot()
{
    if (!startTakingScreenshot())
        return false;

    connect(scene, &Scene::screenshotTaken, this, &CutScreenshot::on_screenshotTaken);
    view->showFullScreen();
    return true;
    /*
    //Такой вариант не подходит, нужно использовать слоты/сигналы!!!
    qDebug() << "Taking cut screenshot! ";
    Scene scene(&screenshot);
    QGraphicsView * view = new QGraphicsView(&scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->connect(&scene, &Scene::screenshotTaken, view, &QWidget::close);
    view->showFullScreen();
    if (screenshot.isNull())
        return false;
    qDebug() << "Finished taking cut screenshot!";
    QGuiApplication::clipboard()->setPixmap(screenshot);
    return true;*/
}


bool CutScreenshot::takeAndSaveScreenshot(std::string name)
{
    if (!startTakingScreenshot())
        return false;

    connect(scene, &Scene::screenshotTaken, this, &CutScreenshot::on_saveScreenshotTaken);
    view->showFullScreen();
    return true;
}

void CutScreenshot::on_saveScreenshotTaken(const QPixmap &screenshot)
{
    disconnect(scene, &Scene::screenshotTaken, this, &CutScreenshot::on_saveScreenshotTaken);
    takingScreenshot = false;
    if (screenshot.isNull())
        return;

    QGuiApplication::clipboard()->setPixmap(screenshot);
    saveScreenshot();
    emit screenshotTaken();
}

void CutScreenshot::on_screenshotTaken(const QPixmap &screenshot)
{
    disconnect(scene, &Scene::screenshotTaken, this, &CutScreenshot::on_screenshotTaken);
    takingScreenshot = false;
    if (screenshot.isNull())
        return;
    QGuiApplication::clipboard()->setPixmap(screenshot);
    emit screenshotTaken();
}

