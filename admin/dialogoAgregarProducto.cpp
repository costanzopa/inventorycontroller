#include "dialogoAgregarProducto.h"

/****** CONSTRUCTOR ******/

DialogoAgregarProducto::DialogoAgregarProducto(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder):Gtk::Dialog(cobject),listaImagenes(1){
	nImagenes=0;
	builder -> get_widget("nombreProductoEntry",nombreEntry);
	builder -> get_widget("descripcionText", descripcionText);
	builder -> get_widget("iconoFile", iconoFile);

	builder -> get_widget("scrolled", scrolled);
	Glib::RefPtr<Gtk::FileFilter> filtroImagen = Gtk::FileFilter::create();
	filtroImagen->set_name("Imágenes");
	filtroImagen->add_pattern("*.jpg");
	filtroImagen->add_pattern("*.png");
	iconoFile->add_filter(filtroImagen);

	scrolled->add(listaImagenes);
	Gtk::TreeModelColumn <Glib::ustring> nombre;
	mCol.add(nombre); 
	builder -> get_widget("productoImage", imagen);
	builder -> get_widget("icono", icono);	
	lista = Gtk::ListStore::create(mCol);
	listaImagenes.set_model(lista);
	selection = listaImagenes.get_selection();
	listaImagenes.set_column_title(0,"Imagenes");
	scrolled->show_all();

	conectarSeniales(builder);
}

void DialogoAgregarProducto::conectarSeniales(Glib::RefPtr<Gtk::Builder>& builder){
	Gtk::Button* agregarImagenButton;
	Gtk::Button* eliminarImagenButton;
	Gtk::Button* modificarImagenButton;
	Gtk::Button* aceptarButton;
	Gtk::Button* cancelarButton;
	builder -> get_widget("agregarImagenButton", agregarImagenButton);
	builder -> get_widget("eliminarImagenButton", eliminarImagenButton);
	builder -> get_widget("aceptarProductoButton", aceptarButton);
	builder -> get_widget("cancelarProductoButton", cancelarButton);
	agregarImagenButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarProducto::agregarImagen));
	eliminarImagenButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarProducto::eliminarImagen));
	cancelarButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarProducto::cerrar));
	aceptarButton->signal_clicked().connect(sigc::mem_fun(this,&DialogoAgregarProducto::aceptar));
	selection -> signal_changed().connect(sigc::mem_fun(this, &DialogoAgregarProducto::mostrarImagen));
	iconoFile -> signal_file_set().connect(sigc::mem_fun(this, &DialogoAgregarProducto::mostrarIcono));
}

/****** PARA EL MODIFICAR ******/

void DialogoAgregarProducto::precargarCampos(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes){
	nombreEntry->set_text(producto);
	descripcionText->get_buffer()->set_text(descripcion);
	iconoFile->set_filename(icono);
	mostrarIcono();
	for(int i = 0; i < imagenes.size(); i++){
		Gtk::TreeModel::iterator iter = lista -> append();
		Gtk::TreeModel::Row row = *iter;
		row.set_value(0,imagenes[i]);
		if(i==0)selection -> select(iter);
		nImagenes++;
	}
	
}

/****** PARA MOSTRAR LA IMAGENES Y EL ÍCONO ******/

void DialogoAgregarProducto::mostrarImagen(){
	Gtk::TreeModel::iterator iter = selection -> get_selected();
	if(!iter)return;
	Gtk::TreeModel::Row row = *iter;
	std::string nombre;
	row.get_value(0,nombre);
	imagen->set(Gdk::Pixbuf::create_from_file(nombre,150,150,true));
}
void DialogoAgregarProducto::mostrarIcono(){
	std::string nombre = iconoFile->get_filename();
	icono->set(Gdk::Pixbuf::create_from_file(nombre,64,64,true));
}

/****** PARA ACEPTAR Y CANCELAR ******/

void DialogoAgregarProducto::aceptar(){
	std::string mensaje = "";

	if(nombreEntry->get_text() == ""){
		mensaje = "Error: no se especificó un nombre de producto";
	} else if(nImagenes == 0){
		mensaje = "Error: no hay imágenes para el producto";
	} else if (iconoFile -> get_filename() ==""){
		mensaje = "Error: no hay un ícono para el producto";
		
	}else if(descripcionText->get_buffer()->get_text()==""){
			mensaje = "Error: no hay una descripción para el producto";
	}
	if(mensaje != ""){
		Gtk::MessageDialog dialogo (mensaje,Gtk::MESSAGE_ERROR);
		dialogo.set_transient_for(*this);
		dialogo.run();
	}	
	else {
		response(Gtk::RESPONSE_OK);
		close();
	}

}
void DialogoAgregarProducto::cerrar(){
	response(Gtk::RESPONSE_CANCEL);
	close();
}

/****** IMAGENES DEL PRODUCTO ******/

void DialogoAgregarProducto::agregarImagen(){
  Gtk::FileChooserDialog fileChooser("Seleccionar imagen para agregar",Gtk::FILE_CHOOSER_ACTION_OPEN);
	fileChooser.add_button("Abrir",Gtk::RESPONSE_OK);
	fileChooser.add_button("Cancelar",Gtk::RESPONSE_CANCEL);
	Glib::RefPtr<Gtk::FileFilter> filtroImagen = Gtk::FileFilter::create();
	filtroImagen->set_name("Imágenes");
	filtroImagen->add_pattern("*.jpg");
	filtroImagen->add_pattern("*.png");
	fileChooser.add_filter(filtroImagen);
	int result=  fileChooser.run();
	switch(result){
		case (Gtk::RESPONSE_OK) :{
			nImagenes ++;
			std::string imagen = fileChooser.get_filename();
			Gtk::TreeModel::iterator iter = lista->append();
			Gtk::TreeModel::Row row = *iter;
			row.set_value(0,imagen);
			break;
		}
		case (Gtk::RESPONSE_CANCEL):
			break;
	}
}
void DialogoAgregarProducto::eliminarImagen(){
	Glib::RefPtr<Gtk::TreeSelection> selec = listaImagenes.get_selection();
	Gtk::TreeModel::iterator iter = selec->get_selected();
	if(!iter)return;
	lista->erase(iter);
	nImagenes--;
}
/****** OBTENER DATOS ******/

std::string DialogoAgregarProducto::obtenerNombreProducto(){
	return nombreEntry->get_text();
}
std::string DialogoAgregarProducto::obtenerDescripcionProducto(){
	Glib::RefPtr<Gtk::TextBuffer> buffer = descripcionText->get_buffer();
	return buffer->get_text();
}
std::string DialogoAgregarProducto::obtenerIcono(){
	return iconoFile->get_filename();
}
std::vector<std::string> DialogoAgregarProducto::obtenerImagenes(){
	Gtk::TreeModel::iterator iter = lista->get_iter("0");
	std::string  str;
	std::vector<std::string> imagenes;
	for(int i = 0; i < nImagenes; i++){	
		iter->get_value(0,str);
		imagenes.push_back(str);
		iter++;
	}
	return  imagenes;
}
