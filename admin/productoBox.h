#ifndef STOCK_PRODUCTO
#define STOCK_PRODUCTO

#include <vector>
#include <sstream>
#include <gtkmm.h>
#include <iostream>
#include <cairomm/context.h>
#include "graficoDeBarras.h"
#include "dialogoAgregarProducto.h"
#include "selectorFecha.h"

#define TAM_ICONO 64

class ProductoBox:public Gtk::Box{
	private:
	
		/****** SEÑALES ******/		

		sigc::signal<void,std::string,std::string,std::string> sig_stockHistoricoProducto;
		sigc::signal<void,std::string> sig_bajaProducto;
		sigc::signal<void, std::string, std::string, std::string, std::vector<std::string> > sig_altaProducto;
		sigc::signal<void,std::string> sig_imagenesProducto;
		sigc::signal<void, std::string, std::string, std::string,std::string, std::vector<std::string> > sig_modificarProducto;
		/****** WIDGETS *****/

		SelectorFecha* selectorFecha;
		Gtk::Label* nombreProductoLabel;
		Glib::RefPtr<Gtk::TextBuffer> descripcionBuffer;
		Gtk::Image* iconoProducto;
		GraficoDeBarras* graficoDeBarras;

		/****** MODELO DE LISTADO DE PRODUCTOS ******/

		Glib::RefPtr<Gtk::TreeSelection> selection;	
		Glib::RefPtr<Gtk::ListStore> listado;
		Gtk::TreeModelColumnRecord columnas;
		Gtk::TreeModelColumn<Glib::ustring> nombre;
		Gtk::TreeModelColumn<Glib::ustring> descripcion;
		Gtk::TreeModelColumn<Glib::ustring> icono;
		Gtk::TreeModelColumn<Glib::ustring> id;
		Gtk::TreeView* productosTreeView;

	public:

		/****** CONSTRUCTOR ******/

		ProductoBox(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder);

		/****** CONEXIÓN DE SEÑALES ******/

		sigc::signal<void, std::string> signal_imagenesProducto();
		sigc::signal<void,std::string> signal_bajaProducto();
		sigc::signal<void,std::string,std::string, std::string> signal_stockHistoricoProducto();
		sigc::signal<void, std::string, std::string, std::string, std::vector<std::string> > signal_altaProducto();

		/****** ALTA, BAJA Y MODIFICACIÓN ******/		

		void bajaProducto();
		void altaProducto();
		void imagenesProducto();
		void modificarProducto(std::vector<std::string> imagenes);

		/****** OTROS MÉTODOS ******/

		void actualizar();
		void actualizarGrafico();
		void setProducto(std::string producto, std::string descripcion, std::string icono);
		void recibirStockProducto(std::vector<int>& stock);
		void actualizarDatos(std::vector<std::string> productos, std::vector<std::string> ids, std::vector<std::string> descripciones, std::vector<std::string> iconos);

		/****** DESTRUCTOR ******/

		~ProductoBox();


		sigc::signal<void, std::string, std::string, std::string, std::string, std::vector<std::string> > signal_modificarProducto();
};

#endif
