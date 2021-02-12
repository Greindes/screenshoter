#ifndef SIMPLESCREENSHOT_H
#define SIMPLESCREENSHOT_H

#include "screenshot.h"

//скриншот представляет собой снимок экрана
class SimpleScreenshot : public Screenshot
{
public:
    SimpleScreenshot(std::string savePath = "");

    // Screenshot interface
public:
    virtual bool takeScreenshot() override;
};

#endif // SIMPLESCREENSHOT_H
