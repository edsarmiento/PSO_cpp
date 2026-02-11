#pragma once

#include <glibmm.h>
#include <glibmm/dispatcher.h>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

namespace pso {
namespace gui {

/** Worker that runs PSO alignment in a background thread and signals when done. */
class AlignmentWorker {
public:
    AlignmentWorker();
    ~AlignmentWorker();

    void launch();
    void join();

    sigc::signal<void>& signal_finished();
    std::string get_output();

    void set_file1(const std::string& path) { file1_ = path; }
    void set_file2(const std::string& path) { file2_ = path; }
    void set_population(int n) { population_ = n; }
    void set_dimensions(int n) { dimensions_ = n; }
    void set_iterations(int n) { iterations_ = n; }
    void set_c1(double x) { c1_ = x; }
    void set_c2(double x) { c2_ = x; }
    void set_w(double x) { w_ = x; }

private:
    void on_finished_on_main_thread();
    void thread_function();

    std::unique_ptr<std::thread> thread_;
    Glib::Dispatcher dispatcher_;
    std::stringstream output_;

    sigc::signal<void> signal_finished_;

    std::string file1_;
    std::string file2_;
    int population_ = 5000;
    int dimensions_ = 3;
    int iterations_ = 500;
    double c1_ = 3.0;
    double c2_ = 1.0;
    double w_ = 0.8;
};

}  // namespace gui
}  // namespace pso
