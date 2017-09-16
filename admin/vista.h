#ifndef VISTA
#define VISTA

#include <vector>
#include <string>
#include <iostream>
#include <gtkmm.h>
#include "generalBox.h"
#include "productoBox.h"
#include "areaVisionBox.h"

class Vista{
	private:

		/****** BUILDER ******/

		Glib::RefPtr<Gtk::Builder> builder;
		
		/****** VENTANA PRINCIPAL ******/

		Gtk::Window* ventanaPrincipal;

		/****** OTROS WIDGETS ******/

		Gtk::Notebook* notebook;

		Gtk::Box* actual;
		GeneralBox* generalBox;
		ProductoBox* productoBox;
		AreaVisionBox* areaVisionBox;

		/****** SEÑALES ******/

		sigc::signal<void> sig_informacionProductos;
		sigc::signal<void> sig_stockGeneral;
		sigc::signal<void> sig_informacionAreasVision;

	public:
		/****** CONSTRUCTOR ******/

		Vista();

		/****** CONEXION DE SEÑALES ******/

		sigc::signal<void, std::string> signal_imagenesProducto();
		sigc::signal<void> signal_informacionProductos();
		sigc::signal<void> signal_stockGeneral();
		sigc::signal<void, std::string, std::string, std::string> signal_modificarAreaVision();
		sigc::signal<void, std::string, std::string> signal_altaAreaVision();
		sigc::signal<void, std::string, std::string, std::string>signal_stockHistoricoProducto();
		sigc::signal<void, std::string> signal_bajaProducto();
		sigc::signal<void, std::string, std::string,std::string,  std::vector<std::string> > signal_altaProducto();
		sigc::signal<void, std::string> signal_stockAreaVision();
		sigc::signal<void, std::string> signal_bajaAreaVision();
		sigc::signal<void> signal_informacionAreasVision();
		sigc::signal<void, std::string, std::string, std::string, std::string, std::vector<std::string> > signal_modificarProducto();

		/****** OTROS METODOS ******/

		Gtk::Window& obtenerVentanaPrincipal();		
		void cambiarActual(Gtk::Widget* page, guint idx);
		void cargarGeneral();
		void cargarProductos();
		void cargarAreasVision();

		/****** METODOS RELACIONADOS CON LA ADMINISTRACION ******/

		void recibirStockGeneral(std::vector<std::pair<std::string, int> > stock);
		void recibirInformacionProductos(std::vector<std::string> productos, std::vector<std::string> ids, std::vector<std::string> descripciones, std::vector<std::string> iconos);
		void recibirStockAreaVision(std::vector<std::pair<std::string, int > > stock,std::vector<std::string> iconos);
		void recibirStockGeneral(std::vector<std::string> productos, std::vector<std::string> iconos, std::vector<int> stock);
		void recibirStockProducto(std::vector<int> stock);
		void recibirImagenesProducto(std::vector<std::string> imagenes);
		void recibirInformacionAreasVision(std::vector<std::string> areasVision,std::vector<std::string> ids ,std::vector<std::string> tiposAreasVision);

		/****** DESTRUCTOR ******/

		virtual ~Vista();
};

#endif
