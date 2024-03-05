#include "MapBookmarks.h"

MapBookmarks::MapBookmarks(QToolBar *parent) : QToolBar(parent)
{
    castleButton = new QPushButton("Turku Castle", this);
    kakskertaButton = new QPushButton("Kakskerta", this);

    connect(castleButton, &QPushButton::clicked, this, &MapBookmarks::jumpToCastle);
    connect(kakskertaButton, &QPushButton::clicked, this, &MapBookmarks::jumpToKakskerta);
    addWidget(castleButton);
    addWidget(kakskertaButton);
}

void MapBookmarks::jumpToCastle()
{
    double latitude = 60.435278;
    double longitude = 22.228611;

    emit jumpTo(std::make_pair(latitude, longitude));
}
void MapBookmarks::jumpToKakskerta()
{
    double latitude = 60.367042;
    double longitude = 22.211186;

    emit jumpTo(std::make_pair(latitude, longitude));
}