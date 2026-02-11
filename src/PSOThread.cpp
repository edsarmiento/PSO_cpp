#include <glibmm.h>
#include "PSOThread.h"
#include "Scanner.h"
#include "pso.h"

PSOThread::PSOThread() : thread_(nullptr), sout(std::ios::in | std::ios::out) {
    dispatcher_.connect(sigc::mem_fun(*this, &PSOThread::on_finished_from_main_thread));
}

PSOThread::~PSOThread() {
    if (thread_ && thread_->joinable())
        thread_->join();
}

void PSOThread::on_finished_from_main_thread() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_.reset();
    signal_finished_();
}

void PSOThread::join() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_.reset();
}

void PSOThread::launch() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_ = std::make_unique<std::thread>(&PSOThread::thread_function, this);
}

sigc::signal<void>& PSOThread::signal_finished()
{
  return signal_finished_;
}

void PSOThread::thread_function() {
    std::string t1 = scannADN(file1.data());
    std::string t2 = scannADN(file2.data());
    if (t1.length() == 0) {
        sout << "File " << file1 << " is not a valid ADN file." << std::endl;
        dispatcher_.emit();
        return;
    }
    if (t2.length() == 0) {
        sout << "File " << file2 << " is not a valid ADN file." << std::endl;
        dispatcher_.emit();
        return;
    }
    alinear(t1, t2, population, dimensions, iterations, c1, c2, w, sout);
    sout.flush();
    dispatcher_.emit();
}

std::string PSOThread::get_output(){
    std::string output(sout.str());
    return output;
}