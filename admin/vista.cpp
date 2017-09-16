#include "vista.h"

/****** CONSTRUCTOR ******/

Vista::Vista(){

	builder = Gtk::Builder::create();
	builder -> add_from_file("glade/principal.glade");

	builder -> get_widget("ventanaPrincipal", ventanaPrincipal);

	builder -> get_widget_derived("productoBox", productoBox);	
	builder -> get_widget_derived("areasVisionBox",areaVisionBox);
	builder -> get_widget_derived("generalBox",generalBox);
	
	builder -> get_widget("notebook", notebook);

	notebook->signal_switch_page().connect(sigc::mem_fun(this, &Vista::cambiarActual));
	//sig_informacionProductos.emit();
}

/****** CONEXION DE SEÑALES ******/

sigc::signal<void, std::string> Vista::signal_stockAreaVision(){
	return areaVisionBox->signal_stockAreaVision();
}
sigc::signal<void, std::string, std::string, std::string> Vista::signal_modificarAreaVision(){
	return areaVisionBox->signal_modificarAreaVision();
}
sigc::signal<void, std::string, std::string> Vista::signal_altaAreaVision(){
	return areaVisionBox->signal_altaAreaVision();
}
sigc::signal<void,std::string,std::string, std::string,std::string ,std::vector<std::string> > Vista::signal_modificarProducto(){
	return productoBox->signal_modificarProducto();
}
sigc::signal<void,std::string> Vista::signal_bajaProducto(){
	return productoBox->signal_bajaProducto();
}
sigc::signal<void, std::string> Vista::signal_bajaAreaVision(){
	return areaVisionBox->signal_bajaAreaVision();
}
sigc::signal<void, std::string, std::string, std::string, std::vector<std::string> > Vista::signal_altaProducto(){
	return productoBox->signal_altaProducto();
}
sigc::signal<void> Vista::signal_informacionProductos(){
	return sig_informacionProductos;
}
sigc::signal<void> Vista::signal_stockGeneral(){
	return sig_stockGeneral;
}
sigc::signal<void, std::string, std::string, std::string>Vista::signal_stockHistoricoProducto(){
	return productoBox->signal_stockHistoricoProducto();
}
sigc::signal<void> Vista::signal_informacionAreasVision(){
	return sig_informacionAreasVision;
}

sigc::signal<void, std::string> Vista::signal_imagenesProducto()
{
	return productoBox->signal_imagenesProducto();
}

/****** OTROS METODOS ******/

Gtk::Window& Vista::obtenerVentanaPrincipal(){
	return *ventanaPrincipal;
}
void Vista::cambiarActual(Gtk::Widget* page,guint idx){
	if(page == productoBox)	cargarProductos();
	else if (page == areaVisionBox) cargarAreasVision();
	else if (page == generalBox) cargarGeneral();
}
void Vista::cargarGeneral(){
	sig_stockGeneral.emit();
}
void Vista::cargarProductos(){
	sig_informacionProductos.emit();	
}
void Vista::cargarAreasVision(){
	sig_informacionAreasVision.emit();
}

/****** METODOS RELACIONADOS CON LA ADMINISTRACION ******/

void Vista::recibirStockProducto(std::vector<int> stock){
	productoBox->recibirStockProducto(stock);
}
void Vista::recibirImagenesProducto(std::vector<std::string> imagenes){
	productoBox->modificarProducto(imagenes);
}
void Vista::recibirStockAreaVision(std::vector<std::pair<std::string,int> > stock,std::vector<std::string> iconos){
	areaVisionBox->recibirStockAreaVision(stock,iconos);
}
void Vista::recibirStockGeneral(std::vector<std::string> productos, std::vector<std::string> iconos, std::vector<int> stock){
	generalBox->actualizarDatos(productos,iconos,stock);
}
void Vista::recibirStockGeneral(std::vector<std::pair<std::string,int> > stock){
	generalBox->recibirStockGeneral(stock);
}
void Vista::recibirInformacionProductos(std::vector<std::string> productos, std::vector<std::string> ids, std::vector<std::string> descripciones , std::vector<std::string> iconos){
	productoBox->actualizarDatos(productos,ids, descripciones,iconos);
}
void Vista::recibirInformacionAreasVision(std::vector<std::string> areasVision, std::vector<std::string> ids,std::vector<std::string> tiposAreasVision){
	areaVisionBox -> actualizarDatos(areasVision,ids, tiposAreasVision);
}

/****** DESTRUCTOR ******/

Vista::~Vista(){}
