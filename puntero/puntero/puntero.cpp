#include <iostream>
#include<string>
using namespace std;


int main(){
    string saludo = "hola";
    string* p = &saludo;
    cout << p << "\n";
    cout << *p << "\n";
    p = "me chupa tres pingos";
    cout << *p << "\n";
    cout << saludo << "\n";
    return 0;
}

