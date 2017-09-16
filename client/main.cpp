#include <glibmm/refptr.h>
#include <gtkmm/application.h>

#include "Home.h"

int main(int argc, char* argv[]) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
                                                                "tp.final");
  Home home(app);
  home.ejecutar();

}

