#pragma once

#include <gtkmm.h>
#include <memory>
#include "core/alignment_result.h"
#include "gui/alignment_worker.h"

namespace pso {
namespace gui {

class PsoHistoryColumns : public Gtk::TreeModel::ColumnRecord {
public:
    PsoHistoryColumns() {
        add(col_iteration);
        add(col_k);
        add(col_j);
        add(col_len);
        add(col_fitness);
    }

    Gtk::TreeModelColumn<int> col_iteration;
    Gtk::TreeModelColumn<Glib::ustring> col_k;
    Gtk::TreeModelColumn<Glib::ustring> col_j;
    Gtk::TreeModelColumn<Glib::ustring> col_len;
    Gtk::TreeModelColumn<Glib::ustring> col_fitness;
};

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    ~MainWindow() override;

private:
    void connect_signals();
    void setup_widgets();
    void setup_menubar();
    void setup_output_notebook();
    void setup_file_filters();
    void on_align_clicked();
    void on_credits_activated();
    void on_alignment_finished(AlignmentWorker* worker);
    void show_result(const core::AlignmentResult& result);
    void clear_results();
    void clear_summary_grid();
    void add_summary_row(int row, const Glib::ustring& field, const Glib::ustring& meaning,
                         const Glib::ustring& value);

    std::unique_ptr<AlignmentWorker> worker_;

    Gtk::Frame frame_input_;
    Gtk::Box box_files_;
    Gtk::Label lbl_file1_;
    Gtk::FileChooserButton fcb_file1_;
    Gtk::Label lbl_file2_;
    Gtk::FileChooserButton fcb_file2_;
    Gtk::Button btn_align_;

    Gtk::Frame frame_params_;
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
    Gtk::Notebook notebook_output_;
    Gtk::ScrolledWindow scroll_summary_;
    Gtk::ScrolledWindow scroll_history_;
    Gtk::ScrolledWindow scroll_alignment_;
    Gtk::Grid grid_summary_;
    Gtk::TreeView tree_history_;
    Gtk::TextView text_alignment_;
    Glib::RefPtr<Gtk::TextBuffer> buffer_alignment_;
    PsoHistoryColumns history_columns_;
    Glib::RefPtr<Gtk::ListStore> history_store_;

    Gtk::Label lbl_status_;

    Gtk::MenuBar menubar_;
    Gtk::MenuItem menuitem_credits_;

    Gtk::Box box_root_;
    Gtk::Box box_columns_;
    Gtk::Box box_left_;
    Gtk::Box box_right_;
    Gtk::Box box_align_;
    Gtk::Box box_main_;
};

}  // namespace gui
}  // namespace pso
