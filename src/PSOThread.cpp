
#include <glibmm.h>
#include "PSOThread.h"
#include "Scanner.h"
#include "pso.h"

PSOThread::PSOThread():thread_(0),sout(std::ios::in|std::ios::out){
    
}

PSOThread::~PSOThread(){
    // It is an error if the thread is still running at this point.
  g_return_if_fail(thread_ == 0);
}


void PSOThread::join(){
    thread_->join();
    thread_=0;
}

void PSOThread::launch(){
    // Create a joinable thread.
  thread_ = Glib::Thread::create(sigc::mem_fun(*this, &PSOThread::thread_function), true);
}

sigc::signal<void>& PSOThread::signal_finished()
{
  return signal_finished_;
}

void PSOThread::thread_function()
{
//    sout.str("");
    std::string t1 = scannADN(file1.data());
    std::string t2 = scannADN(file2.data());
    if(t1.length()==0){
        sout<<"File "<<file1<<" is not a valid ADN file."<<std::endl;
        signal_finished_();
        return;
    }
    if(t2.length()==0){
        sout<<"File "<<file2<<" is not a valid ADN file."<<std::endl;
        signal_finished_();
        return;
    }    
    alinear(t1,t2,population,dimensions,iterations,c1,c2,w,sout);
    sout.flush();
    thread_=0;
    signal_finished_();
//    std::cout<<"signal_finished_()"<<std::endl;
}

std::string PSOThread::get_output(){
    std::string output(sout.str());
    return output;
}