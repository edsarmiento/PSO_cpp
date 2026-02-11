#include "gui/main_window.h"

namespace pso {
namespace gui {

MainWindow::MainWindow()
    : lbl_title_("Use a NCBI GenBank Format File"),
      lbl_file1_("Query String:"),
      fcb_file1_("Select a sequence file"),
      lbl_file2_("Subject String:"),
      fcb_file2_("Select a sequence file"),
      btn_align_("Align"),
      lbl_population_("Population:"),
      adj_population_(Gtk::Adjustment::create(5000, 100, 100000000, 100, 1000, 0)),
      lbl_dimensions_("Dimensions:"),
      adj_dimensions_(Gtk::Adjustment::create(3, 1, 1000, 1, 10, 0)),
      lbl_iterations_("Iterations:"),
      adj_iterations_(Gtk::Adjustment::create(500, 1, 100000000, 100, 1000, 0)),
      lbl_c1_("c1:"),
      adj_c1_(Gtk::Adjustment::create(3.0, 0.1, 5.0, 0.1, 0.5, 0)),
      lbl_c2_("c2:"),
      adj_c2_(Gtk::Adjustment::create(1.0, 0.1, 5.0, 0.1, 0.5, 0)),
      lbl_w_("w:"),
      adj_w_(Gtk::Adjustment::create(0.8, 0.1, 100.0, 0.1, 0.5, 0)),
      frame_output_("Output:"),
      box_file1_(Gtk::ORIENTATION_HORIZONTAL, 0),
      box_file2_(Gtk::ORIENTATION_HORIZONTAL, 0),
      box_align_(Gtk::ORIENTATION_HORIZONTAL, 0),
      box_main_(Gtk::ORIENTATION_VERTICAL, 15) {
    worker_ = std::make_unique<AlignmentWorker>();
    setup_widgets();
    setup_file_filters();
    connect_signals();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup_widgets() {
    set_title("PSO Comparator Algorithm V2013GUI");
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(800, 600);

    lbl_title_.set_alignment(0.5f, 0.5f);
    box_main_.pack_start(lbl_title_, false, true, 0);

    lbl_file1_.set_alignment(0.0f, 0.5f);
    box_file1_.pack_start(lbl_file1_, false, false, 0);
    box_file1_.pack_start(fcb_file1_, true, true, 0);
    box_main_.pack_start(box_file1_, false, false, 0);

    lbl_file2_.set_alignment(0.0f, 0.5f);
    box_file2_.pack_start(lbl_file2_, false, false, 0);
    box_file2_.pack_start(fcb_file2_, true, true, 0);
    box_main_.pack_start(box_file2_, false, false, 0);

    box_align_.pack_start(btn_align_, true, false, 0);
    box_main_.pack_start(box_align_, false, false, 0);

    spn_population_.set_adjustment(adj_population_);
    spn_population_.set_numeric(true);
    spn_population_.set_digits(0);
    spn_population_.set_alignment(1.0f);

    spn_dimensions_.set_adjustment(adj_dimensions_);
    spn_dimensions_.set_numeric(true);
    spn_dimensions_.set_digits(0);
    spn_dimensions_.set_alignment(1.0f);
    spn_dimensions_.set_sensitive(false);

    spn_iterations_.set_adjustment(adj_iterations_);
    spn_iterations_.set_numeric(true);
    spn_iterations_.set_digits(0);
    spn_iterations_.set_alignment(1.0f);

    spn_c1_.set_adjustment(adj_c1_);
    spn_c1_.set_numeric(true);
    spn_c1_.set_digits(2);
    spn_c1_.set_alignment(1.0f);

    spn_c2_.set_adjustment(adj_c2_);
    spn_c2_.set_numeric(true);
    spn_c2_.set_digits(2);
    spn_c2_.set_alignment(1.0f);

    spn_w_.set_adjustment(adj_w_);
    spn_w_.set_numeric(true);
    spn_w_.set_digits(2);
    spn_w_.set_alignment(1.0f);

    grid_params_.set_column_spacing(5);
    grid_params_.set_row_spacing(5);
    grid_params_.attach(lbl_population_, 0, 0, 1, 1);
    grid_params_.attach(spn_population_, 1, 0, 1, 1);
    grid_params_.attach(lbl_dimensions_, 2, 0, 1, 1);
    grid_params_.attach(spn_dimensions_, 3, 0, 1, 1);
    grid_params_.attach(lbl_iterations_, 4, 0, 1, 1);
    grid_params_.attach(spn_iterations_, 5, 0, 1, 1);
    grid_params_.attach(lbl_c1_, 0, 1, 1, 1);
    grid_params_.attach(spn_c1_, 1, 1, 1, 1);
    grid_params_.attach(lbl_c2_, 2, 1, 1, 1);
    grid_params_.attach(spn_c2_, 3, 1, 1, 1);
    grid_params_.attach(lbl_w_, 4, 1, 1, 1);
    grid_params_.attach(spn_w_, 5, 1, 1, 1);
    box_main_.pack_start(grid_params_, false, true, 0);

    buffer_output_ = Gtk::TextBuffer::create();
    text_output_.set_buffer(buffer_output_);
    text_output_.override_font(Pango::FontDescription("monospace 12"));
    scroll_output_.set_margin_end(12);
    scroll_output_.add(text_output_);
    frame_output_.add(scroll_output_);
    box_main_.pack_start(frame_output_, true, true, 0);
    box_main_.pack_start(statusbar_, false, true, 0);

    add(box_main_);
}

void MainWindow::connect_signals() {
    btn_align_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_align_clicked));
    worker_->signal_finished().connect(
        sigc::bind<1>(sigc::mem_fun(*this, &MainWindow::on_alignment_finished), worker_.get()));
}

void MainWindow::setup_file_filters() {
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    fcb_file1_.add_filter(filter_text);
    fcb_file2_.add_filter(filter_text);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    fcb_file1_.add_filter(filter_any);
    fcb_file2_.add_filter(filter_any);
}

void MainWindow::on_align_clicked() {
    Glib::ustring path1 = fcb_file1_.get_filename();
    Glib::ustring path2 = fcb_file2_.get_filename();
    if (path1.empty()) {
        statusbar_.push("Select the first sequence file.");
        return;
    }
    if (path2.empty()) {
        statusbar_.push("Select the second sequence file.");
        return;
    }

    worker_->set_file1(path1.raw());
    worker_->set_file2(path2.raw());
    worker_->set_population(static_cast<int>(spn_population_.get_value()));
    worker_->set_dimensions(static_cast<int>(spn_dimensions_.get_value()));
    worker_->set_iterations(static_cast<int>(spn_iterations_.get_value()));
    worker_->set_c1(spn_c1_.get_value());
    worker_->set_c2(spn_c2_.get_value());
    worker_->set_w(spn_w_.get_value());

    statusbar_.push("Aligning...");
    worker_->launch();
}

void MainWindow::on_alignment_finished(AlignmentWorker* w) {
    if (w) {
        buffer_output_->set_text(w->get_output());
    }
    statusbar_.push("Alignment finished.");
}

}  // namespace gui
}  // namespace pso
