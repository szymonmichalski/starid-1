#include "mnist.h"

Eigen::Matrix<double, 28, 28> data::Mnist::readImage(std::string& imgfile, int targetimgndx) {
    Eigen::Matrix<double, 28, 28> image;
    std::ifstream file (imgfile, std::ios::binary);
    if (file.is_open())
    {
        int magnumimg, imgcnt, axjcnt, axicnt; // local variables, function is static
        file.read((char*) &magnumimg, sizeof(magnumimg));
        magnumimg = reverseInt(magnumimg);
        file.read((char*) &imgcnt, sizeof(imgcnt));
        imgcnt = reverseInt(imgcnt);
        file.read((char*) &axjcnt, sizeof(axjcnt));
        axjcnt = reverseInt(axjcnt); // 28
        file.read((char*) &axicnt, sizeof(axicnt));
        axicnt = reverseInt(axicnt); // 28

        int imgndx = 0;
        while (imgndx < targetimgndx) {
            for (int axjndx = 0; axjndx < 28; ++axjndx) { // inverted-y-like, row-like
                for (int axindx = 0; axindx < 28; ++axindx) { // x-like, col-like
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                }
            }
            ++imgndx;
        }
        // (axjndx inverted-y-like row-like), (axindx x-like col-like) plane
        for (int axjndx = 0; axjndx < 28; ++axjndx) { // inverted-y-like, row-like
            for (int axindx = 0; axindx < 28; ++axindx) { // x-like, col-like
                unsigned char temp = 0;
                file.read((char*) &temp, sizeof(temp));
                image(axjndx, axindx) = (double)temp;
            }
        }
    }
    return image;
}

void data::Mnist::writeImages(std::string filename, std::vector<arma::mat> &images) {
    std::ofstream file (filename, std::ios::binary);
    int rev_magnumimg = reverseInt(magnumimg);
    int rev_imgcnt = reverseInt(imgcnt);
    int rev_axjcnt = reverseInt(axjcnt);
    int rev_axicnt = reverseInt(axicnt);
    if (file.is_open()) {
        file.write((char*) &rev_magnumimg, sizeof(rev_magnumimg));
        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
        file.write((char*) &rev_axjcnt, sizeof(rev_axjcnt));
        file.write((char*) &rev_axicnt, sizeof(rev_axicnt));
        for (int imgndx = 0; imgndx < imgcnt; ++imgndx) {
            arma::mat image = images[imgndx];
            for (int axjndx = 0; axjndx < axjcnt; ++axjndx) {
                for(int axindx = 0; axindx < axicnt; ++axindx) {
                    unsigned char temp = (unsigned char) image(axjndx, axindx);
                    file.write((char*) &temp, sizeof(temp));
                }
            }
        }
    }
}

void data::Mnist::readImages(std::string filename, std::vector<arma::mat> &images) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open())
    {
        file.read((char*) &magnumimg, sizeof(magnumimg));
        magnumimg = reverseInt(magnumimg);
        file.read((char*) &imgcnt, sizeof(imgcnt));
        imgcnt = reverseInt(imgcnt);
        file.read((char*) &axjcnt, sizeof(axjcnt));
        axjcnt = reverseInt(axjcnt);
        file.read((char*) &axicnt, sizeof(axicnt));
        axicnt = reverseInt(axicnt);
        for(int imgndx = 0; imgndx < imgcnt; ++imgndx) {
            arma::mat image(axjcnt, axicnt);
            for(int axjndx = 0; axjndx < axjcnt; ++axjndx) {
                for(int axindx = 0; axindx < axicnt; ++axindx) {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    image(axjndx, axindx) = (double) temp;
                }
            }
            images.push_back(image);
        }
    }
}

void data::Mnist::writeLabels(std::string filename, arma::colvec &labels) {
    std::ofstream file (filename, std::ios::binary);
    int rev_magnumlab = reverseInt(magnumlab);
    int rev_imgcnt = reverseInt(imgcnt);
    if (file.is_open()) {
        file.write((char*) &rev_magnumlab, sizeof(rev_magnumlab));
        file.write((char*) &rev_imgcnt, sizeof(rev_imgcnt));
        for(int imgndx = 0; imgndx < imgcnt; ++imgndx) {
            unsigned char temp = (unsigned char) labels(imgndx);
            file.write((char*) &temp, sizeof(temp));
        }
    }
}

void data::Mnist::readLabels(std::string filename, arma::colvec &labels) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open()) {
        file.read((char*) &magnumlab, sizeof(magnumlab));
        magnumlab = reverseInt(magnumlab);
        file.read((char*) &imgcnt, sizeof(imgcnt));
        imgcnt = reverseInt(imgcnt);
        for(int imgndx = 0; imgndx < imgcnt; ++imgndx) {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            labels(imgndx)= (double) temp;
        }
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
