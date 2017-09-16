#include "areaVisionBox.h"

/****** CONSTRUCTOR ******/

AreaVisionBox::AreaVisionBox(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder):Gtk::Box(cobject){
	builder -> get_widget("nombreAreaVisionLabel",nombreAreaVisionLabel);
	builder -> get_widget_derived("areaVisionIconos", vistaIconos);
	builder -> get_widget("tipoAreaVisionLabel", tipoAreaVisionLabel);
	builder -> get_widget("areasVisionTreeView", areasVisionTreeView);
	Gtk::DrawingArea* stockAreaVisionDrawing;
	builder -> get_widget("stockAreaVisionDrawing",stockAreaVisionDrawing);
	grafico = new GraficoDeTorta(stockAreaVisionDrawing);
	selection = areasVisionTreeView->get_selection();
	columnas.add(nombre);
	columnas.add(tipo);
	columnas.add(id);
	Gtk::Button* bajaAreaVisionButton;
	builder -> get_widget("bajaAreaVisionButton", bajaAreaVisionButton);
	bajaAreaVisionButton->signal_clicked().connect(sigc::mem_fun(this, &AreaVisionBox::bajaAreaVision));
	Gtk::Button* altaAreaVisionButton;
	builder -> get_widget("altaAreaVisionButton",altaAreaVisionButton);
	altaAreaVisionButton->signal_clicked().connect(sigc::mem_fun(this, &AreaVisionBox::altaAreaVision));	
	selection->signal_changed().connect(sigc::mem_fun(this,&AreaVisionBox::actualizar));
	Gtk::Button* modificarAreaVisionButton;
	builder -> get_widget("modificarAreaVisionButton", modificarAreaVisionButton);
	modificarAreaVisionButton->signal_clicked().connect(sigc::mem_fun(this,&AreaVisionBox::modificarAreaVision));
}

/****** CONEXIÓN DE SEÑALES ******/

sigc::signal<void, std::string, std::string, std::string> AreaVisionBox::signal_modificarAreaVision(){
	return sig_modificarAreaVision;
}
sigc::signal<void,std::string> AreaVisionBox::signal_bajaAreaVision(){
	return sig_bajaAreaVision;
}
sigc::signal<void, std::string, std::string> AreaVisionBox::signal_altaAreaVision(){
	return sig_altaAreaVision;
}
sigc::signal<void,std::string> AreaVisionBox::signal_stockAreaVision(){
	return sig_stockAreaVision;
}

/****** ALTA, BAJA Y MODIFICACIÓN ******/

void AreaVisionBox::modificarAreaVision(){
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	Glib::ustring nombre1;
	nombre1 = row.get_value(nombre);
	Glib::ustring id1;
	id1 = row.get_value(id);
	Glib::ustring tipo1;
	tipo1 = row.get_value(tipo);
	DialogoAgregarAreaVision* dialogo;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	builder -> add_from_file("glade/dialogoAgregarAreaVision.glade");
	builder -> get_widget_derived("dialogoAgregarAreaVision",dialogo);
	dialogo->precargarCampos(nombre1, tipo1);
	int result = dialogo->run();
	if(result == Gtk::RESPONSE_OK)sig_modificarAreaVision.emit(id1,dialogo->obtenerNombreAreaVision(), dialogo->obtenerTipoAreaVision());
}
void AreaVisionBox::altaAreaVision(){
	DialogoAgregarAreaVision* dialogo;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	builder -> add_from_file("glade/dialogoAgregarAreaVision.glade");
	builder -> get_widget_derived("dialogoAgregarAreaVision",dialogo);
	int result = dialogo->run();
	if(result == Gtk::RESPONSE_OK){
		sig_altaAreaVision.emit(dialogo->obtenerNombreAreaVision(),dialogo->obtenerTipoAreaVision());
	}
}
void AreaVisionBox::bajaAreaVision(){
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::MessageDialog dialogo("¿Esta seguro de que desea eliminar?",false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);
	dialogo.set_secondary_text("Seguro?");
	int result = dialogo.run();
	switch(result){
		case Gtk::RESPONSE_OK:{

			Gtk::TreeModel::Row row = *iter;
			Glib::ustring id1;
			id1 = row.get_value(id);
			sig_bajaAreaVision.emit(id1);
			break;}
		case Gtk::RESPONSE_CANCEL:
			break;
	}
}

/****** OTROS MÉTODOS ******/

void AreaVisionBox::actualizar(){
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	Glib::ustring nombre1;
	Glib::ustring tipo1;
	nombre1 = row.get_value(nombre);
	tipo1 = row.get_value(tipo);
	set_area_vision(nombre1, tipo1);
	sig_stockAreaVision.emit(nombre1);
}
void AreaVisionBox::actualizarDatos(std::vector<std::string> nombres, std::vector<std::string> ids, std::vector<std::string> tipos){
	listado = Gtk::ListStore::create(columnas);
	areasVisionTreeView -> set_model(listado);
	areasVisionTreeView -> remove_all_columns();
	areasVisionTreeView -> append_column("Área de visión", nombre);
	for(int i = 0; i < nombres.size(); i++){
		Gtk::TreeModel::iterator iter = listado -> append();
		Gtk::TreeModel::Row row = *iter;
		row[nombre] = nombres[i];
		row[tipo] = tipos[i];
		row[id] = ids[i];
		if(i == 0) selection -> select(iter);
	}
}
void AreaVisionBox::set_area_vision(std::string nombre, std::string tipo){
	nombreAreaVisionLabel->set_text(nombre);
	tipoAreaVisionLabel->set_text(tipo);
	vistaIconos->vaciar();
}
void AreaVisionBox::recibirStockAreaVision(std::vector<std::pair<std::string, int> > stock,std::vector<std::string> iconos){
		std::vector<std::string> productos;
	for(int i = 0; i < stock.size(); i++){
		productos.push_back(stock[i].first);
	}
	grafico -> setearDatos(stock);
	vistaIconos->setItems(productos, iconos);	
	grafico->dibujarStock();
}

/****** DESTRUCTOR ******/

AreaVisionBox::~AreaVisionBox(){
	delete grafico;
}

