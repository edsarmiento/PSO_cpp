#include <gtkmm.h>
#include "gui/main_window.h"

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    pso::gui::MainWindow window;
    window.show_all_children(true);
    Gtk::Main::run(window);
    return EXIT_SUCCESS;
}
