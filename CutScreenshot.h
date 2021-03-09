#ifndef CUTSCREENSHOT_H
#define CUTSCREENSHOT_H

#include <QObject>
#include "Screenshot.h"

class QPixmap;
class QGraphicsView;
class Scene;

class CutScreenshot : public QObject, public Screenshot
{
    Q_OBJECT
public:
    CutScreenshot(std::string savePath = "");
    virtual ~CutScreenshot() override;
    // Screenshot interface
public:
    bool startTakingScreenshot();
    virtual bool takeScreenshot() override;
    virtual bool takeAndSaveScreenshot(std::string name = "") override;

private:
    bool takingScreenshot = false;
    Scene * scene;
    QGraphicsView * view;
    void prepareView();
public slots:
    void on_saveScreenshotTaken(const QPixmap& screenshot);
    void on_screenshotTaken(const QPixmap& screenshot);

signals:
    void screenshotTaken();


};

#endif // CUTSCREENSHOT_H
