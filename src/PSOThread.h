/* 
 * File:   PSOThread.h
 * Author: alejandro
 *
 * Created on February 25, 2012, 1:41 PM
 */

#ifndef PSOTHREAD_H
#define	PSOTHREAD_H

#include <glibmm.h>
#include <glibmm/dispatcher.h>
#include <sstream>
#include <string>
#include <thread>
#include <memory>

class PSOThread {
public:
    explicit PSOThread();
    virtual ~PSOThread();

    void launch();
    void join();

    sigc::signal<void>& signal_finished();
    std::string get_output();
    
    void set_file1(std::string f1){this->file1=f1;}
    void set_file2(std::string f2){this->file2=f2;}
    void set_population(int population){this->population=population;}
    void set_dimensions(int dimensions){this->dimensions=dimensions;}
    void set_iterations(int iterations){this->iterations=iterations;}
    void set_c1(double c1){this->c1=c1;}
    void set_c2(double c2){this->c2=c2;}
    void set_w(double w){this->w=w;}
    
private:
    void on_finished_from_main_thread();

    std::unique_ptr<std::thread> thread_;
    Glib::Dispatcher dispatcher_;
    std::stringstream sout;

    sigc::signal<void> signal_finished_;

    std::string file1;
    std::string file2;
    
    int population;
    int dimensions;
    int iterations;
    double c1;
    double c2;
    double w;
    
    
    void progress_increment();
    void thread_function();
};


#endif	/* PSOTHREAD_H */

