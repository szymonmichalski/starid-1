/// *stars*
///
/// sky representation and image generation
///

#include <optionparser/optionparser.h>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include "sky.h"
#include "globals.h"
#include "triangles.h"

std::string pairsdata = "/home/noah/starid/identification/";
std::string skydata = "/home/noah/starid/stars/";
enum  optionIndex { UNKNOWN, HELP, STARS, IMAGES, TEST };

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
    {UNKNOWN, 0, "", "", option::Arg::None, "\nusage: stars [options]\n\noptions:" },
    {HELP, 0, "h", "help", option::Arg::None, "  -h, --help  \tprint usage and exit" },
    {STARS, 0, "s", "", Arg::None, "  -s  \tcreate star data files" },
    {IMAGES, 0, "m", "", Arg::None, "  -i  \tcreate images container files" },
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

    if (options[TEST]) {

    }

    if (options[STARS]) {
        starid::stopwatch stopwatch;
        starid::sky sky;
        sky.init(std::string(skydata + "skymap.txt"));
        std::ofstream os1(std::string(skydata + "sky"));
        cereal::BinaryOutputArchive oarchive1(os1);
        oarchive1(sky);

        starid::pairs pairs;
        pairs.init(starid::star_pair_angle_limit, sky);
        std::ofstream os2(std::string(pairsdata + "pairs"));
        cereal::BinaryOutputArchive oarchive2(os2);
        oarchive2(pairs);
        std::cout << "star data files " << stopwatch.end() << std::endl;
    }

    if (options[IMAGES]) {
        starid::sky sky;
        sky.init(std::string(skydata + "skymap.txt"));
    }

    return 0;
}
