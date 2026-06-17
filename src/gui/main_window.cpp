#include "gui/main_window.h"

#include <iomanip>
#include <sstream>

namespace pso {
namespace gui {

namespace {

Glib::ustring format_double(double value, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

Glib::ustring basename(const std::string& path) {
    const std::size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos)
        return path;
    return path.substr(pos + 1);
}

}  // namespace

MainWindow::MainWindow()
    : lbl_file1_("Query String:"),
      fcb_file1_("Select a sequence file"),
      lbl_file2_("Subject String:"),
      fcb_file2_("Select a sequence file"),
      btn_align_("Align"),
      lbl_status_(""),
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
      frame_input_("Use a NCBI GenBank Format File"),
      box_files_(Gtk::ORIENTATION_VERTICAL, 8),
      frame_params_("PSO Parameters"),
      frame_output_("Results:"),
      box_columns_(Gtk::ORIENTATION_HORIZONTAL, 16),
      box_left_(Gtk::ORIENTATION_VERTICAL, 10),
      box_right_(Gtk::ORIENTATION_VERTICAL, 10),
      history_store_(Gtk::ListStore::create(history_columns_)) {
    worker_ = std::make_unique<AlignmentWorker>();
    setup_widgets();
    setup_output_notebook();
    setup_file_filters();
    connect_signals();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup_widgets() {
    set_title("PSO Comparator Algorithm V2013GUI");
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(950, 650);

    box_main_.set_margin_start(12);
    box_main_.set_margin_end(12);
    box_main_.set_margin_top(10);
    box_main_.set_margin_bottom(8);
    box_main_.set_spacing(8);

    box_columns_.set_hexpand(true);
    box_columns_.set_vexpand(true);

    box_left_.set_size_request(340, -1);
    box_left_.set_valign(Gtk::ALIGN_START);

    box_right_.set_hexpand(true);
    box_right_.set_vexpand(true);
    box_right_.set_spacing(10);

    box_files_.set_margin_start(12);
    box_files_.set_margin_end(12);
    box_files_.set_margin_top(10);
    box_files_.set_margin_bottom(10);

    lbl_file1_.set_halign(Gtk::ALIGN_START);
    lbl_file1_.set_xalign(0.0);
    lbl_file2_.set_halign(Gtk::ALIGN_START);
    lbl_file2_.set_xalign(0.0);

    fcb_file1_.set_hexpand(true);
    fcb_file1_.set_halign(Gtk::ALIGN_FILL);
    fcb_file2_.set_hexpand(true);
    fcb_file2_.set_halign(Gtk::ALIGN_FILL);

    box_files_.pack_start(lbl_file1_, false, false, 0);
    box_files_.pack_start(fcb_file1_, false, true, 0);
    box_files_.pack_start(lbl_file2_, false, false, 0);
    box_files_.pack_start(fcb_file2_, false, true, 0);

    frame_input_.add(box_files_);
    box_left_.pack_start(frame_input_, false, true, 0);

    box_align_.set_halign(Gtk::ALIGN_CENTER);
    btn_align_.set_halign(Gtk::ALIGN_CENTER);
    btn_align_.set_margin_top(8);
    btn_align_.set_margin_bottom(4);
    box_align_.pack_start(btn_align_, false, false, 0);
    box_left_.pack_start(box_align_, false, false, 0);

    lbl_status_.set_halign(Gtk::ALIGN_CENTER);
    lbl_status_.set_margin_top(4);
    lbl_status_.set_margin_bottom(4);
    box_left_.pack_start(lbl_status_, false, false, 0);

    box_columns_.pack_start(box_left_, false, true, 0);

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

    grid_params_.set_column_spacing(10);
    grid_params_.set_row_spacing(8);
    grid_params_.set_margin_start(12);
    grid_params_.set_margin_end(12);
    grid_params_.set_margin_top(10);
    grid_params_.set_margin_bottom(10);
    grid_params_.attach(lbl_population_, 0, 0, 1, 1);
    grid_params_.attach(spn_population_, 1, 0, 1, 1);
    grid_params_.attach(lbl_dimensions_, 0, 1, 1, 1);
    grid_params_.attach(spn_dimensions_, 1, 1, 1, 1);
    grid_params_.attach(lbl_iterations_, 0, 2, 1, 1);
    grid_params_.attach(spn_iterations_, 1, 2, 1, 1);
    grid_params_.attach(lbl_c1_, 0, 3, 1, 1);
    grid_params_.attach(spn_c1_, 1, 3, 1, 1);
    grid_params_.attach(lbl_c2_, 0, 4, 1, 1);
    grid_params_.attach(spn_c2_, 1, 4, 1, 1);
    grid_params_.attach(lbl_w_, 0, 5, 1, 1);
    grid_params_.attach(spn_w_, 1, 5, 1, 1);

    lbl_population_.set_halign(Gtk::ALIGN_START);
    lbl_dimensions_.set_halign(Gtk::ALIGN_START);
    lbl_iterations_.set_halign(Gtk::ALIGN_START);
    lbl_c1_.set_halign(Gtk::ALIGN_START);
    lbl_c2_.set_halign(Gtk::ALIGN_START);
    lbl_w_.set_halign(Gtk::ALIGN_START);
    spn_population_.set_hexpand(true);
    spn_population_.set_halign(Gtk::ALIGN_FILL);
    spn_dimensions_.set_hexpand(true);
    spn_dimensions_.set_halign(Gtk::ALIGN_FILL);
    spn_iterations_.set_hexpand(true);
    spn_iterations_.set_halign(Gtk::ALIGN_FILL);
    spn_c1_.set_hexpand(true);
    spn_c1_.set_halign(Gtk::ALIGN_FILL);
    spn_c2_.set_hexpand(true);
    spn_c2_.set_halign(Gtk::ALIGN_FILL);
    spn_w_.set_hexpand(true);
    spn_w_.set_halign(Gtk::ALIGN_FILL);

    frame_params_.add(grid_params_);
    box_right_.pack_start(frame_params_, false, true, 0);

    frame_output_.add(notebook_output_);
    frame_output_.set_vexpand(true);
    box_right_.pack_start(frame_output_, true, true, 0);

    box_columns_.pack_start(box_right_, true, true, 0);
    box_main_.pack_start(box_columns_, true, true, 0);

    add(box_main_);
}

void MainWindow::setup_output_notebook() {
    grid_summary_.set_column_spacing(12);
    grid_summary_.set_row_spacing(6);
    grid_summary_.set_margin_start(12);
    grid_summary_.set_margin_end(12);
    grid_summary_.set_margin_top(12);
    grid_summary_.set_margin_bottom(12);

    scroll_summary_.add(grid_summary_);
    scroll_summary_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    notebook_output_.append_page(scroll_summary_, "Summary");

    tree_history_.set_model(history_store_);
    tree_history_.append_column("Iter", history_columns_.col_iteration);
    tree_history_.append_column("k (query)", history_columns_.col_k);
    tree_history_.append_column("j (subject)", history_columns_.col_j);
    tree_history_.append_column("len (bp)", history_columns_.col_len);
    tree_history_.append_column("Fitness", history_columns_.col_fitness);
    tree_history_.set_headers_visible(true);
    tree_history_.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);

    scroll_history_.add(tree_history_);
    scroll_history_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    notebook_output_.append_page(scroll_history_, "PSO evolution");

    buffer_alignment_ = Gtk::TextBuffer::create();
    text_alignment_.set_buffer(buffer_alignment_);
    text_alignment_.set_editable(false);
    text_alignment_.set_cursor_visible(false);
    text_alignment_.override_font(Pango::FontDescription("monospace 11"));

    scroll_alignment_.add(text_alignment_);
    scroll_alignment_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    notebook_output_.append_page(scroll_alignment_, "Alignment");
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
        lbl_status_.set_text("Select the first sequence file.");
        return;
    }
    if (path2.empty()) {
        lbl_status_.set_text("Select the second sequence file.");
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

    lbl_status_.set_text("Aligning...");
    clear_results();
    worker_->launch();
}

void MainWindow::clear_results() {
    clear_summary_grid();
    history_store_->clear();
    buffer_alignment_->set_text("");
    notebook_output_.set_current_page(0);
}

void MainWindow::clear_summary_grid() {
    for (Gtk::Widget* child : grid_summary_.get_children())
        grid_summary_.remove(*child);
}

void MainWindow::add_summary_row(int row, const Glib::ustring& field, const Glib::ustring& meaning,
                                 const Glib::ustring& value) {
    auto lbl_field = Gtk::manage(new Gtk::Label(field, Gtk::ALIGN_START));
    auto lbl_meaning = Gtk::manage(new Gtk::Label(meaning, Gtk::ALIGN_START));
    auto lbl_value = Gtk::manage(new Gtk::Label(value, Gtk::ALIGN_START));

    lbl_field->set_markup("<b>" + field + "</b>");
    lbl_meaning->set_line_wrap(true);
    lbl_value->set_selectable(true);

    grid_summary_.attach(*lbl_field, 0, row, 1, 1);
    grid_summary_.attach(*lbl_meaning, 1, row, 1, 1);
    grid_summary_.attach(*lbl_value, 2, row, 1, 1);
}

void MainWindow::show_result(const core::AlignmentResult& result) {
    clear_summary_grid();

    if (!result.error.empty()) {
        add_summary_row(0, "Error", "Message", result.error);
        grid_summary_.show_all();
        history_store_->clear();
        buffer_alignment_->set_text("");
        notebook_output_.set_current_page(0);
        return;
    }

    int row = 0;
    auto hdr_field = Gtk::manage(new Gtk::Label("Field", Gtk::ALIGN_START));
    auto hdr_meaning = Gtk::manage(new Gtk::Label("Meaning", Gtk::ALIGN_START));
    auto hdr_value = Gtk::manage(new Gtk::Label("Value", Gtk::ALIGN_START));
    hdr_field->set_markup("<b>Field</b>");
    hdr_meaning->set_markup("<b>Meaning</b>");
    hdr_value->set_markup("<b>Value</b>");
    grid_summary_.attach(*hdr_field, 0, row, 1, 1);
    grid_summary_.attach(*hdr_meaning, 1, row, 1, 1);
    grid_summary_.attach(*hdr_value, 2, row, 1, 1);
    row++;

    add_summary_row(row++, "Query file", "Input sequence (query)", basename(result.file1));
    add_summary_row(row++, "Subject file", "Input sequence (subject)", basename(result.file2));
    add_summary_row(row++, "Query length", "Nucleotides in query", Glib::ustring::format(result.seq1_length) + " bp");
    add_summary_row(row++, "Subject length", "Nucleotides in subject", Glib::ustring::format(result.seq2_length) + " bp");
    add_summary_row(row++, "k", "Start position in query (0-based)", Glib::ustring::format(result.k));
    add_summary_row(row++, "j", "Start position in subject (0-based)", Glib::ustring::format(result.j));
    add_summary_row(row++, "len", "Fragment length compared", Glib::ustring::format(result.len) + " bp");
    add_summary_row(row++, "Fitness", "NUC44 score without gaps", format_double(result.fitness));
    add_summary_row(row++, "Gap score", "Smith-Waterman score in region", format_double(result.gap_score));
    add_summary_row(row++, "PSO steps", "Iterations logged when fitness improves",
                    Glib::ustring::format(result.pso_history.size()));

    grid_summary_.show_all();

    history_store_->clear();
    for (const core::PsoIterationStep& step : result.pso_history) {
        Gtk::TreeModel::Row history_row = *(history_store_->append());
        history_row[history_columns_.col_iteration] = step.iteration;
        history_row[history_columns_.col_k] = format_double(step.k, 1);
        history_row[history_columns_.col_j] = format_double(step.j, 1);
        history_row[history_columns_.col_len] = format_double(step.len, 1);
        history_row[history_columns_.col_fitness] = format_double(step.fitness);
    }

    std::ostringstream alignment_header;
    alignment_header << "Region: k=" << result.k << ", j=" << result.j << ", len=" << result.len << "\n";
    alignment_header << "Score with gaps: " << format_double(result.gap_score).raw() << "\n\n";
    buffer_alignment_->set_text(alignment_header.str() + result.alignment_text);

    notebook_output_.set_current_page(0);
}

void MainWindow::on_alignment_finished(AlignmentWorker* w) {
    if (w)
        show_result(w->get_result());
    lbl_status_.set_text("Alignment finished.");
}

}  // namespace gui
}  // namespace pso
