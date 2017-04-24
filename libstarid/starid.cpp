#include "starid.h"

starid::starid() {

    std::string datadir = "/home/noah/starid/stars/data/";
    std::ifstream is1(std::string(datadir + "sky"));
    cereal::BinaryInputArchive iarchive1(is1);
    iarchive1(sky);

}
