#include "productoBox.h"
#include "../common/StringUtils.h"
/****** CONSTRUCTOR ******/

ProductoBox::ProductoBox(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder):Gtk::Box(cobject){
	Gtk::DrawingArea* stockHistoricoDrawing;
	Gtk::Button* actualizarButton;
	builder -> get_widget("actualizarButton",actualizarButton);
	actualizarButton -> signal_clicked().connect(sigc::mem_fun(this,&ProductoBox::actualizarGrafico));
	builder -> get_widget("stockHistoricoDrawing",stockHistoricoDrawing);
	builder -> get_widget_derived("selectorFechaBox",selectorFecha);
	builder -> get_widget("nombreProductoLabel",nombreProductoLabel);
	Gtk::TextView* descripcionProductoTextView;
	builder -> get_widget("descripcionProductoTextView",descripcionProductoTextView);
	descripcionBuffer = descripcionProductoTextView -> get_buffer();
	builder -> get_widget("iconoProducto",iconoProducto);
	graficoDeBarras = new GraficoDeBarras(stockHistoricoDrawing,GBARRAS_HISTORICO);
	builder -> get_widget("productosTreeView", productosTreeView);
	columnas.add(nombre);
	columnas.add(descripcion);
	columnas.add(icono);
	columnas.add(id);

	selection = productosTreeView -> get_selection();	
	productosTreeView->set_model(listado);
	Gtk::Button* bajaProductoButton;
	Gtk::Button* altaProductoButton;
	builder -> get_widget("bajaProductoButton", bajaProductoButton);
	builder -> get_widget("altaProductoButton", altaProductoButton);
	bajaProductoButton->signal_clicked().connect(sigc::mem_fun(this,&ProductoBox::bajaProducto));
	altaProductoButton->signal_clicked().connect(sigc::mem_fun(this,&ProductoBox::altaProducto));
	selection->signal_changed().connect(sigc::mem_fun(this,&ProductoBox::actualizar));
	Gtk::Button* modificarProductoButton;
	builder -> get_widget("modificarProductoButton", modificarProductoButton);
	modificarProductoButton->signal_clicked().connect(sigc::mem_fun(this,&ProductoBox::imagenesProducto));
}

/****** CONEXIÓN DE SEÑALES ******/

sigc::signal<void, std::string> ProductoBox::signal_imagenesProducto(){
	return sig_imagenesProducto;
}
sigc::signal<void,std::string,std::string,std::string> ProductoBox::signal_stockHistoricoProducto(){
	return sig_stockHistoricoProducto;
}
sigc::signal<void,std::string> ProductoBox::signal_bajaProducto(){
	return sig_bajaProducto;
}
sigc::signal<void,std::string,std::string,std::string, std::vector<std::string> >ProductoBox::signal_altaProducto(){
	return sig_altaProducto;
}
sigc::signal<void, std::string, std::string,std::string,std::string,std::vector<std::string> > ProductoBox::signal_modificarProducto(){
	return sig_modificarProducto;
}
/****** ALTA, BAJA Y MODIFICACION ******/

void ProductoBox::imagenesProducto(){
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	std::string pId = row.get_value(id);
	sig_imagenesProducto.emit(pId);
}
void ProductoBox::modificarProducto(std::vector<std::string> imagenes){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	builder -> add_from_file("glade/dialogoAgregarProducto.glade");
	DialogoAgregarProducto* dialogo;
	builder -> get_widget_derived("dialogoAgregarProducto", dialogo);
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	std::string producto = row.get_value(nombre);
	std::string descripcionS = row.get_value(descripcion);
	std::string iconoS = row.get_value(icono);	
	std::string idS = row.get_value(id);
	dialogo->precargarCampos(producto, descripcionS,iconoS,imagenes);
	int result = dialogo->run();
	if(result == Gtk::RESPONSE_CANCEL)return;
	dialogo -> close();
	std::vector<std::string> nuevasImagenes = dialogo->obtenerImagenes();
	std::string nuevoNombre = dialogo->obtenerNombreProducto();
	std::string nuevaDescripcion = dialogo->obtenerDescripcionProducto();
	std::string nuevoIcono = dialogo -> obtenerIcono();
	sig_modificarProducto.emit(idS,nuevoNombre,nuevaDescripcion,nuevoIcono,nuevasImagenes);
}
void ProductoBox::altaProducto(){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	builder -> add_from_file("glade/dialogoAgregarProducto.glade");
	DialogoAgregarProducto* dialogo;
	builder -> get_widget_derived("dialogoAgregarProducto", dialogo);
	int result = dialogo->run();
		
	if(result == Gtk::RESPONSE_OK){
		std::string producto = dialogo->obtenerNombreProducto();
		std::string iconoS = dialogo->obtenerIcono();
		std::string descripcionS = dialogo->obtenerDescripcionProducto();
		std::vector<std::string> imagenes = dialogo->obtenerImagenes();
		sig_altaProducto.emit(producto,descripcionS,iconoS,imagenes);
	}
}
void ProductoBox::bajaProducto(){
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
			sig_bajaProducto.emit(id1);
			break;}
		case Gtk::RESPONSE_CANCEL:
			break;
	}
}

/****** OTROS MÉTODOS ******/

void ProductoBox::actualizar(){
	Gtk::TreeModel::iterator iter =	selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	Glib::ustring nombre;
	Glib::ustring descripcion;
	Glib::ustring icono;
	row.get_value(0,nombre);
	row.get_value(1,descripcion);
	row.get_value(2,icono);
	setProducto(nombre,descripcion,icono);
	graficoDeBarras->vaciar();
}
void ProductoBox::setProducto(std::string producto,std::string descripcion,std::string icono){
	nombreProductoLabel -> set_text(producto);
	descripcionBuffer -> set_text (descripcion);
	iconoProducto -> set(Gdk::Pixbuf::create_from_file(icono,TAM_ICONO,TAM_ICONO,true));
}
void ProductoBox::recibirStockProducto(std::vector<int>& stock){
	std::vector<std::string> labels;
	std::stringstream s;
	for(int i = 0; i < stock.size()+1; i++){
		s << i;
		labels.push_back("FECHA"+s.str());
		s.str("");
	}
	graficoDeBarras->setDatos(labels, stock);
	graficoDeBarras->dibujar();
}
void ProductoBox::actualizarDatos(std::vector<std::string> productos,std::vector<std::string> ids, std::vector<std::string> descripciones, std::vector<std::string> iconos){
	listado = Gtk::ListStore::create(columnas);
	productosTreeView->unset_model();
	productosTreeView -> set_model(listado);
	productosTreeView -> remove_all_columns();
	productosTreeView -> append_column("Producto",nombre);
	
	for(int i = 0; i < productos.size();i++){
		Gtk::TreeModel::iterator iter = listado -> append();
		Gtk::TreeModel::Row row = *iter;
		row[nombre] = productos[i];
		row[descripcion] = descripciones[i];
		row[icono] = iconos[i];
		row[id] = ids[i];
		if(i == 0) selection -> select(iter);
	}
}
void ProductoBox::actualizarGrafico(){
	std::string s_desde = selectorFecha->obtenerDesde();
	std::string s_hasta = selectorFecha->obtenerHasta();
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	std::string pId = row.get_value(id);
	sig_stockHistoricoProducto.emit(pId,s_desde,s_hasta);
}

/****** DESTRUCTOR ******/

ProductoBox::~ProductoBox(){
	delete graficoDeBarras;
}
