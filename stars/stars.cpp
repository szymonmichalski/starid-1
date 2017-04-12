/// **stars**
///
/// sky representation and image generation
///
#include "image.h"
#include "pairs.h"

#include "util/stopwatch.h"
#include "util/optionparser.h"
#include "cereal/archives/binary.hpp"
#include <fstream>


std::string datadir = "/home/noah/starid/stars/data/";
void doMnist(int, std::string&, std::string&, stars::Sky&);

enum  optionIndex { UNKNOWN, HELP, DATADIR, SKY, MNIST, TEST };
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
    {DATADIR, 0, "d", "data", Arg::Required, "  -d, --data  \tdata dir" },
    {SKY, 0, "s", "", Arg::None, "  -s  \tcreate sky and pair files" },
    {MNIST, 0, "m", "", Arg::None, "  -m  \tcreate mnist files" },
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
    } else {
        std::cout << "using default datadir " << datadir << std::endl;
    }

    if (options[TEST]) {
        std::string datadir = "/home/noah/starid/stars/data/";
        std::string imgfile = "images_b1.mnist";
        int imgndx = 0;
        stars::Image image;
        std::string filename = datadir + imgfile;
        image.axjAxiImageReadMnist(filename, imgndx);
        std::cout << " " << std::endl;
    }

    if (options[SKY]) {
        util::Stopwatch stopwatch;
        stars::Sky sky;
        sky.init(std::string(datadir + "skymap.txt"));
        std::ofstream os1(std::string(datadir + "sky.cereal"));
        cereal::BinaryOutputArchive oarchive1(os1);
        oarchive1(sky);

        stars::Pairs pairs;
        pairs.init(stars::star_pair_angle_limit, sky);
        std::ofstream os2(std::string(datadir + "pairs.cereal"));
        cereal::BinaryOutputArchive oarchive2(os2);
        oarchive2(pairs);
        std::cout << "sky and pairs " << stopwatch.end() << std::endl;
    }

    if (options[MNIST]) {
        stars::Sky sky;
        sky.init(std::string(datadir + "skymap.txt"));
        std::string a = "images_a";
        std::string b = "images_b";
        doMnist(60000, datadir, a, sky);
        doMnist(10000, datadir, b, sky);
    }

    return 0;
}

void doMnist(int imgCnt, std::string& datadir, std::string& filename, stars::Sky& sky) {
//    data::Mnist mnist;
//    std::vector<arma::mat> axjAxiImages;
//    arma::colvec labels = arma::zeros<arma::colvec>(imgCnt);
//    mnist.readAxjAxiImages(std::string(datadir + filename + "1.mnist"), axjAxiImages); // 28x28ximgCnt images
//    mnist.readLabels(std::string(datadir + filename + "2.mnist"), labels); // imageCntx1 labels
//    for (int starSetNdx = 0; starSetNdx < imgCnt/10; ++starSetNdx) {
//        for (int starndx = 0; starndx < 10; ++starndx) {
//            arma::mat axjAxiImage = axjAxiImages[10*starSetNdx + starndx]; // get current image
//            stars::Image image;
//            image.axjAxiImageUpdate(axjAxiImage, sky, starndx);
//            labels(10*starSetNdx + starndx) = (double) starndx; // update current label
//            axjAxiImages[10*starSetNdx + starndx] = axjAxiImage; // update current image
//        }
//    }
//    mnist.writeImages(std::string(datadir + filename + "1.mnist"), axjAxiImages);
//    mnist.writeLabels(std::string(datadir + filename + "2.mnist"), labels);
}
