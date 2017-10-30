#include "sky.h"

void starid::sky::init(std::string fcatin) {
    fcatalog = fcatin;
    t = 0.0;
    star star;

    starid::star_catalog skymapCatalog(fcatalog);
    int starndx = 0;
    for (auto rec : skymapCatalog.star_records) {
        star.starndx = starndx;
        star.skymap_number = rec.skymap_number;
        star.mv = rec.mv1;
        star.ra_degrees = 15.0 * (rec.rah + rec.ram/60.0 + rec.ras/3600.0);
        star.dec_degrees = rec.decsign * (rec.decd + rec.decm/60.0 + rec.decs/3600.0);
//        star.ra_degrees += (t * rec.pmra_arcsec_per_year) / 3600.0;
//        star.dec_degrees += (t * rec.pmdecsign * rec.pmdec_arcsec_per_year) / 3600.0;
        double ra = star.ra_degrees * starid::pi / 180.0;
        double dec = star.dec_degrees * starid::pi / 180.0;
        star.x = std::cos(ra) * std::cos(dec);
        star.y = std::sin(ra) * std::cos(dec);
        star.z = std::sin(dec);
        xtable.add_pair(star.x, starndx);
        ytable.add_pair(star.y, starndx);
        ztable.add_pair(star.z, starndx);
        stars.push_back(star);
        catalog_lines.push_back(rec.fileline);
        ++starndx;
    }
    xtable.sort();
    ytable.sort();
    ztable.sort();
}

std::vector<int> starid::sky::stars_near_point(double x, double y, double z) {
    double max_ang = 1.4 * starid::image_radius_radians;
    std::vector<int> xring = stars_in_ring(x, max_ang, xtable);
    std::vector<int> yring = stars_in_ring(y, max_ang, ytable);
    std::vector<int> zring = stars_in_ring(z, max_ang, ztable);
    std::vector<int> xy;
    std::set_intersection(xring.begin(), xring.end(), yring.begin(), yring.end(), std::back_inserter(xy));
    std::vector<int> xyz;
    std::set_intersection(xy.begin(), xy.end(), zring.begin(), zring.end(), std::back_inserter(xyz));
    std::vector<int> ndxs;
    for (uint i = 0; i < xyz.size(); ++i) {
        ndxs.push_back(xyz[i]);
    }
    return ndxs;
}

std::vector<int> starid::sky::stars_in_ring(double p, double radius, starid::float_int_table& table)
{
    double pmin, pmax;
    if (p >= cos(radius)) {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = 1.0;
    } else if (p <= -cos(radius)) {
        pmin = -1.0;
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    } else {
        pmin = p*cos(radius) - sqrt(1-(p*p))*sin(radius);
        pmax = p*cos(radius) + sqrt(1-(p*p))*sin(radius);
    }
    return table.find_ints(pmin, pmax);
}

void starid::sky::status() {
    std::cout << "number of stars " << stars.size() << "\n";
}

void starid::float_int_table::add_pair(double newFloat, int newInt)
{
    std::pair<double,int> pair {newFloat, newInt};
    float_int_table.push_back(pair);
}

void starid::float_int_table::sort()
{
    std::sort(float_int_table.begin(), float_int_table.end());
}

std::vector<int> starid::float_int_table::find_ints(double lowerFloat, double upperFloat)
{
    std::vector<int> intsFromTable;
    auto itlow = std::lower_bound(float_int_table.begin(), float_int_table.end(),
                                  std::make_pair(lowerFloat, 0));
    auto ithi = std::upper_bound(float_int_table.begin(), float_int_table.end(),
                                 std::make_pair(upperFloat, 0));
    if (itlow == ithi) {
        return intsFromTable;
    }
    for (auto it = itlow; it <= ithi; ++it) {
        auto tableRow = *it;
        intsFromTable.push_back(tableRow.second);
    }
    std::sort(intsFromTable.begin(),intsFromTable.end());
    return intsFromTable;
}

starid::star_catalog::star_catalog(std::string fcat) {
    std::ifstream catfile (fcat);
    if (catfile.is_open()) {
        std::string line;
        star_record rec;
        while (std::getline(catfile, line)) {
            try {
                try {rec.mv1 = std::stof(line.substr(232,6));} catch(...){}
                if (rec.mv1 > starid::star_brightness_limit) {
                    ++dim_stars;
                    continue;
                }
                rec.iau_identifier = line.substr(0,27);
                try {rec.star_name = line.substr(98,10);} catch(...){}
                try {rec.variablestar_name = line.substr(108,10);} catch(...){}
                rec.skymap_number = std::stoi(line.substr(27,8));
                try {rec.hd_number = std::stoi(line.substr(35,8));} catch(...){}
                try {rec.sao_number = std::stoi(line.substr(43,7));} catch(...){}
                try {rec.dm_number = std::stoi(line.substr(50,13));} catch(...){}
                try {rec.hr_number = std::stoi(line.substr(63,4));} catch(...){}
                try {rec.wds_number = std::stoi(line.substr(67,6));} catch(...){}
                try {rec.ppm_number = std::stoi(line.substr(83,7));} catch(...){}
                try {rec.blended_position = std::stoi(line.substr(146,1));} catch(...){}
                rec.rah = std::stof(line.substr(118,2));
                rec.ram = std::stof(line.substr(120,2));
                rec.ras = std::stof(line.substr(122,7));
                rec.decd = std::stof(line.substr(130,2));
                rec.decm = std::stof(line.substr(132,2));
                rec.decs = std::stof(line.substr(134,6));
                rec.pmra_arcsec_per_year = 15.0 * std::stof(line.substr(149,8));
                rec.pmdec_arcsec_per_year = std::stof(line.substr(158,7));
                rec.decsign = 1.0;
                rec.pmdecsign = 1.0;
                if (line.substr(129,1).compare("-") == 0)
                    rec.decsign = -1.0;
                if (line.substr(157,1).compare("-") == 0)
                    rec.pmdecsign = -1.0;
                rec.fileline = line;
                star_records.push_back(rec);
            } catch (...) {
            }
        }
        catfile.close();
    }
}

