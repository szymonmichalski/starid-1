#include "sensor.h"
#include "triangles.h"
#include "mnist.h"
#include <armadillo>
#include "optionparser.h"
#include "cereal/archives/binary.hpp"
#include <fstream>
#include "stopwatch.h"

enum  optionIndex { UNKNOWN, HELP, DATADIR, SKY };
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
    {DATADIR, 0, "d", "data", Arg::Required, "  -d, --data  \tdata dir" },
    {SKY, 0, "s", "", Arg::None, "  -s  \tcreate sky and pair files" },
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

    std::string datadir = "/home/noah/dev/starid/data/";
    if (options[DATADIR]) {
        datadir = options[DATADIR].arg;
    } else {
        std::cout << "no data dir parameter - using default" << std::endl;
    }

    if (options[SKY]) {
        double mv = 6.5;
        double fov = 4.0 * arma::datum::pi / 180.0;
        util::Stopwatch stopwatch;

        stars::Sky sky;
        sky.init(std::string(datadir + "skymap.txt"), mv);
        std::ofstream os1(std::string(datadir + "sky.cereal"));
        cereal::BinaryOutputArchive oarchive1(os1);
        oarchive1(sky);

        rules::PairsOverWholeSky pairs;
        pairs.init(sky, fov);
        std::ofstream os2(std::string(datadir + "pairs.cereal"));
        cereal::BinaryOutputArchive oarchive2(os2);
        oarchive2(pairs);

        std::cout << "create sky and pairs files " << stopwatch.end() << std::endl;
    }

    return 0;
}

//    arma::arma_rng::set_seed_random();
//    std::string fsky2000    = "/home/noah/dev/starid/data/SKYMAP_SKY2000_V5R4.txt";
//    std::string f10stars    = "/home/noah/dev/starid/data/SKYMAP_10_stars.txt";
//    std::string f8876stars  = "/home/noah/dev/starid/data/SKYMAP_8876_stars.txt";
//    double mv               = 6.5;
//    double fov              = 4.0 * arma::datum::pi / 180.0;

//    if (0) { // catalog subset (800, 1600, 2400, ... 8000)
//        stars::Sky stars;
//        stars.init(fsky2000, mv);
//        std::ofstream fout1(f10stars);
//        for (int label = 0; label < 10; ++label) {
//            int starndx = 800 * (label + 1);
//            fout1 << stars.catalogLines[starndx] << std::endl;
//        }
//        fout1.close();
//        std::ofstream fout2(f8876stars);
//        for (auto it = stars.catalogLines.begin(); it != stars.catalogLines.end(); ++it) {
//            fout2 << *it << std::endl;
//        }
//        fout2.close();
//    }

//    if (0) { // generate star images in mnist format
//        int number_of_images  = 60000; // 60k for training file, 10k for test file
//        std::string fimg1    = "/home/noah/dev/starid/data/mnist_format/mnist_imagesb.mnist";
//        std::string flab1    = "/home/noah/dev/starid/data/mnist_format/mnist_labelsb.mnist";
//        std::string fimg2    = "/home/noah/dev/starid/data/mnist_format/starid_imagesb.mnist";
//        std::string flab2    = "/home/noah/dev/starid/data/mnist_format/starid_labelsb.mnist";
//        data::Mnist mnist;
//        std::vector<arma::mat> images;
//        arma::colvec labels = arma::zeros<arma::colvec>(number_of_images);
//        mnist.ReadMnistI(fimg1, images);
//        mnist.ReadMnistL(flab1, labels);
//        stars::Sensor sensor(f10stars, mv, fov);
//        for (int tenscnt = 0; tenscnt < number_of_images/10; ++tenscnt) {
//            for (int label = 0; label < 10; ++label) {
//                int starndx = 800 * (label+1);
//                arma::mat img = sensor.makeStarImage(starndx);
//                labels(10*tenscnt + label) = (double)label;
//                images[10*tenscnt + label] = img;
//                //sensor.status();
//            }
//        }
//        //mnist.WriteMnistI(fimg2, images, yaw);
//        //mnist.WriteMnistL(flab2, labels);
//    }
