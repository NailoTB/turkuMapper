// MapMainWindow.cpp
#include "MapMainWindow.h"
MapMainWindow::MapMainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    turkuMap = new MapScene();
    setCentralWidget(turkuMap->views()[0]);

    toolbar = new MapToolBar();
    bookmarks = new MapBookmarks();
    addToolBar(toolbar);
    addToolBar(Qt::RightToolBarArea, bookmarks);

    connect(toolbar, &MapToolBar::submitPressed, this, &MapMainWindow::generateMarker);
    connect(toolbar, &MapToolBar::jumpPressed, this, &MapMainWindow::jumpTo);
    connect(bookmarks, &MapBookmarks::jumpTo, this, &MapMainWindow::jumpTo);
}

MapMainWindow::~MapMainWindow()
{
    delete turkuMap;
}

void MapMainWindow::generateMarker(std::pair<double, double> longLatPair)
{
    turkuMap->generateMarker(longLatPair);
}

void MapMainWindow::jumpTo(std::pair<double, double> longLatPair)
{
    turkuMap->jumpTo(longLatPair);
}