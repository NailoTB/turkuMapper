#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "proj.h"

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
    std::pair<int, int> projectionToPixelCoordinates(const std::pair<double, double> &projectedCoordinates);;
    QGraphicsView *mapView;
    std::pair<double, double> transformLatLongToETRS(std::pair<double, double> latLongPair);
    std::pair<double, double> transformETRSTolatLong(std::pair<int, int> ETRSPair);
};

#endif // MAPSCENE_H
