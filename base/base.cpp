#include "pointing.h"
#include "catalog.h"
#include "sensor.h"

#include <string>

int main()
{
    std::string fcatalog = "../../SKYMAP_SKY2000_V5R4.txt";
    double t = 0.0;
    double mv = 6.5;
    double fov = 4.0 * arma::datum::pi / 180.0;
    double ra = 0.0 * arma::datum::pi / 180.0;
    double dec = 60.0 * arma::datum::pi / 180.0;
    double yaw = 0.0 * arma::datum::pi / 180.0;
    base::Pointing pointing(ra, dec, yaw);

    base::Catalog catalog(fcatalog, t, mv);
    base::Sensor sensor(fov, mv);
    sensor.Update(catalog, pointing);
    sensor.Status();

    return 0;
}