std::random_device r;
std::default_random_engine e1(r());
std::uniform_real_distribution<double> unitscatter(0, 1);

starid::image_matrix starid::pointing_vectors::new_image_matrix(int starndx, starid::sky &sky) {
    using namespace Eigen;
    image_matrix imgmat = image_matrix::Zero();

    Vector3d pointing;
    pointing << sky.stars[starndx].x, sky.stars[starndx].y, sky.stars[starndx].z;
    std::vector<int> starndxs = sky.stars_near_point(pointing(0), pointing(1), pointing(2));

    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    Eigen::MatrixXd ndxs = Eigen::MatrixXd::Zero(100,1);
    int pvecsndx = 0;
    for (auto ndx : starndxs) {
        pvecs.row(pvecsndx) << sky.stars[ndx].x, sky.stars[ndx].y, sky.stars[ndx].z;
        ndxs.row(pvecsndx) << ndx;
        ++pvecsndx;
    }
    pvecs.conservativeResize(pvecsndx, 3);
    Eigen::Matrix3d attitude = rotation_matrix(pointing);
    pvecs = (attitude.transpose() * pvecs.transpose()).transpose();

    double yaw = unitscatter(e1) * 2 * starid::pi;
    for (int ndx = 0; ndx < pvecsndx; ++ndx) {
        double x = std::cos(yaw) * pvecs(ndx,0) - std::sin(yaw) * pvecs(ndx,1);
        double y = std::sin(yaw) * pvecs(ndx,0) + std::cos(yaw) * pvecs(ndx,1);
        double axi = x + starid::image_radius_unit_vector_plane;
        double axj = -y + starid::image_radius_unit_vector_plane;
        int axindx = std::floor( axi / starid::image_pixel_unit_vector_plane );
        int axjndx = std::floor( axj / starid::image_pixel_unit_vector_plane );
        if (ndxs(ndx,0) == starndx) continue;
        if (axjndx < 0 || axjndx > 27) continue;
        if (axindx < 0 || axindx > 27) continue;
        imgmat(axjndx, axindx) = 1.0;
    }

    return imgmat;
}

starid::image_info starid::pointing_vectors::new_image_info(int starndx, starid::sky &sky) {
    using namespace Eigen;
    image_info imginfo = image_info::Zero(100,6);

    Vector3d pointing;
    pointing << sky.stars[starndx].x, sky.stars[starndx].y, sky.stars[starndx].z;
    std::vector<int> starndxs = sky.stars_near_point(pointing(0), pointing(1), pointing(2));

    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    Eigen::MatrixXd ndxs = Eigen::MatrixXd::Zero(100,4);
    int pvecsndx = 0;
    for (auto ndx : starndxs) {
        pvecs.row(pvecsndx) << sky.stars[ndx].x, sky.stars[ndx].y, sky.stars[ndx].z;
        ndxs.row(pvecsndx) << sky.stars[ndx].starndx, sky.stars[ndx].skymap_number, sky.stars[ndx].ra_degrees, sky.stars[ndx].dec_degrees;
        ++pvecsndx;
    }
    pvecs.conservativeResize(pvecsndx, 3);
    Eigen::Matrix3d attitude = rotation_matrix(pointing);
    pvecs = (attitude.transpose() * pvecs.transpose()).transpose();

    double yaw = unitscatter(e1) * 2 * starid::pi;
    int imginfondx = 0;
    for (int ndx = 0; ndx < pvecsndx; ++ndx) {
        double x = std::cos(yaw) * pvecs(ndx,0) - std::sin(yaw) * pvecs(ndx,1);
        double y = std::sin(yaw) * pvecs(ndx,0) + std::cos(yaw) * pvecs(ndx,1);
        double axi = x + starid::image_radius_unit_vector_plane;
        double axj = -y + starid::image_radius_unit_vector_plane;
        int axindx = std::floor( axi / starid::image_pixel_unit_vector_plane );
        int axjndx = std::floor( axj / starid::image_pixel_unit_vector_plane );
        if (ndxs(ndx,0) == starndx) continue;
        if (axjndx < 0 || axjndx > 27) continue;
        if (axindx < 0 || axindx > 27) continue;
        imginfo(imginfondx, 0) = axjndx;
        imginfo(imginfondx, 1) = axindx;
        imginfo(imginfondx, 2) = ndxs(ndx,0); // starndx
        imginfo(imginfondx, 3) = ndxs(ndx,1); // skymap_number
        imginfo(imginfondx, 4) = ndxs(ndx,2); // ra
        imginfo(imginfondx, 5) = ndxs(ndx,3); // dec
        ++imginfondx;
    }
    imginfo.conservativeResize(imginfondx, 6);

    return imginfo;
}

