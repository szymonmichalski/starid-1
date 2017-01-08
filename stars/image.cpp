#include "image.h"

void stars::Image::useMnistImage(int imgndx) {

    Eigen::Matrix<double, 28, 28> image = data::Mnist::readImage(imgndx);

    double fov = 4.0 * arma::datum::pi / 180.0;

    uvecs.zeros(100,3);
    int uvecsndx = 0;
    for(int r = 0; r < 28; ++r) {
        for(int c = 0; c < 28; ++c) {
            if (image(r,c) > 0) {
                double h = fov * (r - 14.0) / 14.0;
                double v = fov * (c - 14.0) / 14.0;
                double x = tan(h);
                double y = tan(v);
                double z = 1.0;
                double len = std::sqrt( x*x + y*y + z*z );
                uvecs(uvecsndx,0) = x/len;
                uvecs(uvecsndx,1) = y/len;
                uvecs(uvecsndx,2) = z/len;
                ++uvecsndx;
            }
        }
    }
    uvecs.shed_rows(uvecsndx, 99);
}




//    l1_hv.col(0) = arma::atan(l1_uvec.col(0) / l1_uvec.col(2));
//    l1_hv.col(1) = arma::atan(l1_uvec.col(1) / l1_uvec.col(2));
//        int row = 14 + floor(14 * l1_hv(i,0) / fov);
//        int col = 14 + floor(14 * l1_hv(i,1) / fov);


//stars::Sensor::Sensor(std::string fcatalog, double mv, double fov)
//    : mv(mv), fov(fov)
//{
//    sky.init(fcatalog, mv);
//    noise = 5.0;
//    ra = 0.0 * arma::datum::pi / 180.0;
//    dec = 0.0 * arma::datum::pi / 180.0;
//    yaw = 0.0 * arma::datum::pi / 180.0;
//    pointing.set_size(3);
//    pointing(0) = std::cos(ra) * std::cos(dec);
//    pointing(1) = std::sin(ra) * std::cos(dec);
//    pointing(2) = std::sin(dec);
//    pointing = arma::normalise(pointing);
//}

//arma::mat stars::Sensor::makeStarImage(uint starndx) {
//    using namespace arma;
//    pointing.set_size(3);
//    pointing(0) = sky.stars[starndx].x;
//    pointing(1) = sky.stars[starndx].y;
//    pointing(2) = sky.stars[starndx].z;
//    starsvec_ndxs = sky.starsNearPoint(pointing(0), pointing(1), pointing(2), fov);

//    l1_uvec.set_size(starsvec_ndxs.size(),3);
//    l1_hv.set_size(starsvec_ndxs.size(),2);
//    l1_starndx.set_size(starsvec_ndxs.size());
//    l1_mag.set_size(starsvec_ndxs.size());

//    for (uint i = 0; i < starsvec_ndxs.size(); ++i) {
//        l1_uvec(i,0) = sky.stars[starsvec_ndxs[i]].x;
//        l1_uvec(i,1) = sky.stars[starsvec_ndxs[i]].y;
//        l1_uvec(i,2) = sky.stars[starsvec_ndxs[i]].z;
//        l1_starndx(i) = starsvec_ndxs[i];
//        l1_mag(i) = sky.stars[starsvec_ndxs[i]].mv1;
//    }
//    l1_uvec = trans(trans(stars::Sensor::rotationMatrix(pointing)) * trans(l1_uvec));
//    l1_hv.col(0) = arma::atan(l1_uvec.col(0) / l1_uvec.col(2));
//    l1_hv.col(1) = arma::atan(l1_uvec.col(1) / l1_uvec.col(2));

//    mat img(28, 28, fill::zeros);
//    for (uint i = 0; i < l1_hv.n_rows; ++i) {
//        int row = 14 + floor(14 * l1_hv(i,0) / fov);
//        int col = 14 + floor(14 * l1_hv(i,1) / fov);
//        if (row < 0 || row > 27) continue;
//        if (col < 0 || col > 27) continue;
//        img(row, col) = 255.0;
//    }
//    //    std::cout << img << "\n";

//    return img;
//}

//void stars::Sensor::status() {
//    using namespace arma;
//    mat tmp1 = l1_uvec;
//    mat tmp2 = 14 + floor(14 * l1_hv / fov);
//    tmp1.insert_cols(3, tmp2);
//    tmp1.insert_cols(5, l1_starndx);
//    tmp1.insert_cols(6, l1_mag);
//    std::cout << tmp1 << "\n";
//}

