#pragma once

#include <glibmm.h>
#include <glibmm/dispatcher.h>
#include <memory>
#include <string>
#include <thread>

#include "core/alignment_result.h"

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
    const core::AlignmentResult& get_result() const { return result_; }

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

    sigc::signal<void> signal_finished_;
    core::AlignmentResult result_;

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
