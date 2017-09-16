#ifndef DIALOGO_AGREGAR_PRODUCTO
#define DIALOGO_AGREGAR_PRODUCTO

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>

class DialogoAgregarProducto:public Gtk::Dialog{
	private:

		/****** MODELO DEL LISTADO DE IMÁGENES ******/

		Gtk::ListViewText listaImagenes;
		Glib::RefPtr<Gtk::TreeSelection> selection;
		Gtk::TreeModelColumnRecord mCol;
		Glib::RefPtr<Gtk::ListStore> lista;
		int nImagenes;

		/****** WIDGETS ******/

		Gtk::Image* imagen;
		Gtk::Entry* nombreEntry;
		Gtk::TextView* descripcionText;
		Gtk::FileChooserButton* iconoFile;
		Gtk::ScrolledWindow* scrolled;
		Gtk::Image* icono;

		void conectarSeniales(Glib::RefPtr<Gtk::Builder>& builder);



	public:
	
		/****** CONSTRUCTOR ******/

		DialogoAgregarProducto(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder);

		/****** PARA MOSTRAR LAS IMÁGENES Y EL ÍCONO ******/

		void mostrarIcono();
		void mostrarImagen();

		/****** IMÁGENES DEL PRODUCTO ******/

		void agregarImagen();
		void eliminarImagen();
		void modificarImagen();

		/****** PARA ACEPTAR Y CANCELAR ******/

		void cerrar();
		void aceptar();

		/****** PARA OBTENER LOS DATOS ******/
		
		std::string obtenerNombreProducto();
		std::string obtenerDescripcionProducto();
		std::string obtenerIcono();
		std::vector<std::string> obtenerImagenes();	
		
		/****** PARA MODIFICAR ******/

		void precargarCampos(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes);
};

#endif
