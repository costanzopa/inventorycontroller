#include "vista.h"
#include <gtkmm.h>
#include "controlador.h"
#include "modelo.h"
int main(int argc, char*  argv[]){
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"mi.app");
	Vista vista;
	std::string s;
	std::getline(std::cin,s);
	Modelo modelo(s);
	Controlador controlador(modelo,vista);
	controlador.iniciar();
	app -> run(vista.obtenerVentanaPrincipal());
}
