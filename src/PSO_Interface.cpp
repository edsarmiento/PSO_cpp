#include <sstream>
#include "PSO_Interface.h"
#include <gtkmm.h>
#include <iostream>

PSOWindow::PSOWindow():
        lblTitle("Use a NCBI GenBank Format File "),
        lblADN1("Query String:"),
        fcbADN1("Select an ADN File"),
        lblADN2("Subject String: "),
        fcbADN2("Select an ADN File"),
        cmdAlign("Align"),
        credits("E. David Sarmiento, V. Alejandro Herrera"),
        frmOutPut("Output:"),
        lblPopulation("Population: "),
        adjPopulation(Gtk::Adjustment::create(5000, 100, 100000000, 100, 1000, 0)),
        lblDimensions("Dimensions: "),
        adjDimensions(Gtk::Adjustment::create(3, 1, 1000, 1, 10, 0)),
        lblIterations("Iterations: "),
        adjIterations(Gtk::Adjustment::create(500, 1, 100000000, 100, 1000, 0)),
        lblC1("c1: "),
        adjC1(Gtk::Adjustment::create(3.0, 0.1, 5.0, 0.1, 0.5, 0)),
        lblC2("c2: "),
        adjC2(Gtk::Adjustment::create(1.0, 0.1, 5.0, 0.1, 0.5, 0)),
        lblW("w: "),
        adjW(Gtk::Adjustment::create(0.8, 0.1, 100.0, 0.1, 0.5, 0)),
        hbFile1(Gtk::ORIENTATION_HORIZONTAL, 0),
        hbFile2(Gtk::ORIENTATION_HORIZONTAL, 0),
        hbAlign(Gtk::ORIENTATION_HORIZONTAL, 0),
        hbOutPut(Gtk::ORIENTATION_HORIZONTAL, 0),
        vbMain(Gtk::ORIENTATION_VERTICAL, 15)
{
    thread = new PSOThread();
    initialize_widgets();
    configure_dialogs();
    connect_signals();
}

PSOWindow::~PSOWindow(){
    delete thread;
}

void PSOWindow::initialize_widgets(){
    
    set_title("PSO  Comparator Algorithm V2013GUI");
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(800,600);
    
    lblTitle.set_alignment(0.5f, 0.5f);
    vbMain.pack_start(lblTitle,false,true,0);
    
    lblADN1.set_alignment(0.0f, 0.5f);
    
    hbFile1.pack_start(lblADN1,false,false,0);
    hbFile1.pack_start(fcbADN1,true,true,0);
    
    vbMain.pack_start(hbFile1,false,false,0);
    
    lblADN2.set_alignment(0.0f, 0.5f);
    
    hbFile2.pack_start(lblADN2,false,false,0);
    hbFile2.pack_start(fcbADN2,true,true,0);
    
    vbMain.pack_start(hbFile2,false,false,0);
    
    hbAlign.pack_start(cmdAlign,true,false,0);
    vbMain.pack_start(hbAlign,false,false,0);
    
    spnPopulation.set_adjustment(adjPopulation);
    spnPopulation.set_numeric(true);
    spnPopulation.set_digits(0);
    spnPopulation.set_alignment(1.0f);
    
    spnDimensions.set_adjustment(adjDimensions);
    spnDimensions.set_numeric(true);
    spnDimensions.set_digits(0);
    spnDimensions.set_alignment(1.0f);
//    spnDimensions.set_editable(false);
    spnDimensions.set_sensitive(false);
    
    spnIterations.set_adjustment(adjIterations);
    spnIterations.set_numeric(true);
    spnIterations.set_digits(0);
    spnIterations.set_alignment(1.0f);
    
    spnC1.set_adjustment(adjC1);
    spnC1.set_numeric(true);
    spnC1.set_digits(2);
    spnC1.set_alignment(1.0f);
    
    spnC2.set_adjustment(adjC2);
    spnC2.set_numeric(true);
    spnC2.set_digits(2);
    spnC2.set_alignment(1.0f);
    
    spnW.set_adjustment(adjW);
    spnW.set_numeric(true);
    spnW.set_digits(2);
    spnW.set_alignment(1.0f);
    
    gridParameters.set_column_spacing(5);
    gridParameters.set_row_spacing(5);
    
    gridParameters.attach(lblPopulation, 0, 0, 1, 1);
    gridParameters.attach(spnPopulation, 1, 0, 1, 1);
    gridParameters.attach(lblDimensions, 2, 0, 1, 1);
    gridParameters.attach(spnDimensions, 3, 0, 1, 1);
    gridParameters.attach(lblIterations, 4, 0, 1, 1);
    gridParameters.attach(spnIterations, 5, 0, 1, 1);
    gridParameters.attach(lblC1, 0, 1, 1, 1);
    gridParameters.attach(spnC1, 1, 1, 1, 1);
    gridParameters.attach(lblC2, 2, 1, 1, 1);
    gridParameters.attach(spnC2, 3, 1, 1, 1);
    gridParameters.attach(lblW, 4, 1, 1, 1);
    gridParameters.attach(spnW, 5, 1, 1, 1);

    vbMain.pack_start(gridParameters, false, true, 0);
    
    bufOutput = Gtk::TextBuffer::create();
    txtOutPut.set_buffer(bufOutput);
    
    txtOutPut.override_font(Pango::FontDescription("monospace 12"));
    scrOutPut.set_margin_end(12);
    scrOutPut.add(txtOutPut);
    
    frmOutPut.add(scrOutPut);
    
    vbMain.pack_start(frmOutPut,true,true,0);
    
    vbMain.pack_start(stbStatus,false,true,0);
    
    add(vbMain);
    
}

void PSOWindow::connect_signals(){
    cmdAlign.signal_clicked().connect( sigc::mem_fun(*this,&PSOWindow::cmdAlign_clicked) );
    thread->signal_finished().connect(
          sigc::bind<1>(sigc::mem_fun(*this, &PSOWindow::on_progress_finished), thread));
}

void PSOWindow::configure_dialogs() {
    Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    fcbADN1.add_filter(filter_text);
    fcbADN2.add_filter(filter_text);

    Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    fcbADN1.add_filter(filter_any);
    fcbADN2.add_filter(filter_any);
}

void PSOWindow::cmdAlign_clicked(){
    Glib::ustring f1=fcbADN1.get_filename();
    Glib::ustring f2=fcbADN2.get_filename();
    if(f1.length()==0){
        stbStatus.push("Select the first ADN file!");
        return;
    }
    if(f2.length()==0){
        stbStatus.push("Select the second ADN file!");
        return;
    }
    int population=(int)spnPopulation.get_value();
    int dimensions=(int)spnDimensions.get_value();
    int iterations=(int)spnIterations.get_value();
    double c1=spnC1.get_value();
    double c2=spnC2.get_value();
    double w=spnW.get_value();
    
    thread->set_file1(f1.raw());
    thread->set_file2(f2.raw());
    thread->set_population(population);
    thread->set_dimensions(dimensions);
    thread->set_iterations(iterations);
    thread->set_c1(c1);
    thread->set_c2(c2);
    thread->set_w(w);
    
    
    stbStatus.push("Aligning...");
    thread->launch();
}

void PSOWindow::on_progress_finished(PSOThread* pso_thread){
//    std::cout<<"PSOWindow::on_progress_finished"<<std::endl;
//    std::cout<<thread->get_output()<<std::endl;
    Glib::ustring output(pso_thread->get_output());
    bufOutput->set_text(output);
    stbStatus.push("Alignment finished.");
}