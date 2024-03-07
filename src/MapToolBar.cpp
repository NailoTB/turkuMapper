#include "MapToolBar.h"

MapToolBar::MapToolBar(QToolBar *parent) : QToolBar(parent)
{
    submitButton = new QPushButton("Add marker", this);
    jumpButton = new QPushButton("Jump to", this);

    longitudeLabel = new QLabel("Longitude:", this);
    latitudeLabel = new QLabel("Latitude:", this);
    longitude = new QLineEdit(this);
    latitude = new QLineEdit(this);

    addWidget(submitButton);
    addWidget(jumpButton);
    addWidget(latitudeLabel);
    addWidget(latitude);
    addWidget(longitudeLabel);
    addWidget(longitude);

    connect(submitButton, &QPushButton::clicked, this, &MapToolBar::submitButtonPressed);
    connect(jumpButton, &QPushButton::clicked, this, &MapToolBar::jumpButtonPressed);
}

void MapToolBar::submitButtonPressed()
{
    bool longitudeOk, latitudeOk;
    double longitudeValue = longitude->text().toDouble(&longitudeOk);
    double latitudeValue = latitude->text().toDouble(&latitudeOk);

    if (longitudeOk && latitudeOk)
    {
        emit submitPressed(std::make_pair(latitudeValue, longitudeValue));
    }
    else
    {
        std::cerr << "Invalid coordinates: " << latitudeValue << ' ' << longitudeValue << '\n';
    }
}
void MapToolBar::jumpButtonPressed()
{
    bool longitudeOk, latitudeOk;
    double longitudeValue = longitude->text().toDouble(&longitudeOk);
    double latitudeValue = latitude->text().toDouble(&latitudeOk);

    if (longitudeOk && latitudeOk)
    {
        emit jumpPressed(std::make_pair(latitudeValue, longitudeValue));
    }
    else
    {
        std::cerr << "Invalid coordinates: " << latitudeValue << ' ' << longitudeValue << '\n';
    }
}