// MapScene.cpp
#include "MapScene.h"

PJ_CONTEXT *ctx = proj_context_create();

const char *latLongToETRSPipeline = "+proj=pipeline +step +proj=axisswap +order=2,1 +step +proj=unitconvert +xy_in=deg +xy_out=rad +step +proj=utm +zone=35 +ellps=GRS80";
const char *ETRSToLatLongPipeline = "+proj=pipeline +step +inv +proj=utm +zone=35 +ellps=GRS80 +step +proj=unitconvert +xy_in=rad +xy_out=deg +step +proj=axisswap +order=2,1";

PJ *latLongToETRStransformer = proj_create(ctx, latLongToETRSPipeline);
PJ *ETRStoLatLongTransformer = proj_create(ctx, ETRSToLatLongPipeline);

MapScene::MapScene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    mapView = new QGraphicsView(this);
    mapView->setFixedSize(800, 600);
    mapView->setMouseTracking(true);

    imagesFolder.setPath("tileset/");
    loadImagesFromFolder(imagesFolder.absolutePath());
}

std::pair<double, double> MapScene::transformLatLongToETRS(std::pair<double, double> latLongPair)
{

    if (!latLongToETRStransformer)
    {
        qDebug() << "Failed to create transformation pipeline\n";
    }

    PJ_COORD input_coord = proj_coord(latLongPair.first, latLongPair.second, 0, 0);
    PJ_COORD output_coord = proj_trans(latLongToETRStransformer, PJ_FWD, input_coord);

    if (proj_errno(latLongToETRStransformer))
    {
        qDebug() << "Transformation failed: " << proj_errno_string(proj_errno(latLongToETRStransformer)) << '\n';
    }

    return std::make_pair(output_coord.xy.x, output_coord.xy.y);
}

std::pair<double, double> MapScene::transformETRSTolatLong(std::pair<int, int> ETRSPair)
{
    if (!ETRStoLatLongTransformer)
    {
        qDebug() << "Failed to create transformation pipeline\n";
    }

    double xShifted = (ETRSPair.first + 1) * 2.0;
    double yShifted = -1.0 * (ETRSPair.second + 1) * 2.0;
    PJ_COORD input_coord = proj_coord(xShifted, yShifted, 0, 0);
    PJ_COORD output_coord = proj_trans(ETRStoLatLongTransformer, PJ_FWD, input_coord);

    if (proj_errno(ETRStoLatLongTransformer))
    {
        qDebug() << "Transformation failed: " << proj_errno_string(proj_errno(ETRStoLatLongTransformer)) << '\n';
    }

    return std::make_pair(output_coord.xy.x, output_coord.xy.y);
}

std::pair<int, int> MapScene::projectionToPixelCoordinates(const std::pair<double, double> &projectedCoordinates)
{
    int pixelLongitude = (projectedCoordinates.first - 1) / 2.0;
    int pixelLatitude = -1.0 * (projectedCoordinates.second - 1) / 2.0;

    return std::make_pair(pixelLongitude, pixelLatitude);
}

bool MapScene::coordinatesWithinBoundaries(const std::pair<int, int> &pixelCoordinates)
{
    bool withinX = pixelCoordinates.first < mapXBoundary.second && pixelCoordinates.first > mapYBoundary.first;
    bool withinY = pixelCoordinates.second < mapYBoundary.second && pixelCoordinates.second > mapYBoundary.first;
    return withinX && withinY;
}

void MapScene::generateMarker(std::pair<double, double> latLongPair)
{
    double markerSize = 10.0;
    double markerOffset = markerSize / 2.0;

    std::pair<double, double> ETRSPair = transformLatLongToETRS(latLongPair);
    std::pair<int, int> pixelCoordinates = projectionToPixelCoordinates(ETRSPair);

    if (coordinatesWithinBoundaries(pixelCoordinates))
    {
        QGraphicsEllipseItem *redCircle = new QGraphicsEllipseItem(pixelCoordinates.first - markerOffset, pixelCoordinates.second - markerOffset, markerSize, markerSize); // Adjust the position and size of the circle as needed
        redCircle->setBrush(Qt::red);
        addItem(redCircle);
        jumpTo(latLongPair);
    }
    else
    {
        qDebug() << "Bruh";
    }
}

void MapScene::jumpTo(std::pair<double, double> latLongPair)

{
    std::pair<double, double> ETRSPair = transformLatLongToETRS(latLongPair);
    std::pair<int, int> pixelCoordinates = projectionToPixelCoordinates(ETRSPair);
    if (coordinatesWithinBoundaries(pixelCoordinates))
    {
        mapView->centerOn(pixelCoordinates.first, pixelCoordinates.second);
    }
}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QPointF mousePos = event->scenePos();
    std::pair<int, int> pixelCoordinates = std::make_pair(mousePos.x(), mousePos.y());
    auto latLong = transformETRSTolatLong(pixelCoordinates);

    QString tooltipText = QString("(%1, %2)").arg(latLong.first).arg(latLong.second);

    QToolTip::showText(QCursor::pos(), tooltipText, mapView);
}

void MapScene::loadImagesFromFolder(const QString &folderPath)
{
    QStringList filters;
    filters << "*.png";
    imagesFolder.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    imagesFolder.setNameFilters(filters);

    QStringList images = imagesFolder.entryList();
    qDebug() << "Loading map tiles... ";
    std::vector<double> xCoordinates, yCoordinates;

    for (const QString &imageName : images)
    {
        QString dataFile = imageName.left(imageName.length() - 4) + ".pgw";

        QFile file(folderPath + "/" + dataFile);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Error opening file:" << file.errorString();
            return;
        }

        QTextStream in(&file);
        QStringList lines;

        while (!in.atEnd())
        {
            QString line = in.readLine();

            lines.append(line);
        }

        auto pixelSize = lines[0].toDouble();
        auto xCoordinate = (lines[lines.size() - 2].toDouble() - 1) / pixelSize;  // make sure that this doesn't go bonkers
        auto yCoordinate = -(lines[lines.size() - 1].toDouble() - 1) / pixelSize; // change to int

        xCoordinates.push_back(xCoordinate);
        yCoordinates.push_back(yCoordinate);

        QPixmap pixmap(folderPath + "/" + imageName);
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
        pixmapItem->setPos(xCoordinate, yCoordinate);
        addItem(pixmapItem);
    }
    std::sort(xCoordinates.begin(), xCoordinates.end());
    std::sort(yCoordinates.begin(), yCoordinates.end());

    xCoordinates.erase(std::unique(xCoordinates.begin(), xCoordinates.end()), xCoordinates.end());
    yCoordinates.erase(std::unique(yCoordinates.begin(), yCoordinates.end()), yCoordinates.end());

    int xExtent = xCoordinates[1] - xCoordinates[0];
    int yExtent = yCoordinates[1] - yCoordinates[0];

    mapXBoundary.first = xCoordinates[0];
    mapXBoundary.second = xCoordinates[xCoordinates.size() - 1] + xExtent;
    mapYBoundary.first = yCoordinates[0];
    mapYBoundary.second = yCoordinates[yCoordinates.size() - 1] + yExtent;

    qDebug() << mapXBoundary;
    qDebug() << mapYBoundary;
    qDebug() << "Loading complete!";
}