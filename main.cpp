#include <iostream>
#include <armadillo>

int main()
{
    using namespace std;
    using namespace arma;

    cout << "Hello World!" << endl;

    mat a = { {1,0} , {0,1} };
    cout << inv(a) << endl;

    return 0;
}