//arma::mat stars::Sensor::rotationMatrix(arma::vec& pointing, double yaw) {
//    arma::mat rm;
//    rm.eye(3,3);
//    arma::vec bz = pointing;
//    arma::vec iz = { 0.0, 0.0, 1.0 };
//    arma::vec b1x = arma::cross(bz,iz);
//    b1x = arma::normalise(b1x);
//    arma::vec b1y = arma::cross(bz,b1x);
//    b1y = arma::normalise(b1y);
//    arma::vec bx = std::cos(yaw) * b1x + std::sin(yaw) * b1y;
//    arma::vec by = std::sin(yaw) * b1x + std::cos(yaw) * b1y;
//    rm.col(0) = arma::normalise(bx);
//    rm.col(1) = arma::normalise(by);
//    rm.col(2) = bz;
//    double err = std::abs(arma::det(rm) - 1.0);
//    assert(err < 1e-10);
//    return rm;
//}

//double stars::Sensor::sgn(double x) { // nonstandard signum return +1 for 0
//    if (x >= 0.0) return 1.0;
//    if (x < 0.0) return -1.0;
//    return 1.0;
//}

//arma::vec stars::Sensor::rm2q(arma::mat& rm) {
//    arma::vec q { 0.0, 0.0, 0.0, 1.0 };
//    q(0) = 0.5 * sqrt(1.0 + rm(0,0) - rm(1,1) - rm(2,2)) * sgn( rm(1,2)-rm(2,1) );
//    q(1) = 0.5 * sqrt(1.0 - rm(0,0) + rm(1,1) - rm(2,2)) * sgn( rm(2,0)-rm(0,2) );
//    q(2) = 0.5 * sqrt(1.0 - rm(0,0) - rm(1,1) + rm(2,2)) * sgn( rm(0,1)-rm(1,0) );
//    q(3) = 0.5 * sqrt(1.0 + rm(0,0) + rm(1,1) + rm(2,2));
//    q = arma::normalise(q);
//    if (q(3) < 0.0) q = -q;
//    return q;
//}

//arma::vec stars::Sensor::quaternion(arma::vec& pointing, double yaw = 0) {
//    arma::mat rm = rotationMatrix(pointing, yaw);
//    arma::vec q;
//    q.set_size(4);
//    q = rm2q(rm);
//    q = arma::normalise(q);
//    assert(arma::norm(q) == 1.0);
//    return q;
//}

//arma::vec stars::Sensor::qmult(arma::vec& q1, arma::vec& q2) {
//    arma::vec q3 {
//        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
//        -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
//        q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
//        -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
//    };
//    q3 = arma::normalise(q3);
//    if (q3(3) < 0.0) q3 = -q3;
//    return q3;
//}

//arma::vec stars::Sensor::qconj(arma::vec& q) {
//    arma::vec q2 { -q(0), -q(1), -q(2), q(3) };
//    return q2;
//}

//arma::vec stars::Sensor::rv2q(arma::vec& rv) {
//    arma::vec q { rv(0)/2, rv(1)/2, rv(2)/2, 1 };
//    q = arma::normalise(q);
//    if (q(3) < 0.0) q = -q;
//    return q;
//}

//arma::vec stars::Sensor::q2rv(arma::vec& q) {
//    arma::vec rv { 2*q(0), 2*q(1), 2*q(2) };
//    return rv;
//}

//arma::vec stars::Sensor::qdif2rv(arma::vec& q1, arma::vec& q2a) {
//    arma::vec q2 { -q2a(0), -q2a(1), -q2a(2), q2a(3) };
//    arma::vec q3 {
//        q1(0)*q2(3) + q1(1)*q2(2) + -q1(2)*q2(1) + q1(3)*q2(0),
//        -q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0) + q1(3)*q2(1),
//        q1(0)*q2(1) + -q1(1)*q2(0) + q1(2)*q2(3) + q1(3)*q2(2),
//        -q1(0)*q2(0) + -q1(1)*q2(1) + -q1(2)*q2(2) + q1(3)*q2(3)
//    };
//    q3 = arma::normalise(q3);
//    if ( q3(3) < 0 ) { q3 = -q3; }
//    arma::vec rv { 2.0*q3(0), 2.0*q3(1), 2.0*q3(2) };
//    return rv;
//}

