// Transformations.h

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "proj.h"
#include <utility>
#include <cerrno>
#include <iostream>
#include <cstring> 
namespace Transformations
{
    std::pair<int, int> projectionToPixelCoordinates(const std::pair<double, double> &projectedCoordinates);;
    std::pair<double, double> transformLatLongToETRS(std::pair<double, double> latLongPair);
    std::pair<double, double> transformETRSTolatLong(std::pair<int, int> ETRSPair);
}

#endif // TRANSFORMATIONS_H
