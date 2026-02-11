#pragma once

#include <gtkmm.h>
#include <memory>
#include "gui/alignment_worker.h"

namespace pso {
namespace gui {

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    ~MainWindow() override;

private:
    void connect_signals();
    void setup_widgets();
    void setup_file_filters();
    void on_align_clicked();
    void on_alignment_finished(AlignmentWorker* worker);

    std::unique_ptr<AlignmentWorker> worker_;

    Gtk::Label lbl_title_;
    Gtk::Label lbl_file1_;
    Gtk::FileChooserButton fcb_file1_;
    Gtk::Label lbl_file2_;
    Gtk::FileChooserButton fcb_file2_;
    Gtk::Button btn_align_;

    Gtk::Grid grid_params_;
    Gtk::Label lbl_population_;
    Gtk::SpinButton spn_population_;
    Glib::RefPtr<Gtk::Adjustment> adj_population_;
    Gtk::Label lbl_dimensions_;
    Gtk::SpinButton spn_dimensions_;
    Glib::RefPtr<Gtk::Adjustment> adj_dimensions_;
    Gtk::Label lbl_iterations_;
    Gtk::SpinButton spn_iterations_;
    Glib::RefPtr<Gtk::Adjustment> adj_iterations_;
    Gtk::Label lbl_c1_;
    Gtk::SpinButton spn_c1_;
    Glib::RefPtr<Gtk::Adjustment> adj_c1_;
    Gtk::Label lbl_c2_;
    Gtk::SpinButton spn_c2_;
    Glib::RefPtr<Gtk::Adjustment> adj_c2_;
    Gtk::Label lbl_w_;
    Gtk::SpinButton spn_w_;
    Glib::RefPtr<Gtk::Adjustment> adj_w_;

    Gtk::Frame frame_output_;
    Gtk::ScrolledWindow scroll_output_;
    Gtk::TextView text_output_;
    Glib::RefPtr<Gtk::TextBuffer> buffer_output_;

    Gtk::Statusbar statusbar_;

    Gtk::Box box_file1_;
    Gtk::Box box_file2_;
    Gtk::Box box_align_;
    Gtk::Box box_main_;
};

}  // namespace gui
}  // namespace pso
