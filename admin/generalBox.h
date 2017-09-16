#ifndef GENERAL_BOX
#define GENERAL_BOX

#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include "graficoDeBarras.h"
#include "vistaIconos.h"

class GeneralBox:public Gtk::Box{
	private:

		/****** WIDGETS ******/

		VistaIconos* productosIconos;
		GraficoDeBarras* grafico;

		/****** LISTADOS ******/

		std::vector<std::string> productos;
		std::vector<int> stock;
		std::vector<std::string> iconos;

	public:

		/****** CONSTRUCTOR ******/

		GeneralBox(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>&builder);

		/****** ACTUALIZAR LOS PRODUCTOS ******/

		void actualizarDatos(std::vector<std::string> productos, std::vector<std::string> iconos, std::vector<int> stock);

		/****** STOCK ******/

		void recibirStockGeneral(std::vector<std::pair<std::string,int> > stock);

		/****** DESTRUCTOR ******/

		~GeneralBox();

};

#endif
