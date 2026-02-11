///* 
// * File:   main.cpp
// * Author: Victor Alejandro Herrera Magallanes
// *
// * Created on 29 de marzo de 2011, 21:52
// */
//
//#include <cstdlib>
//#include <vector>
//#include <iostream>
//#include "Scanner.h"
//#include <string>
//#include <time.h>
//using namespace std;
//
///*
// * 
// */
//
//double penaltyMatrix[][4]={{2,1,-1,-1},{1,2,-1,-1},{-1,-1,2,1},{-1,-1,1,2}};
//
//int nucleotideToInt(char n){
//    switch (n){
//        case 'c': return 0;
//        case 't': return 1;
//        case 'a': return 2;
//        case 'g': return 3;
//    }
//}
//
//double fitness2(double *x, string cad1, string cad2) {
//    double s = 0;
//    int k = (int) x[0];
//    int j = (int) x[1];
//    int l1 = cad1.length();
//    int l2 = cad2.length();
//    while(k<l1 && j<l2){
//        int ia=nucleotideToInt(cad1[k]);
//        int ib=nucleotideToInt(cad2[j]);
//        s+=penaltyMatrix[ia][ib];
//        k++;
//        j++;
//    }
//    return s;
//}
//
//
//
//double fitness4(double *x, string cad1, string cad2) {
//    //TODO: Check this function for test all posible cases
//    double s = 0;
//    int k = (int) x[0];
//    int j = (int) x[1];
//    int len = (int) x[2];
//    if (len < 0)
//        len = -len;
//    int l1 = cad1.length();
//    int l2 = cad2.length();
//    if (k + len > l1) len = l1 - k;
//    if (j + len > l2) len = l2 - j;
//    x[2] = len * 1.0;
//    //cout<<"Eval: "<<k<<" "<<l1<<" "<<j<<" "<<l2<<endl;
//    for (int i = 0; i < len; i++) {
//        int ia=nucleotideToInt(cad1[k+1]);
//        int ib=nucleotideToInt(cad2[j+i]);
//        s+=penaltyMatrix[ia][ib];
//    }
//    return s;
//}
//
//
//double drandom() {
//    return rand()*1.0 / RAND_MAX;
//}
//
////TODO: Delete this function
//double fitness(double *x, int n) {
//    double s = 0.0;
//    for (int i = 0; i < n; i++) {
//        double t = x[i];
//        s += t*t;
//    }
//    return -s;
//
//}
//
//double fitnes(double *x, string cad1, string cad2) {
//    double s = 0;
//    int k = (int) x[0];
//    int j = (int) x[1];
//    int len = (int) x[2];
//    if (len < 0)
//        len = -len;
//    int l1 = cad1.length();
//    int l2 = cad2.length();
//    if (k + len > l1) len = l1 - k;
//    if (j + len > l2) len = l2 - j;
//    int last = 0, now = 0;
//    int acc = 2;
//    x[2] = len * 1.0;
//    for (int i = 0; i < len; i++) {
//        now = (cad1[k + i] == cad2[j + i]) ? 1 : -1;
//        if (cad1[k + i] == cad2[j + i]) {
//            if (last == 1) {
//                acc *= 3;
//            } else
//                acc = 3;
//            s += acc;
//        } else {
//            if (last == 0) {
//                acc *= 2;
//            } else
//                acc = 2;
//            s -= acc;
//        }
//        //            s--;
//        last = now;
//        //        s+=(cad1[k+i]==cad2[j+i])?1:-1;
//    }
//    if (len > 0) s -= 4 * len;
//    return s;
//}
//
//double **getInitialPopulation(int np, int nx, double* min, double* max) {
//    double** po = new double* [np];
//    srand(time(0));
//    for (int i = 0; i < np; i++) {
//        double *elem = new double[nx];
//        for (int j = 0; j < nx; j++) {
//            double rango = max[j] - min[j];
//            double t = drandom() * rango + min[j];
//            elem[j] = t;
//        }
//        po[i] = elem;
//    }
//    return po;
//}
//
//
//
//double *deepCopy(double *v, int n) {
//    double *c = new double[n];
//    for (int i = 0; i < n; i++) {
//        c[i] = v[i];
//    }
//    return c;
//
//}
//
//double **deepCopy(double **m, int n, int nn) {
//    double **mm = new double* [n];
//    for (int i = 0; i < n; i++) {
//        mm[i] = deepCopy(m[i], nn);
//    }
//    return mm;
//
//}
//
//int getBestIndex(double *f, int n) {
//    double best = 1000000.0;
//    int ibest = -1;
//    for (int i = 0; i < n; i++) {
//        if (f[i] < best) {
//            best = f[i];
//            ibest = i;
//        }
//    }
//    return ibest;
//}
//
//void printParticula(double *p, int n) {
//    cout << "( " << p[0];
//    for (int i = 1; i < n; i++) {
//        cout << ", " << p[i];
//    }
//    cout << " )";
//
//}
//
//void deleteMatrix(double **m, int n) {
//    for (int i = 0; i < n; i++) {
//        delete m[i];
//    }
//}
//
////TODO: Edit for allow write the result in a stream
//double *basicPSO(int np, int tp, double* min, double* max, double(*f)(double*, string, string), int itera, double* vmin, double* vmax, double w, double c1, double c2, string cad1, string cad2) {
//    double **ps = getInitialPopulation(np, tp, min, max);
//    double *fit = evalFitnes(ps, np, f, cad1, cad2);
//    double **v = getInitialPopulation(np, tp, vmin, vmax);
//    double **pBest = deepCopy(ps, np, tp);
//    double *pBestFitness = deepCopy(fit, np);
//    int leaderIndex = getBestIndex(fit, np);
//    double *leader = deepCopy(ps[leaderIndex], tp);
//    //    double leaderBest=fit[leaderIndex];
//    for (int i = 0; i < itera; i++) {
//        for (int j = 0; j < np; j++) {
//            for (int k = 0; k < tp; k++) {
//        //cout<<"Iteracion #"<<i<<" "<<j<<" "<<k<<endl;
//                v[j][k] = w * v[j][k] + c1 * drandom()*(pBest[j][k] - ps[j][k]) + c2 * drandom()*(leader[k] - ps[j][k]);
//                if (v[j][k] > vmax[k]) v[j][k] = vmax[k];
//                if (v[j][k] < vmin[k]) v[j][k] = vmin[k];
//                ps[j][k] += v[j][k];
//                if (ps[j][k] > max[k]) ps[j][k] = max[k];
//                if (ps[j][k] < min[k]) ps[j][k] = min[k];
//                //cout<<"Iterado #"<<i<<" "<<j<<" "<<k<<endl;
//            }
//            //cout<<"Eval #"<<i<<" "<<j<<endl;
//            fit[j] = f(ps[j], cad1, cad2);
//            //cout<<"best for #"<<i<<" "<<j<<endl;
//            if (fit[j] > pBestFitness[j]) {
//                pBestFitness[j] = fit[j];
//                delete pBest[j];
//                pBest[j] = deepCopy(ps[j], tp);
//            }
//            //cout<<"Best for #"<<i<<" "<<j<<endl;
//        }
//        //cout<<"Getting best"<<endl;
//        leaderIndex = getBestIndex(pBestFitness, np);
//        delete leader;
//        leader = deepCopy(pBest[leaderIndex], tp);
//        //cout << i << ": ";
//        //printParticula(leader, tp);
//        //cout << " => " << f(leader, cad1, cad2) << endl;
//    }
//    deleteMatrix(ps, np);
//    delete ps;
//    delete fit;
//    deleteMatrix(v, np);
//    delete v;
//    deleteMatrix(pBest, np);
//    delete pBest;
//    delete pBestFitness;
//    return leader;
//}
//
////TODO: Delete function
//void printAlign(double *x, string cad1, string cad2, int limit) {
//    int k = (int) x[0];
//    int j = (int) x[1];
//    int p = 0;
//    int len = (int) x[2];
//    int l1 = cad1.length();
//    int l2 = cad2.length();
//    if (k + len > l1) len = l1 - k;
//    if (j + len > l2) len = l2 - j;
//    cout << k << " " << j << " " << len << endl;
//    while (/*p < cad1.length() && p < cad2.length() && */ p<len) {
//        //cout<<"P: "<<p<<endl;
//        for (int i = 0; i+p < len && i < limit; i++) {
//            cout << cad1[k + i+p];
//        }
//        cout << endl;
//        for (int i = 0; i+p < len && i<limit; i++) {
//            char t = (cad2[j + i+p] == cad1[k + i+p]) ? '|' : '*';
//            cout << t;
//        }
//        cout << endl;
//        for (int i = 0; i+p < len && i<limit; i++) {
//            cout << cad2[j + i+p];
//        }
//        cout << endl;
//        cout << endl;
//        p+=limit;
//    }
//}
//
////TODO: Real function for print, allow a stream for write in it
//void printAlign2(double *x, string cad1, string cad2, int limit) {
//    int k = (int) x[0];
//    int j = (int) x[1];
//    int p = 0;
//    int l1 = cad1.length();
//    int l2 = cad2.length();
//    cout << k << " " << j <<endl;
//    int c1=l1-k;
//    int c2=l2-j;
//    int len=(c1<c2)?c1:c2;
//    cout << k << " " << j << " " << len << endl;
//    while (/*p < cad1.length() && p < cad2.length() && */ p<len) {
//        //cout<<"P: "<<p<<endl;
//        for (int i = 0; i+p < len && i < limit; i++) {
//            cout << cad1[k + i+p];
//        }
//        cout << endl;
//        for (int i = 0; i+p < len && i<limit; i++) {
//            char t = (cad2[j + i+p] == cad1[k + i+p]) ? '|' : '*';
//            cout << t;
//        }
//        cout << endl;
//        for (int i = 0; i+p < len && i<limit; i++) {
//            cout << cad2[j + i+p];
//        }
//        cout << endl;
//        cout << endl;
//        p+=limit;
//    }
//}
//
////Change the interface, and allow configure the parameters
//int alinear(string cad1, string cad2) {
//    int np = 500;
//    int tp = 3;
//    double l1 = cad1.length();
//    double l2 = cad2.length();
//    double min[3] = {0, 0, 15};
////    double min[3] = {0, 0, ((l1 < l2) ? l1 : l2)*0.4};
//    double max[3] = {l1, l2, ((l1 < l2) ? l1 : l2)};
//    int iteraciones = 1000;
//    //    double vmin[3] = {-0.40,-0.40,-0.40};
//    //    double vmax[3] = {0.40,0.40,0.40};
//    double v1 = l1 * 0.4;
//    double v2 = l2 * 0.4;
//    cout << "v1: " << v1 << " v2: " << v2 << endl;
//    int lm = (l1 < l2) ? l1 : l2;
//
//    double vmin[3] = {-v1, -v2, -lm * 0.45};
//    double vmax[3] = {v1, v2, lm * 0.45};
//    double c1 = 1.0;
//    double c2 = 3.0;
//    double w = 1.0;
//    double *p_best = basicPSO(np, tp, min, max, fitness4, iteraciones, vmin, vmax, w, c1, c2, cad1, cad2);
//    cout << "Best: ";
//    printParticula(p_best, tp);
//    cout << " => ";
//    double bf = fitness4(p_best, cad1, cad2);
//    cout << bf << endl;
//    printAlign(p_best, cad1, cad2,70);
//    delete p_best;
//    return 0;
//}
//
//int main2(int argc, char** argv) {
//    //cout << "Args: " << argc << endl;
//    if (argc == 3) {
//        string t1 = scannADN(argv[1]);
//        string t2 = scannADN(argv[2]);
//        int l1 = t1.length();
//        int l2 = t2.length();
//        cout << "Alinear: " << l1 << " " << l2 << endl;
//        //cout<<"T1: "<<t1<<endl;
//        //cout<<"T2: "<<t2<<endl;
//        alinear(t1, t2);
//    } else {
//        string t1 = scannADN("H1N1");
//        string t2 = scannADN("vih2.txt");
//        int l1 = t1.length();
//        int l2 = t2.length();
//        alinear(t1, t2);
//    }
//}

