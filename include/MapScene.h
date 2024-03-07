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
#include <QTimer>
class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MapScene(QGraphicsScene *parent = 0);
    void generateMarker(std::pair<double, double> &latLongPair);
    void jumpTo(std::pair<double, double> &latLongPair);
    void loadImagesFromFolder(const QString &folderPath);
signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

private:
    QDir imagesFolder;
    QGraphicsView *mapView;

    std::pair<int,int> mapXBoundary;
    std::pair<int,int> mapYBoundary;
    bool coordinatesWithinBoundaries(const std::pair<int, int>& pixelCoordPair);
};

#endif // MAPSCENE_H
