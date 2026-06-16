#include "gui/alignment_worker.h"
#include "core/alignment.h"
#include "io/genbank_reader.h"

namespace pso {
namespace gui {

AlignmentWorker::AlignmentWorker() {
    dispatcher_.connect(sigc::mem_fun(*this, &AlignmentWorker::on_finished_on_main_thread));
}

AlignmentWorker::~AlignmentWorker() {
    if (thread_ && thread_->joinable())
        thread_->join();
}

void AlignmentWorker::on_finished_on_main_thread() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_.reset();
    signal_finished_();
}

void AlignmentWorker::join() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_.reset();
}

void AlignmentWorker::launch() {
    if (thread_ && thread_->joinable())
        thread_->join();
    thread_ = std::make_unique<std::thread>(&AlignmentWorker::thread_function, this);
}

sigc::signal<void>& AlignmentWorker::signal_finished() {
    return signal_finished_;
}

void AlignmentWorker::thread_function() {
    result_ = core::AlignmentResult{};

    std::string seq1 = io::load_sequence_from_genbank(file1_.c_str());
    std::string seq2 = io::load_sequence_from_genbank(file2_.c_str());

    if (seq1.empty()) {
        result_.error = "File " + file1_ + " is not a valid GenBank/sequence file.";
        dispatcher_.emit();
        return;
    }
    if (seq2.empty()) {
        result_.error = "File " + file2_ + " is not a valid GenBank/sequence file.";
        dispatcher_.emit();
        return;
    }

    result_ = core::align_sequences(seq1, seq2, population_, dimensions_, iterations_,
                                    c1_, c2_, w_, file1_, file2_);
    dispatcher_.emit();
}

}  // namespace gui
}  // namespace pso
