#ifndef SEL_FECHA
#define SEL_FECHA

#include <gtkmm.h>

class SelectorFecha: public Gtk::Box {
	private:

		/****** WIDGETS DESDE ******/

		Gtk::Calendar* fechaDesdeCalendar;
		Gtk::ComboBoxText* horaDesdeCombo;
		Gtk::ComboBoxText* minDesdeCombo;
		Gtk::CheckButton* principioCheck;

		/****** WIDGETS HASTA ******/

		Gtk::Calendar* fechaHastaCalendar;
		Gtk::ComboBoxText* horaHastaCombo;
		Gtk::ComboBoxText* minHastaCombo;
		Gtk::CheckButton* finCheck;

		/****** ACTIVAR Y DESACTIVAR LOS CALENDARIOS ******/

		void toggleDesdeActivo();
		void toggleHastaActivo();

	public:

		/****** CONSTRUCTOR ******/

		SelectorFecha(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder);

		/****** OBTENER LAS FECHAS ******/

		std::string obtenerDesde();
		std::string obtenerHasta();
};

#endif
