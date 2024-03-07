#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "Transformations.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QToolTip>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MapScene(QGraphicsScene *parent = 0);
    void generateMarker(std::pair<double, double> latLongPair);
    void jumpTo(std::pair<double, double> latLongPair);
    void loadImagesFromFolder(const QString &folderPath);
signals:

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

private:
    QDir imagesFolder;

    std::pair<double,double> mapXBoundary;
    std::pair<double,double> mapYBoundary;
    bool coordinatesWithinBoundaries(const std::pair<int, int>& pixelCoordPair);
    QGraphicsView *mapView;
};

#endif // MAPSCENE_H
