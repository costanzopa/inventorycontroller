#include "vistaIconos.h"

/****** CONSTRUCTOR ******/

VistaIconos::VistaIconos(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder):Gtk::IconView(cobject){
	ancho = 64;
	alto = 64;
	columnas.add(columnaIcono);
	columnas.add(columnaNombre);
	lista = Gtk::ListStore::create(columnas);
	set_pixbuf_column(columnaIcono);
	set_text_column(columnaNombre);
	set_model(lista);
	show();
}

/****** PARA AGREAR ICONOS ******/

void VistaIconos::agregarItem(std::string nombre, std::string icono){
	Gtk::TreeModel::iterator iter = lista -> append();
	Gtk::TreeModel::Row row = *iter;
	row[columnaNombre] = nombre;
	row[columnaIcono] = Gdk::Pixbuf::create_from_file(icono,ancho,alto,true);
}
void VistaIconos::setItems(std::vector<std::string> nombres, std::vector<std::string> iconos){
	lista = Gtk::ListStore::create(columnas);
	set_model(lista);
	for(int i = 0; i < nombres.size(); i++)agregarItem(nombres[i],iconos[i]);
}

/****** PARA VACIAR LA VISTA DE ÍCONOS ******/

void VistaIconos::vaciar(){
	lista = Gtk::ListStore::create(columnas);
	set_model(lista);
}
