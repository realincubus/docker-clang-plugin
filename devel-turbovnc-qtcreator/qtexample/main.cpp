#include <iostream>

using namespace std;

struct A{
    int a;
};

double dfun(){

   return 0;
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    double l[100];
    double x[100];

    for( int i = 0 ; i < 10 ; i++ ){
        l[i] = x[i];
    }


    return 0;
}
