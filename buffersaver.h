#ifndef BUFFERSAVER_H
#define BUFFERSAVER_H

#include<string>

class QImage;

class BufferSaver
{
public:
    enum SubDirSettings {NONE, YEAR, MONTH, DAY};

    BufferSaver();
    virtual ~BufferSaver();
    virtual bool saveScreenshot(const std::string& path, const std::string& name);

    SubDirSettings getSetting() const;
    void setSetting(const SubDirSettings &value);

private:
    SubDirSettings setting;
};


#endif // BUFFERSAVER_H
