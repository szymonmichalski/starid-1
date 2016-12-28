#include "triangles_in_star_image.h"
#include "sensor.h"
#include <armadillo>
#include "optionparser.h"

enum  optionIndex { UNKNOWN, HELP, PLUS };
const option::Descriptor usage[] =
{
    {UNKNOWN, 0, "", "",option::Arg::None, "USAGE: example [options]\n\n"
     "Options:" },
    {HELP, 0,"", "help",option::Arg::None, "  --help  \tPrint usage and exit." },
    {PLUS, 0,"p","plus",option::Arg::None, "  --plus, -p  \tIncrement count." },
    {UNKNOWN, 0, "", "",option::Arg::None, "\nExamples:\n"
     "  example --unknown -- --this_is_no_option\n"
     "  example -unk --plus -ppp file1 file2\n" },
    {0,0,0,0,0,0}
};

int main(int argc, char* argv[])
{
    argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);
    if (parse.error()) return 1;
    if (options[HELP] || argc == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    std::string fcatalog   = "/home/noah/dev/starid/data/SKYMAP_8876_stars.txt";
    double mv              = 6.5; // sensor upper limit for visual magnitude
    double fov             = 4.0 * arma::datum::pi / 180.0; // sensor field of view
    uint starndx           = 800; // star to be used
    double triangles_tol   = 60 * arma::datum::pi / 648e3; // tolerance for triangle variations
    uint triangles_max     = 1e3; // upper limit for number of triangles

    // create a sensor and make a star image
    stars::Sensor sensor(fcatalog, mv, fov);
    sensor.makeStarImage(starndx);

    // create star triangles for the image and try to recognize a triangle
    triangles::TrianglesInStarImage triangles(sensor, triangles_tol, triangles_max);
    triangles.recognizeTriangleInStarImage();

    return 0;
}



