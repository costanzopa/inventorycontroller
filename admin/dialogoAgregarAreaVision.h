#ifndef DIALOGO_AGREGAR_AREA_VISION
#define DIALOGO_AGREGAR_AREA_VISION

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>

class DialogoAgregarAreaVision:public Gtk::Dialog{
	private:
		
		/****** WIDGETS ******/

		Gtk::ComboBoxText* tipoAreaVisionCombo;
		Gtk::Entry* nombreEntry;
		Gtk::Button* aceptarButton;
		Gtk::Button* cancelarButton;

		void conectarSeniales(Glib::RefPtr<Gtk::Builder>& builder);

	public:

		/****** CONSTRUCTOR ******/

		DialogoAgregarAreaVision(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder);

		/****** PARA ACEPTAR Y CANCELAR ******/

		void cerrar();
		void aceptar();

		/****** PARA OBTENER LOS DATOS ******/

		std::string obtenerNombreAreaVision();
		std::string obtenerTipoAreaVision();

		/****** PARA MODIFICAR ******/

		void precargarCampos(std::string areaVision, std::string tipo);
};

#endif
