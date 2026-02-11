
#include "pso.h"
#include <string>
#include <iostream>

using namespace std;

int nucleotideToInt(char n){
    switch (n){
        case 'a': return 0;
        case 't': return 1;
        case 'g': return 2;
        case 'c': return 3;
        case 's': return 4;
        case 'w': return 5;
        case 'r': return 6;
        case 'y': return 7;
        case 'k': return 8;
        case 'm': return 9;
        case 'b': return 10;
        case 'v': return 11;
        case 'h': return 12;
        case 'd': return 13;
        case 'n': return 14;
    }
}

double **getInitialPopulation(int np, int nx, double* min, double* max) {
    double** po = new double* [np];
    srand(time(0));
    for (int i = 0; i < np; i++) {
        double *elem = new double[nx];
        for (int j = 0; j < nx; j++) {
            double rango = max[j] - min[j];
            double t = drandom() * rango + min[j];
            elem[j] = t;
        }
        po[i] = elem;
    }
    return po;
}

double *deepCopy(double *v, int n) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) {
        c[i] = v[i];
    }
    return c;
}

double **deepCopy(double **m, int n, int nn) {
    double **mm = new double* [n];
    for (int i = 0; i < n; i++) {
        mm[i] = deepCopy(m[i], nn);
    }
    return mm;

}

int getBestIndex(double *f, int n) {
    double best = -1000000.0;
    double worst=-1000000.0;
    int ibest = -1;
    for (int i = 0; i < n; i++) {
        if (f[i] > best) {
            best = f[i];
            ibest = i;
        }
    }
    return ibest;
}

void deleteMatrix(double **m, int n) {
    for (int i = 0; i < n; i++) {
        delete m[i];
    }
}

void printParticula(double *p, int n, ostream &sout) {
    sout << "( " << p[0];
    for (int i = 1; i < n; i++) {
        sout << ", " << p[i];
    }
    sout << " )";
}

void printAlign(double *x, string cad1, string cad2, int limit, ostream &sout) {
    int k = (int) x[0];
    int j = (int) x[1];
    int p = 0;
    int l1 = cad1.length();
    int l2 = cad2.length();
    int len = (int) x[2];
    if (len < 0)
        len = -len;
    if (k + len > l1) len = l1 - k;
    if (j + len > l2) len = l2 - j;
    while (/*p < cad1.length() && p < cad2.length() && */ p<len) {
        for (int i = 0; i+p < len && i < limit; i++) {
            sout << cad1[k + i+p];
        }
        sout << endl;
        for (int i = 0; i+p < len && i<limit; i++) {
            char t = (cad2[j + i+p] == cad1[k + i+p]) ? '|' : '*';
            sout << t;
        }
        sout << endl;
        for (int i = 0; i+p < len && i<limit; i++) {
            sout << cad2[j + i+p];
        }
        sout << endl;
        sout << endl;
        p+=limit;
    }
}

double fitness3(double *x, string cad1, string cad2) {
    //TODO: Check this function for test all posible cases
    double s = 0;
    int k = (int) x[0];
    int j = (int) x[1];
    int len = (int) x[2];
    if (len < 0)
        len = -len;
    int l1 = cad1.length();
    int l2 = cad2.length();
    if (k + len > l1) len = l1 - k;
    if (j + len > l2) len = l2 - j;
    x[2] = len * 1.0;
    for (int i = 0; i < len; i++) {
        int ia=nucleotideToInt(cad1[k+i]);
        int ib=nucleotideToInt(cad2[j+i]);
        s+=nuc44[ia][ib];
    }
    return nuc44factor*s;
}


double *evalFitnes(double **particles, int n, double(*f)(double*, string, string), string cad1, string cad2) {
    double *fs = new double[n];
    for (int i = 0; i < n; i++) {
        fs[i] = f(particles[i], cad1, cad2);
    }
    return fs;
}


