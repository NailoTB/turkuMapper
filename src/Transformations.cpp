
#include "Transformations.h"

namespace Transformations
{

    PJ_CONTEXT *ctx = proj_context_create();

    const char *latLongToETRSPipeline = "+proj=pipeline +step +proj=axisswap +order=2,1 +step +proj=unitconvert +xy_in=deg +xy_out=rad +step +proj=utm +zone=35 +ellps=GRS80";
    const char *ETRSToLatLongPipeline = "+proj=pipeline +step +inv +proj=utm +zone=35 +ellps=GRS80 +step +proj=unitconvert +xy_in=rad +xy_out=deg +step +proj=axisswap +order=2,1";

    PJ *latLongToETRStransformer = proj_create(ctx, latLongToETRSPipeline);
    PJ *ETRStoLatLongTransformer = proj_create(ctx, ETRSToLatLongPipeline);

    std::pair<double, double> Transformations::transformLatLongToETRS(std::pair<double, double> latLongPair)
    {

        if (!latLongToETRStransformer)
        {
            std::cerr << "Failed to create transformation pipeline" << '\n';
        }

        PJ_COORD input_coord = proj_coord(latLongPair.first, latLongPair.second, 0, 0);
        PJ_COORD output_coord = proj_trans(latLongToETRStransformer, PJ_FWD, input_coord);

        if (proj_errno(latLongToETRStransformer))
        {
            std::cerr << "Transformation failed: " << proj_errno_string(proj_errno(latLongToETRStransformer)) << '\n';
        }

        return std::make_pair(output_coord.xy.x, output_coord.xy.y);
    }

    std::pair<double, double> Transformations::transformETRSTolatLong(std::pair<int, int> ETRSPair)
    {
        if (!ETRStoLatLongTransformer)
        {
            std::cerr << "Failed to create transformation pipeline" << '\n';
        }

        double xShifted = (ETRSPair.first + 1) * 2.0;
        double yShifted = -1.0 * (ETRSPair.second + 1) * 2.0;
        PJ_COORD input_coord = proj_coord(xShifted, yShifted, 0, 0);
        PJ_COORD output_coord = proj_trans(ETRStoLatLongTransformer, PJ_FWD, input_coord);

        if (proj_errno(ETRStoLatLongTransformer))
        {
            std::cerr << "Transformation failed: " << proj_errno_string(proj_errno(ETRStoLatLongTransformer)) << '\n';
        }

        return std::make_pair(output_coord.xy.x, output_coord.xy.y);
    }

    std::pair<int, int> Transformations::projectionToPixelCoordinates(const std::pair<double, double> &projectedCoordinates)
    {
        int pixelLongitude = (projectedCoordinates.first - 1) / 2.0;
        int pixelLatitude = -1.0 * (projectedCoordinates.second - 1) / 2.0;

        return std::make_pair(pixelLongitude, pixelLatitude);
    }
}
