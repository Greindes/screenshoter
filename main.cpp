#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*SimpleScreenshot scr("D:/Screens/");
    BufferSaver bs;
    scr.setSaver(&bs);
    scr.takeAndSaveScreenshot();*/
    Dialog d;
    d.show();
    return app.exec();
}