double *basicPSO(int np, int tp,
        double* min, double* max, 
        double(*f)(double*, string, string), 
        int iteraciones, double* vmin, double* vmax, 
        double w, double c1, double c2, 
        string cad1, string cad2,
        ostream &sout) {
    double **ps = getInitialPopulation(np, tp, min, max);
    double *fit = evalFitnes(ps, np, f, cad1, cad2);
    double **v = getInitialPopulation(np, tp, vmin, vmax);
    double **pBest = deepCopy(ps, np, tp);
    double *pBestFitness = deepCopy(fit, np);
    int leaderIndex = getBestIndex(fit, np);
    double *leader = deepCopy(ps[leaderIndex], tp);
    //For each iteration
    for (int i = 0; i < iteraciones; i++) {
        //For each particle
        for (int j = 0; j < np; j++) {
            //For each dimension
            for (int k = 0; k < tp; k++) {
                //PSO equation for change the velocity
                v[j][k] = w * v[j][k] + c1 * drandom()*(pBest[j][k] - ps[j][k]) + c2 * drandom()*(leader[k] - ps[j][k]);
                //Normalize the velocity
                if (v[j][k] > vmax[k]) v[j][k] = vmax[k];
                if (v[j][k] < vmin[k]) v[j][k] = vmin[k];
                //Move the particle
                ps[j][k] += v[j][k];
                //Normalize the particle
                if (ps[j][k] > max[k]) ps[j][k] = max[k];
                if (ps[j][k] < min[k]) ps[j][k] = min[k];
            }
            //Eval the particle
            fit[j] = f(ps[j], cad1, cad2);
            //Calculate the best particle
            if (fit[j] > pBestFitness[j]) {
                pBestFitness[j] = fit[j];
                delete pBest[j];
                pBest[j] = deepCopy(ps[j], tp);
            }
//            sout<<"Best for #"<<i<<" "<<j<<endl;
        }
        //Get best after iterations
        leaderIndex = getBestIndex(pBestFitness, np);
        delete leader;
        leader = deepCopy(pBest[leaderIndex], tp);
        cout<<i<<" ";
        printParticula(leader,tp,cout);
        cout<<" => "<<fitness3(leader,cad1,cad2)<<endl;
    }
    deleteMatrix(ps, np);
    delete ps;
    delete fit;
    deleteMatrix(v, np);
    delete v;
    deleteMatrix(pBest, np);
    delete pBest;
    delete pBestFitness;
//    cout<<"Returning the leader"<<endl;
    return leader;

}

void alinear(std::string cad1, std::string cad2,
        int np,int tp,int iteraciones,double c1, double c2, double w,
        std::ostream &sout) {
    double l1 = cad1.length();
    double l2 = cad2.length();
    double min[3] = {0, 0, 0};
    double max[3] = {l1*0.9, l2*0.9, ((l1 < l2) ? l1 : l2)};
//    sout << "v1: " << v1 << " v2: " << v2 << endl;
//    cout << "v1: " << v1 << " v2: " << v2 << endl;
    
    double v1 = l1 * 0.4;
    double v2 = l2 * 0.4;
//    sout << "v1: " << v1 << " v2: " << v2 << endl;
    int lm = (l1 < l2) ? l1 : l2;
    double vmin[3] = {-v1, -v2, -lm * 0.9};
    double vmax[3] = {v1, v2, lm * 0.9};
    double *p_best = basicPSO(np, tp, min, max, fitness3, iteraciones, vmin, vmax, w, c1, c2, cad1, cad2,sout);
//    basicPSO(np, tp, min, max, fitness3, iteraciones, vmin, vmax, w, c1, c2, cad1, cad2,sout);
    sout << "Best: ";
    printParticula(p_best, tp,sout);
    printParticula(p_best, tp,cout);
    sout << " => ";
    double bf =fitness3(p_best, cad1, cad2);
    sout << bf << endl;
    printAlign(p_best, cad1, cad2,70, sout);
    sout<<endl;
//    delete p_best;
}
