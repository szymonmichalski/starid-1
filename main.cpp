#include <armadillo>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    using namespace std;
    using namespace arma;

    string line;
    ifstream catfile ("../SKYMAP_SKY2000_V5R4.txt");
    if (catfile.is_open()) {
        getline(catfile,line);
        cout << line << '\n';
        catfile.close();
    } else {
        cout << "Catalog file not found." << "\n";
    }

    mat a = { {1,0} , {0,1} };
    cout << inv(a) << endl;

    return 0;
}

