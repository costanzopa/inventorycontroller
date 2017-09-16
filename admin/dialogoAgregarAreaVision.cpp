#include "dialogoAgregarAreaVision.h"

/****** CONSTRUCTOR ******/

DialogoAgregarAreaVision::DialogoAgregarAreaVision(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder):Gtk::Dialog(cobject){
	builder -> get_widget("nombreAreaVisionEntry",nombreEntry);
  	builder -> get_widget("tipoAreaVisionCombo", tipoAreaVisionCombo);
	builder -> get_widget("aceptarAreaVisionButton", aceptarButton);
  	builder -> get_widget("cancelarAreaVisionButton", cancelarButton);
	cancelarButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarAreaVision::cerrar));
	aceptarButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarAreaVision::aceptar));
}

/****** PARA MODIFICAR ******/

void DialogoAgregarAreaVision::precargarCampos(std::string producto, std::string tipo){
	nombreEntry->set_text(producto);
	tipoAreaVisionCombo->set_active_text(tipo);
}	

/****** PARA ACEPTAR Y CANCELAR ******/

void DialogoAgregarAreaVision::aceptar(){
	std::string mensaje = "";

	if(nombreEntry->get_text() == ""){
		mensaje = "Error: no se especificó un nombre de producto";
		Gtk::MessageDialog dialogo (mensaje,Gtk::MESSAGE_ERROR);
		dialogo.set_transient_for(*this);
		dialogo.run();
	}
	else {
		response(Gtk::RESPONSE_OK);
		close();
	}

}
void DialogoAgregarAreaVision::cerrar(){
	response(Gtk::RESPONSE_CANCEL);
	close();
}

/****** PARA OBTENER LOS DATOS ******/

std::string DialogoAgregarAreaVision::obtenerTipoAreaVision(){
	return tipoAreaVisionCombo->get_active_text();
}
std::string DialogoAgregarAreaVision::obtenerNombreAreaVision(){
	return nombreEntry->get_text();
}
