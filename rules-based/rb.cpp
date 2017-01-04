#include "triangles.h"
#include "sensor.h"
#include "stopwatch.h"
#include <armadillo>
#include "optionparser.h"
#include "cereal/archives/binary.hpp"
#include <fstream>

enum  optionIndex { UNKNOWN, HELP, STARNDX, FPAIRS };
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
    {UNKNOWN, 0, "", "", option::Arg::None, "\nusage: example [options]\n\noptions:" },
    {HELP, 0, "h", "help", option::Arg::None, "  -h, --help  \tprint usage and exit" },
    {STARNDX, 0, "s", "starndx", Arg::Numeric, "  -s, --starndx  \tstarndx" },
    {FPAIRS, 0, "p", "pairs", Arg::Required, "  -p, --pairs  \tpairs file" },
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

    std::string fcatalog    = "/home/noah/dev/starid/data/skymap_8876.txt";
    double mv               = 6.5; // sensor upper limit for visual magnitude
    double fov              = 4.0 * arma::datum::pi / 180.0; // sensor field of view
    double triangles_tol    = 100 * arma::datum::pi / 648e3; // tolerance for triangle variations
    int triangles_max       = 100; // upper limit for number of triangles
    int starndxTrue         = 0;
    if (options[STARNDX]) starndxTrue = atoi(options[STARNDX].arg);

    util::Stopwatch stopwatch;
    stars::Sensor sensor(fcatalog, mv, fov);
    sensor.makeStarImage(starndxTrue);
    std::cout << "sensor " << stopwatch.end() << std::endl;

    stopwatch.reset();
    rules::PairsOverWholeSky pairs;
    if (options[FPAIRS]) {
        std::fstream fs(options[FPAIRS].arg);
        cereal::BinaryInputArchive iarchive(fs);
        iarchive(pairs);
    } else {
        pairs.init(sensor);
        std::ofstream os("/home/noah/dev/starid/data/pairs.bin");
        cereal::BinaryOutputArchive oarchive(os);
        oarchive(pairs);
    }
    std::cout << "pairs " << stopwatch.end() << std::endl;

    stopwatch.reset();
    rules::Triangles triangles(sensor, pairs, triangles_tol, triangles_max);
    int starndxIdentified = triangles.identifyCentralStar();
    std::cout << "triangles " << stopwatch.end() << std::endl;

    std::cout << "identification " << starndxIdentified << std::endl;

    return 0;
}



