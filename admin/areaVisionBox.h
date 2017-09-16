#ifndef AREA_VISION_BOX
#define AREA_VISION_BOX

#include <gtkmm.h>
#include "vistaIconos.h"
#include <iostream>
#include "graficoDeTorta.h"
#include "dialogoAgregarAreaVision.h"

class AreaVisionBox: public Gtk::Box{
	private:

		/****** WIDGETS ******/

		Gtk::Label* nombreAreaVisionLabel;
		Gtk::Label* tipoAreaVisionLabel;
		VistaIconos* vistaIconos;
		GraficoDeTorta* grafico;
		Gtk::TreeView* areasVisionTreeView;

		/****** MODELO DE LISTADO DE AREAS DE VISION ******/

		Glib::RefPtr<Gtk::ListStore> listado;
		Gtk::TreeModelColumnRecord columnas;
		Gtk::TreeModelColumn<Glib::ustring> nombre;
		Gtk::TreeModelColumn<Glib::ustring> tipo;
		Gtk::TreeModelColumn<Glib::ustring> id;
		Glib::RefPtr<Gtk::TreeSelection> selection;

		/****** SEÑALES *******/

		sigc::signal<void, std::string> sig_stockAreaVision;
		sigc::signal<void, std::string> sig_bajaAreaVision;
		sigc::signal<void, std::string, std::string> sig_altaAreaVision;
		sigc::signal<void, std::string, std::string, std::string> sig_modificarAreaVision;

	public:
		
		/****** CONSTRUCTOR ******/

		AreaVisionBox(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder);

		/****** CONEXIÓN DE SEÑALES ******/

        sigc::signal<void,std::string> signal_bajaAreaVision();
        sigc::signal<void, std::string, std::string, std::string> signal_modificarAreaVision();
        sigc::signal<void, std::string, std::string> signal_altaAreaVision();
		sigc::signal<void,std::string> signal_stockAreaVision();

		/****** ALTA, BAJA Y MODIFICACIÓN ******/

		void modificarAreaVision();
		void altaAreaVision();
		void bajaAreaVision();

		/****** OTROS MÉTODOS *******/

		void actualizar();
		void actualizarDatos(std::vector<std::string> nombres,std::vector<std::string> ids, std::vector<std::string> tipos);
		void set_area_vision(std::string nombre, std::string tipo);
		void recibirStockAreaVision(std::vector<std::pair<std::string, int> > stock,std::vector<std::string> iconos);

		/****** DESTRUCTOR ******/

		~AreaVisionBox();

};

#endif