//arma::mat stars::Sensor::q2rm(arma::vec& q) {
//    arma::mat rm(3,3);
//    rm(0,0) =  q(0)*q(0) - q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
//    rm(0,1) = 2.0*( q(0)*q(1) + q(2)*q(3) );
//    rm(0,2) = 2.0*( q(0)*q(2) - q(1)*q(3) );
//    rm(1,0) = 2.0*( q(0)*q(1) - q(2)*q(3) );
//    rm(1,1) = -q(0)*q(0) + q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
//    rm(1,2) = 2.0*( q(1)*q(2) + q(0)*q(3) );
//    rm(2,0) = 2.0*( q(0)*q(2) + q(1)*q(3) );
//    rm(2,1) = 2.0*( q(1)*q(2) - q(0)*q(3) );
//    rm(2,2) = -q(0)*q(0) - q(1)*q(1) + q(2)*q(2) + q(3)*q(3);
//    return rm;
//}

//void stars::Sensor::MakeL1b() {
//    using namespace arma;
//    l1b.starsvec_ndxs = l1a.starsvec_ndxs;
//    l1b.mag = l1a.mag;

//    mat hvnoise = (noise * datum::pi / 6.48e5) * randn(l1a.hv.n_rows, l1a.hv.n_cols);
//    l1b.hv = l1a.hv + hvnoise;

//    // handle false stars in hv space
//    vec nfalsevec = false_stars_mean + (false_stars_stdv * arma::randn(1));
//    int nfalse = std::round(nfalsevec(0));
//    if (nfalse > 0) {
//        uint ntrue = l1b.hv.n_rows;
//        l1b.hv.resize(ntrue + nfalse, l1b.hv.n_cols);
//        for (uint i = 1; i <= nfalse; ++i) {
//            l1b.starsvec_ndxs.push_back(-1);
//            l1b.mag.push_back(-1.0);
//            vec hvrand = ((randu(2) * 2.0) - 1.0) * fov;
//            l1b.hv.row(ntrue - 1 + i) = trans(hvrand);
//        }
//    }

//    // generate pointing vector from hv space
//    mat z(l1b.hv.n_rows, 1, fill::ones);
//    l1b.uvec = l1b.hv;
//    l1b.uvec.insert_cols(2, z);
//    normalise(l1b.uvec, 2, 1);
//}

//void stars::Sensor::MakeL2a() {
//    using namespace arma;

//    // rotate so the nearest star is on the v axis
//    vec d = arma::sqrt(l1a.hv.col(0)%l1a.hv.col(0) + l1a.hv.col(1)%l1a.hv.col(1));
//    uvecec starsvec_ndxs2 = arma::sort_index(d);
//    double h = l1a.hv(starsvec_ndxs2(0),0);
//    double v = l1a.hv(starsvec_ndxs2(0),1);
//    double a = std::atan2(h,v); // angle from v axis
//    mat hv2 = l1a.hv;
//    mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
//    hv2 = trans(rm * trans(hv2));

//    l2a.pattern.zeros(28,28);
//    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
//        try {
//            int h1 = 14 + floor(14 * hv2(i,0) / fov);
//            int v1 = 14 + floor(14 * hv2(i,1) / fov);
//            l2a.pattern(h1,v1) = 1.0;
//        } catch (...) {
//            bool outofbounds = true;
//        }
//    }
//    l2a.fv = arma::vectorise(l2a.pattern);
//}

//void stars::Sensor::MakeL2b() {
//    using namespace arma;

//    // rotate so the nearest star is on the v axis
//    vec d = arma::sqrt(l1b.hv.col(0)%l1b.hv.col(0) + l1b.hv.col(1)%l1b.hv.col(1));
//    uvecec starsvec_ndxs2 = arma::sort_index(d);
//    double h = l1b.hv(starsvec_ndxs2(0),0);
//    double v = l1b.hv(starsvec_ndxs2(0),1);
//    double a = std::atan2(h,v); // angle from v axis
//    mat hv2 = l1b.hv;
//    mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
//    hv2 = trans(rm * trans(hv2));

//    l2b.pattern.zeros(28,28);
//    for (uint i = 0; i <= hv2.n_rows-1; ++i) {
//        try {
//            int h1 = 14 + floor(14 * hv2(i,0) / fov);
//            int v1 = 14 + floor(14 * hv2(i,1) / fov);
//            l2b.pattern(h1,v1) = 1.0;
//        } catch (...) {
//            bool outofbounds = true;
//        }
//    }
//    l2b.fv = arma::vectorise(l2b.pattern);
//}
