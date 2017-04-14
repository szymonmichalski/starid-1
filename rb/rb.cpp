/// *rules based heuristic star identification*
///
/// given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is effectively a large noise source.
///

#include "star_identifier.h"
#include "pointing_vectors.h"
#include "sky.h"
#include "globals.h"
#include "util/stopwatch.h"
#include "util/optionparser.h"
#include "cereal/archives/binary.hpp"
#include <fstream>
#include <cmath>

std::string datadir = "/home/noah/starid/stars/data/";
std::string imgfile = "images_b1";
int imgndx = 0;
int teststar = -1;
enum  optionIndex { UNKNOWN, HELP, DATADIR, IMGFILE, IMGNDX, TESTSTAR, TEST };

struct Arg: public option::Arg {
    static void printError(const char* msg1, const option::Option& opt, const char* msg2) {
        fprintf(stderr, "ERROR: %s", msg1);
        fwrite(opt.name, opt.namelen, 1, stderr);
        fprintf(stderr, "%s", msg2);
    }
    static option::ArgStatus Required(const option::Option& option, bool msg)
    {
        if (option.arg != 0) return option::ARG_OK;
        if (msg) printError("Option '", option, "' requires an argument\n");
        return option::ARG_ILLEGAL;
    }
    static option::ArgStatus Numeric(const option::Option& option, bool msg) {
        char* endptr = 0;
        if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
        if (endptr != option.arg && *endptr == 0) return option::ARG_OK;
        if (msg) printError("Option '", option, "' requires a numeric argument\n");
        return option::ARG_ILLEGAL;
    }
};
const option::Descriptor usage[] = {
    {UNKNOWN, 0, "", "", option::Arg::None, "\nusage: rb [options]\n\noptions:" },
    {HELP, 0, "h", "help", option::Arg::None, "  -h, --help  \tprint usage and exit" },
    {DATADIR, 0, "", "datadir", Arg::Required, "  --datadir  \tdata dir" },
    {IMGFILE, 0, "", "imgfile", Arg::Required, "  --imgfile  \timage file" },
    {IMGNDX, 0, "", "imgndx", Arg::Required, "  --imgndx  \timage ndx" },
    {TESTSTAR, 0, "", "teststar", Arg::Required, "  --teststar  \ttest star ndx" },
    {TEST, 0, "t", "", Arg::None, "  -t  \ttest" },
    {0,0,0,0,0,0} // end of options
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

    if (options[DATADIR]) {
        datadir = options[DATADIR].arg;
        std::cout << "using datadir = " << datadir << std::endl;
    } else {
        std::cout << "using default datadir = " << datadir << std::endl;
    }

    if (options[IMGFILE]) {
        imgfile = options[IMGFILE].arg;
        std::cout << "using imgfile = " << imgfile << std::endl;
    } else {
        std::cout << "using default imgfile = " << imgfile << std::endl;
    }

    if (options[IMGNDX]) {
        imgndx = atoi(options[IMGNDX].arg);
        std::cout << "using imgndx = " << imgndx << std::endl;
    } else {
        std::cout << "using default imgndx = " << imgndx << std::endl;
    }

    if (options[TESTSTAR]) {
        teststar = atoi(options[TESTSTAR].arg);
        std::cout << "using test star ndx = " << teststar << std::endl;
    } else {
        std::cout << "using default test star ndx = " << teststar << std::endl;
    }

    if (options[TEST]) {
        int imgndx = 0;
        int teststar = imgndx;
        std::string datadir = "/home/noah/starid/stars/data/";
        std::string imgfile = "images_b1";
        stars::pointing_vectors image;
        std::string filename = datadir + imgfile;
        stars::image_matrix imgmat1 = image.read_image_matrix(filename, imgndx);
        stars::Sky sky;
        std::ifstream is1(std::string(datadir + "sky"));
        cereal::BinaryInputArchive iarchive1(is1);
        iarchive1(sky);
        stars::image_matrix imgmat2 = image.new_image_matrix(sky, imgndx);
        image.get_pvecs_from_imgmat(imgmat2);
        double epsilon = 0.0;
        double tolrad = (2.0 * std::sqrt(500.0*500.0 + 500.00*500.0) + epsilon) * stars::arcseconds_to_radians;
        stars::Pairs pairs;
        std::ifstream is2(std::string(datadir + "pairs"));
        cereal::BinaryInputArchive iarchive2(is2);
        iarchive2(pairs);
        rules::StarIdentifier triangles(image, pairs, tolrad);
        int starndx = triangles.identify_central_star(teststar);
        std::cout << " " << std::endl;
    }

    if (!options[TEST]) {
        util::Stopwatch stopwatch;

        stars::Sky sky;
        std::ifstream is1(std::string(datadir + "sky"));
        cereal::BinaryInputArchive iarchive1(is1);
        iarchive1(sky);

        stars::Pairs pairs;
        std::ifstream is2(std::string(datadir + "pairs"));
        cereal::BinaryInputArchive iarchive2(is2);
        iarchive2(pairs);

        stars::pointing_vectors image;
        std::string filename = datadir + imgfile;
        stars::image_matrix imgmat =image.read_image_matrix(filename, imgndx);
        image.get_pvecs_from_imgmat(imgmat);
        std::cout << "sky, pairs, image msecs = " << stopwatch.end() << std::endl;

        stopwatch.reset();
        double epsilon = 0.0; // empirical
        double tolrad = (2.0 * std::sqrt(500.0*500.0 + 500.00*500.0) + epsilon) * stars::arcseconds_to_radians;
        rules::StarIdentifier triangles(image, pairs, tolrad);
        int starndxIdentified = triangles.identify_central_star(teststar);
        std::cout << "triangles msecs = " << stopwatch.end() << std::endl;

        std::cout << "identification = " << starndxIdentified << std::endl;
    }

    return 0;
}



