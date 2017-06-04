/// *rules based heuristic star identification*
///
/// given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is effectively a large noise source.
///

#include "sky.h"
#include "globals.h"
#include "triangles.h"
#include <optionparser/optionparser.h>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include <cmath>

std::string pairsdata = "/home/noah/starid/identification/";
std::string skydata = "/home/noah/starid/star/";
int starndx = 0;
int teststar = -1;
enum  optionIndex { UNKNOWN, HELP, STARNDX, TESTSTAR, TEST };

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
    {STARNDX, 0, "", "starndx", Arg::Required, "  --starndx  \timage ndx" },
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

    if (options[STARNDX]) {
        starndx = atoi(options[STARNDX].arg);
        std::cout << "using starndx = " << starndx << std::endl;
    } else {
        std::cout << "using default starndx = " << starndx << std::endl;
    }

    if (options[TESTSTAR]) {
        teststar = atoi(options[TESTSTAR].arg);
        std::cout << "using test star ndx = " << teststar << std::endl;
    } else {
        std::cout << "using default test star ndx = " << teststar << std::endl;
    }

    if (options[TEST]) {
        starid::sky sky;
        std::ifstream is1(std::string(skydata + "sky"));
        cereal::BinaryInputArchive iarchive1(is1);
        iarchive1(sky);
        starid::pairs pairs;
        std::ifstream is2(std::string(pairsdata + "pairs"));
        cereal::BinaryInputArchive iarchive2(is2);
        iarchive2(pairs);

        starid::image_matrix imgmat = starid::pointing_vectors::new_image_matrix(starndx, sky);
        starid::triangles ider(imgmat, pairs);
        int result = ider.id();
        std::cout << result << std::endl;
    }

    if (!options[TEST]) {
        starid::stopwatch stopwatch;
        starid::sky sky;
        std::ifstream is1(std::string(skydata + "sky"));
        cereal::BinaryInputArchive iarchive1(is1);
        iarchive1(sky);
        starid::pairs pairs;
        std::ifstream is2(std::string(pairsdata + "pairs"));
        cereal::BinaryInputArchive iarchive2(is2);
        iarchive2(pairs);
        starid::image_matrix imgmat = starid::pointing_vectors::new_image_matrix(starndx, sky);
        std::cout << "sky, pairs, image msecs = " << stopwatch.end() << std::endl;

        stopwatch.reset();
        starid::triangles ider(imgmat, pairs);
        int result = ider.id(teststar);
        std::cout << "triangles msecs = " << stopwatch.end() << std::endl;

        std::cout << "identification = " << result << std::endl;
    }

    return 0;
}



