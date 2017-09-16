#ifndef VISTA_ICONOS
#define VISTA_ICONOS

#include <gtkmm.h>

class VistaIconos: public Gtk::IconView{
	private:

		size_t ancho;
		size_t alto;

		/****** MODELO DEL LISTADO DE ITEMS ******/

		Gtk::TreeModelColumnRecord columnas;
		Gtk::TreeModelColumn <Glib::RefPtr<Gdk::Pixbuf> > columnaIcono;
		Gtk::TreeModelColumn <Glib::ustring> columnaNombre;
		Glib::RefPtr<Gtk::ListStore> lista;

	public:

		/****** CONSTRUCTOR ******/

		VistaIconos(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder);

		/****** PARA AGREGAR ITEMS ******/		

		void setItems(std::vector<std::string> nombres, std::vector<std::string> iconos);
		void agregarItem(std::string nombre, std::string icono);

		/****** PARA VACIAR LA VISTA DE ÍCONOS ******/

		void vaciar();
};

#endif
