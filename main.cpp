#include <QApplication>
#include "dialog.h"
#include "RunGuard.h"

int main(int argc, char *argv[])
{
    //проверка того, запущено ли уже данное приложение в другом процессоре
    RunGuard guard( "screenshoter" );
        if ( !guard.tryToRun() )
            return 0;

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    Dialog d;
    d.show();
    return app.exec();
}
