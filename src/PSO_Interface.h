/* 
 * File:   PSO_Interface.h
 * Author: alejandro
 *
 * Created on February 17, 2012, 11:15 PM
 */

#ifndef PSO_INTERFACE_H
#define	PSO_INTERFACE_H

#include <gtkmm.h>
#include <sstream>
#include "PSOThread.h"

class PSOWindow : public Gtk::Window {
public:
    PSOWindow();
    virtual ~PSOWindow();
    

private:
    
    PSOThread* thread;
    
    virtual void connect_signals();
    virtual void initialize_widgets();
    virtual void configure_dialogs();
    
    void on_progress_finished(PSOThread* thread_progress);

protected:
    //Signal handlers:
    virtual void cmdAlign_clicked();


    //Child widgets:
    Gtk::Label lblTitle;
    Gtk::Label lblADN1;
    Gtk::FileChooserButton fcbADN1;

    Gtk::Label lblADN2;
    Gtk::FileChooserButton fcbADN2;
    
    Gtk::Table tblParameters;
    
    Gtk::Label lblPopulation;
    Gtk::SpinButton spnPopulation;
    Gtk::Adjustment adjPopulation;
    
    Gtk::Label lblDimensions;
    Gtk::SpinButton spnDimensions;
    Gtk::Adjustment adjDimensions;
    
    Gtk::Label lblIterations;
    Gtk::SpinButton spnIterations;
    Gtk::Adjustment adjIterations;
    
    Gtk::Label lblC1;
    Gtk::SpinButton spnC1;
    Gtk::Adjustment adjC1;
    
    Gtk::Label lblC2;
    Gtk::SpinButton spnC2;
    Gtk::Adjustment adjC2;
   
    Gtk::Label lblW;
    Gtk::SpinButton spnW;
    Gtk::Adjustment adjW;
    
    Gtk::Button cmdAlign;
    Gtk::Button credits;
    
    
    Gtk::Frame frmOutPut;
    Gtk::Alignment aligOutPut;
    Gtk::ScrolledWindow scrOutPut;
    Gtk::TextView txtOutPut;
    Glib::RefPtr<Gtk::TextBuffer> bufOutput;
    Gtk::Label lblOutPut;

    Gtk::Statusbar stbStatus;
    
    Gtk::HBox hbFile1;
    Gtk::HBox hbFile2;
    Gtk::HBox hbAlign;
    Gtk::HBox hbOutPut;

    Gtk::VBox vbMain;
};

#endif	/* PSO_INTERFACE_H */

