
#include "MapMainWindow.h"

#include <stdio.h>
#include <memory>
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MapMainWindow *mapWindow = new MapMainWindow();
    mapWindow->show();
    int execResult = app.exec();

    delete mapWindow;
    return 0;
}
