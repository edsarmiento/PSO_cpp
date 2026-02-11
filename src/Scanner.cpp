#include<fstream>
#include<sstream>
#include <string>

#include<iostream>
using namespace std;

string scannADN(const char* filename) {
    fstream fin;
    fin.open(filename, ios::in);
    char *temp = new char[100];
    char *tadn = new char[100];
    stringstream sout;
    int p;
    int k = 0;
    bool adn = false;
    while (fin.getline(temp, 100)) {
        string str(temp);
        if (!str.empty()) {
            if (str.find("ORIGIN") != string::npos) {
//                cout<<"Origin"<<endl;
                adn = true;
            }
            if (adn) {
                if (str.find("//") != string::npos) {
                    break;
                }
                stringstream sin(ios::out | ios::in);
                sin << str;
                sin >> p;
                while (sin.getline(tadn,20,' ')) {
                    sout << tadn;
                }
//                cout << sout.str() << endl;
            }
        }
        k++;
    }
    fin.close();
    string f=sout.str();
    return f;
}

