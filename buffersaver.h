#ifndef BUFFERSAVER_H
#define BUFFERSAVER_H

#include<string>

class BufferSaver
{
public:
    BufferSaver();
    virtual ~BufferSaver();
    virtual bool saveScreenshot(const std::string& path, const std::string& name);
};

#endif // BUFFERSAVER_H
