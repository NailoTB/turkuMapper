// mapMainWindow.h
#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include "MapScene.h"
#include "MapToolBar.h"
#include "MapBookmarks.h"

#include <QMainWindow>

class MapMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapMainWindow(QMainWindow *parent = 0);
    ~MapMainWindow();

private:
    MapScene *turkuMap;
    MapToolBar *toolbar;
    MapBookmarks *bookmarks;

private slots:
    void generateMarker(std::pair<double, double>);
    void jumpTo(std::pair<double, double>);
};
#endif // MAPMAINWINDOW_H