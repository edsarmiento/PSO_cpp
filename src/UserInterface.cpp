
#include  <gtkmm.h>
#include "PSO_Interface.h"

int main(int argc, char *argv[]){
  
    Gtk::Main kit(argc, argv);

//  Gtk::Window window;
  PSOWindow window;
//  window.set_title("Hola Ale!");
  window.show_all_children(true);
//  window.signal_delete_event().connect(sigc::mem_fun());

  Gtk::Main::run(window);

  return EXIT_SUCCESS;
}