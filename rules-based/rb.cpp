#include "triangles.h"
#include "image.h"
#include "stopwatch.h"
#include <armadillo>
#include "optionparser.h"
#include "cereal/archives/binary.hpp"
#include <fstream>
#include <cmath>

std::string datadir = "/home/noah/dev/starid/data/";
std::string imgfile = "images_b1.mnist";
int imgndx = 0;

enum  optionIndex { UNKNOWN, HELP, DATADIR, IMGFILE, IMGNDX };
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
    } else {
        std::cout << "using default datadir " << datadir << std::endl;
    }
    if (options[IMGFILE]) {
        imgfile = options[IMGFILE].arg;
    } else {
        std::cout << "using default imgfile " << imgfile << std::endl;
    }
    if (options[IMGNDX]) {
        imgndx = atoi(options[IMGNDX].arg);
    } else {
        std::cout << "using default imgndx " << imgndx << std::endl;
    }

    util::Stopwatch stopwatch;
    stars::Sky sky;
    std::ifstream is1(std::string(datadir + "sky.cereal"));
    cereal::BinaryInputArchive iarchive1(is1);
    iarchive1(sky);
    rules::PairsOverWholeSky pairs;
    std::ifstream is2(std::string(datadir + "pairs.cereal"));
    cereal::BinaryInputArchive iarchive2(is2);
    iarchive2(pairs);
    stars::Image image;
    std::string filename = datadir + imgfile;
    image.axjAxiImageReadMnist(filename, imgndx);
    std::cout << "sky, pairs, image " << stopwatch.end() << std::endl;

    stopwatch.reset();
    double triTolRadius = (500.0 / 648000.0) * M_PI;
    int triMaxCnt = 1000;
    rules::Triangles triangles(image, pairs, triTolRadius, triMaxCnt);
    int starndxIdentified = triangles.identifyCentralStar();
    std::cout << "triangles " << stopwatch.end() << std::endl;

    std::cout << "identification " << starndxIdentified << std::endl;

    return 0;
}



