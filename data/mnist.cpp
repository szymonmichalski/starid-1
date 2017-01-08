#include "mnist.h"

Eigen::Matrix<double, 28, 28> data::Mnist::readImage(int imgndx) {
    Eigen::Matrix<double, 28, 28> image;
    std::ifstream file ("/home/noah/dev/starid/data/images_b1.mnist", std::ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        int i = 0;
        while (i < imgndx) {
            for(int r = 0; r < 28; ++r) {
                for(int c = 0; c < 28; ++c) {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                }
            }
            ++i;
        }
        for(int r = 0; r < 28; ++r) {
            for(int c = 0; c < 28; ++c) {
                unsigned char temp = 0;
                file.read((char*) &temp, sizeof(temp));
                image(r, c) = (double)temp;
            }
        }
    }
    return image;
}

void data::Mnist::performYaw(arma::mat &img, double a) {
    using namespace arma;
    mat rm = { {cos(a), -sin(a)}, {sin(a), cos(a)} };
    uvec ndxs = find(img); // pixel values are 0.0 to 255.0, find gives non empty, >0.0, pixels
    mat pixels(ndxs.n_rows, 3, fill::zeros);
    for (uint i = 0; i < ndxs.n_rows; ++i) {
        uvec rowcol = ind2sub(size(img), ndxs(i));
        pixels(i, 0) = rowcol(0) - 13.5;
        pixels(i, 1) = rowcol(1) - 13.5;
        pixels(i, 2) = img(ndxs(i));
    }
    pixels.cols(0,1) = trans(rm * trans(pixels.cols(0,1)));
    img.zeros();
    for (uint i = 0; i < pixels.n_rows; ++i) {
        if (pixels(i,0) <= -14.0 || pixels(i,0) >= 14.0) continue;
        if (pixels(i,1) <= -14.0 || pixels(i,1) >= 14.0) continue;
        img(floor(pixels(i,0) + 14.0), floor(pixels(i,1) + 14.0)) = pixels(i,2);
    }
}

void data::Mnist::writeMnistI(std::string filename, std::vector<arma::mat> &vec, bool yaw) {
    std::ofstream file (filename, std::ios::binary);
    int rev_magic_number = reverseInt(magic_numberi);
    int rev_imgcnt = reverseInt(imgcnt);
    int rev_rows = reverseInt(rows);
    int rev_cols = reverseInt(cols);
    if (file.is_open()) {
        file.write((char*) &rev_magic_number, sizeof(rev_magic_number));
        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
        file.write((char*) &rev_rows, sizeof(rev_rows));
        file.write((char*) &rev_cols, sizeof(rev_cols));
        for (int i = 0; i < imgcnt; ++i) {
            arma::mat img = vec[i];

            if (yaw) {
                arma::vec angle = 2.0 * arma::datum::pi * arma::randu(1);
                performYaw(img, angle(0));
            }

            for(int r = 0; r < rows; ++r) {
                for(int c = 0; c < cols; ++c) {
                    unsigned char temp = (unsigned char)img(r,c);
                    file.write((char*) &temp, sizeof(temp));
                }
            }
        }
    }
}

void data::Mnist::writeMnistL(std::string filename, arma::colvec &vec) {
    std::ofstream file (filename, std::ios::binary);
    int rev_magic_number = reverseInt(magic_numberl);
    int rev_imgcnt = reverseInt(imgcnt);
    if (file.is_open()) {
        file.write((char*) &rev_magic_number, sizeof(rev_magic_number));
        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
        for(int i = 0; i < imgcnt; ++i) {
            unsigned char temp = (unsigned char)vec(i);
            file.write((char*) &temp, sizeof(temp));
        }
    }
}

void data::Mnist::readMnistI(std::string filename, std::vector<arma::mat> &vec) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        for(int i = 0; i < number_of_images; ++i) {
            arma::mat tp(n_rows, n_cols);
            for(int r = 0; r < n_rows; ++r) {
                for(int c = 0; c < n_cols; ++c) {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    tp(r, c) = (double) temp;
                }
            }
            vec.push_back(tp);
        }
        magic_numberi = magic_number;
        rows = n_rows;
        cols = n_cols;
        imgcnt = number_of_images;
    }
}

void data::Mnist::readMnistL(std::string filename, arma::colvec &vec) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i) {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec(i)= (double)temp;
        }
        magic_numberl = magic_number;
    }
}

int data::Mnist::reverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}
