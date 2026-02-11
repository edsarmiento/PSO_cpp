
#include "fileManagement.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;

std::string loadfile(char* filename) {
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
                adn = true;
            }
            if (adn) {
                if (str.find("//") != string::npos) {
                    break;
                }
                stringstream sin(ios::out | ios::in);
                sin << str;
                sin >> p;
                while (sin.getline(tadn, 20, ' ')) {
                    sout << tadn;
                }
            }
        }
        k++;
    }
    fin.close();
    string f = sout.str();
    return f;
}


//TODO: load next parameters:
/*
 * PoblationSize
Iteraciones
V1
V2
C1
C2
W

 */
std::map<std::string, double> loadConfiguration(char* filename) {
    std::map<std::string, double> config;
    fstream fin;
    fin.open(filename, ios::in);
    char *temp = new char[100];
    char key[50];
    double val;
    while (fin.getline(temp, 100)) {
        stringstream sin(ios::out | ios::in);
        sin << temp;
        sin>>key;
        sin>>val;
        config[key]=val;
    }
    return config;
}