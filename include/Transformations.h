// Transformations.h

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "proj.h"
#include <utility>
#include <iostream>
#include <cstring> 

namespace Transformations
{
    std::pair<double, double> transformLatLongToETRS(std::pair<double, double> &latLongPair);
    std::pair<double, double> transformPixelCoordinatesTolatLong(std::pair<int, int> &pixelCoordinates);
    
    std::pair<double, double> pixelCoordinatesToMapCoordinates(const std::pair<int, int> &pixelCoordinates);
    std::pair<int, int> mapCoordinatesToPixelCoordinates(const std::pair<double, double> &projectedCoordinates);;

}

#endif // TRANSFORMATIONS_H
