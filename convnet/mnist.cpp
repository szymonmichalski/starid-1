#include "mnist.h"
#include <math.h>
#include <iostream>

int convnet::Mnist::ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void convnet::Mnist::WriteMnistI(std::string filename, std::vector<arma::mat> &vec) {
//    std::ifstream file (filename, std::ios::binary);
//    if (file.is_open())
//    {
//        int magic_number = 0;
//        int number_of_images = 0;
//        int n_rows = 0;
//        int n_cols = 0;
//        file.read((char*) &magic_number, sizeof(magic_number));
//        magic_number = ReverseInt(magic_number);
//        file.read((char*) &number_of_images,sizeof(number_of_images));
//        number_of_images = ReverseInt(number_of_images);
//        file.read((char*) &n_rows, sizeof(n_rows));
//        n_rows = ReverseInt(n_rows);
//        file.read((char*) &n_cols, sizeof(n_cols));
//        n_cols = ReverseInt(n_cols);
//        for(int i = 0; i < number_of_images; ++i) {
//            arma::mat tp(n_rows, n_cols);
//            for(int r = 0; r < n_rows; ++r) {
//                for(int c = 0; c < n_cols; ++c) {
//                    unsigned char temp = 0;
//                    file.read((char*) &temp, sizeof(temp));
//                    tp(r, c) = (double) temp;
//                }
//            }
//            vec.push_back(tp);
//        }
    }

void convnet::Mnist::WriteMnistL(std::string filename, arma::colvec &vec) {
    std::ofstream file (filename, std::ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i) {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec(i)= (double)temp;
        }
    }
}

void convnet::Mnist::ReadMnistI(std::string filename, std::vector<arma::mat> &vec) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
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

void convnet::Mnist::ReadMnistL(std::string filename, arma::colvec &vec) {
    std::ifstream file (filename, std::ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i) {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec(i)= (double)temp;
        }
        magic_numberl = magic_number;
    }
}

//int main()
//{
//    string filename1 = "mnist/t10k-images-idx3-ubyte";
//    string filename2 = "mnist/t10k-labels-idx1-ubyte";
//    int number_of_images = 10000;
//    int image_size = 28 * 28;
//    vector<arma::mat> vec1;
//    arma::colvec vec2 = arma::zeros<arma::colvec>(number_of_images);
//    read_Mnist(filename1, vec1);
//    read_Mnist_Label(filename2, vec2);
////    cout<<vec1.size()<<endl;
////    cout<<vec1[0].size()<<endl;
////    cout<<vec1[0]<<endl;
////    cout<<vec2.size()<<endl;
//    return 0;
//}