starid::ang_seq_vec starid::pointing_vectors::new_ang_seq_vec(int starndx, starid::sky &sky) {
    using namespace Eigen;
    ang_seq_vec angvec = ang_seq_vec::Zero();

    Vector3d pointing;
    pointing << sky.stars[starndx].x, sky.stars[starndx].y, sky.stars[starndx].z;
    std::vector<int> starndxs = sky.stars_near_point(pointing(0), pointing(1), pointing(2));

    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    Eigen::MatrixXd ndxs = Eigen::MatrixXd::Zero(100,1);
    int pvecsndx = 0;
    for (auto ndx : starndxs) {
        pvecs.row(pvecsndx) << sky.stars[ndx].x, sky.stars[ndx].y, sky.stars[ndx].z;
        ndxs.row(pvecsndx) << ndx;
        ++pvecsndx;
    }
    pvecs.conservativeResize(pvecsndx, 3);
    Eigen::Matrix3d attitude = rotation_matrix(pointing);
    pvecs = (attitude.transpose() * pvecs.transpose()).transpose();

    double yaw = unitscatter(e1) * 2 * starid::pi;
    for (int ndx = 0; ndx < pvecsndx; ++ndx) {
        double x = std::cos(yaw) * pvecs(ndx,0) - std::sin(yaw) * pvecs(ndx,1);
        double y = std::sin(yaw) * pvecs(ndx,0) + std::cos(yaw) * pvecs(ndx,1);
        double axi = x + starid::image_radius_unit_vector_plane;
        double axj = -y + starid::image_radius_unit_vector_plane;
        int axindx = std::floor( axi / starid::image_pixel_unit_vector_plane );
        int axjndx = std::floor( axj / starid::image_pixel_unit_vector_plane );
        if (ndxs(ndx,0) == starndx) continue;
        if (axindx < 0 || axindx > 27) continue;
        if (axjndx < 0 || axjndx > 27) continue;
        double pixelx = (double)axindx - 13.5;
        double pixely = 13.5 - (double)axjndx;
        if (std::sqrt(pixelx*pixelx + pixely*pixely) > 13.0) continue;
        double yawrad = std::atan2(pixely, pixelx); // yaw positive counterclock from x axis
        double yawdeg = yawrad * 180.0 / starid::pi;
        if (yawdeg < 0.0) yawdeg = 360.0 + yawdeg;
        if (yawdeg == 360.0) yawdeg = 359.9;
        int yawvecndx = std::floor(yawdeg / 10.0);
        ++angvec(yawvecndx);
    }

    return angvec;
}

Eigen::MatrixXd starid::pointing_vectors::get_pvecs_from_imgmat(starid::image_matrix &imgmat) {
    Eigen::MatrixXd pvecs = Eigen::MatrixXd::Zero(100,3);
    pvecs.row(0) << 0.0, 0.0, 1.0;
    int pvecsndx = 1;
    for (int axjndx = 0; axjndx < 28; ++axjndx) {
        for (int axindx = 0; axindx < 28; ++axindx) {
            if (imgmat(axjndx, axindx) > 0) { // there's a star inside axjndx, axindx
                double x = starid::image_pixel_unit_vector_plane * ( -13.5 + (double)axindx );
                double y = starid::image_pixel_unit_vector_plane * ( +13.5 - (double)axjndx );
                pvecs.row(pvecsndx) << x, y, std::sqrt(1 - x*x - y*y);
                ++pvecsndx;
            }
        }
    }
    pvecs.conservativeResize(pvecsndx, 3);
    return pvecs;
}

Eigen::Matrix3d starid::pointing_vectors::rotation_matrix(Eigen::Vector3d &bodyz) {
    using namespace Eigen;
    Matrix3d rm = Matrix3d::Identity(3,3);
    Vector3d icrfz(0.0, 0.0, 1.0);
    Vector3d bodyx = crossprod(bodyz, icrfz);
    Vector3d bodyy = crossprod(bodyz, bodyx);
    rm.col(0) = bodyx.normalized();
    rm.col(1) = bodyy.normalized();
    rm.col(2) = bodyz.normalized();
    return rm;
}

Eigen::Vector3d starid::pointing_vectors::crossprod(Eigen::Vector3d &u, Eigen::Vector3d &v) {
    Eigen::Vector3d result;
    result(0) = u(1)*v(2) - u(2)*v(1);
    result(1) = u(2)*v(0) - u(0)*v(2);
    result(2) = u(0)*v(1) - u(1)*v(0);
    return result;
}
