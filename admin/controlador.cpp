#include "controlador.h"

/****** CONSTRUCTOR ******/

void Controlador::iniciar()
{
	obtenerInformacionProductos();
}

Controlador::Controlador(Modelo& modelo,Vista& vista):modelo(modelo),vista(vista){
	vista.signal_stockHistoricoProducto().connect(sigc::mem_fun(this,&Controlador::obtenerStockProducto));
	vista.signal_informacionProductos().connect(sigc::mem_fun(this, &Controlador::obtenerInformacionProductos));
	vista.signal_informacionAreasVision().connect(sigc::mem_fun(this, &Controlador::obtenerInformacionAreasVision));
	vista.signal_stockGeneral().connect(sigc::mem_fun(this,&Controlador::obtenerStockGeneral));
	vista.signal_stockAreaVision().connect(sigc::mem_fun(this,&Controlador::obtenerStockAreaVision));
	vista.signal_bajaProducto().connect(sigc::mem_fun(this,&Controlador::bajaProducto));
	vista.signal_altaProducto().connect(sigc::mem_fun(this,&Controlador::altaProducto));
	vista.signal_bajaAreaVision().connect(sigc::mem_fun(this,&Controlador::bajaAreaVision));
	vista.signal_altaAreaVision().connect(sigc::mem_fun(this, &Controlador::altaAreaVision));
	vista.signal_modificarAreaVision().connect(sigc::mem_fun(this,&Controlador::modificarAreaVision));

	vista.signal_imagenesProducto().connect(sigc::mem_fun(this, &Controlador::imagenesProducto));
	vista.signal_modificarProducto().connect(sigc::mem_fun(this,&Controlador::modificarProducto));
}


/****** ALTA, BAJA Y MODIFICACIÓN DE ÁREAS DE VISIÓN ******/

void Controlador::modificarAreaVision(std::string id, std::string areaVisionNuevo, std::string tipoNuevo){
	modelo.modificarAreaVision(id, areaVisionNuevo,tipoNuevo);
	//Actualizo
	obtenerInformacionAreasVision();
}
void Controlador::altaAreaVision(std::string areaVision, std::string tipo){
	modelo.altaAreaVision(areaVision,tipo);
	//Actualizo
	obtenerInformacionAreasVision();
}
void Controlador::bajaAreaVision(std::string id){
	modelo.bajaAreaVision(id);
	//Actualizo
	obtenerInformacionAreasVision();
}

/****** ALTA, BAJA Y MODIFICACIÓN DE PRODUCTOS ******/

void Controlador::imagenesProducto(std::string id){
	std::vector<std::string> imagenes = modelo.obtenerImagenesProducto(id);
	vista.recibirImagenesProducto(imagenes);
}
void Controlador::bajaProducto(std::string id){
	modelo.bajaProducto(id);
	obtenerInformacionProductos();
}
void Controlador::altaProducto(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes){
	modelo.altaProducto(producto,descripcion,icono,imagenes);
	obtenerInformacionProductos();
}
void Controlador::modificarProducto(std::string id,std::string nombre, std::string descripcion,std::string icono ,std::vector<std::string> imagenes){
	modelo.modificarProducto(id,nombre,descripcion,icono,imagenes);
	obtenerInformacionProductos();
}

/****** CONSULTAS DE STOCK ******/

void Controlador::obtenerStockAreaVision(std::string areaVision){
	std::vector<std::pair<std::string, int> > stock = modelo.obtenerStockAreaVision(areaVision);
	std::vector<std::string> iconos = modelo.obtenerIconosProductos();
	vista.recibirStockAreaVision(stock,iconos);
}
void Controlador::obtenerStockGeneral(){
	std::vector<std::pair<std::string, int > > stock = modelo.obtenerStockGeneral();
	std::vector<std::string> iconos = modelo.obtenerIconosProductos();
	std::vector<std::string> productos = modelo.obtenerListadoProductos();
	std::vector<int> stock1;
	for(int i = 0; i < stock.size(); i++){
		stock1.push_back(stock[i].second);
	}
	vista.recibirStockGeneral(productos,iconos,stock1);
}
void Controlador::obtenerInformacionProductos(){
	modelo.obtenerInformacionProductos();
	std::vector<std::string> listado = modelo.obtenerListadoProductos();
	std::vector<std::string> descripciones = modelo.obtenerDescripcionesProductos();
	std::vector<std::string> iconos = modelo.obtenerIconosProductos();
	std::vector<std::string> ids = modelo.obtenerIdsProductos();
	vista.recibirInformacionProductos(listado,ids, descripciones,iconos);
}
void Controlador::obtenerInformacionAreasVision(){
	std::vector<std::string> areasVision = modelo.obtenerListadoAreasVision();
	std::vector<std::string> tiposAreasVision = modelo.obtenerTiposAreasVision();
	std::vector<std::string> ids = modelo.obtenerIdsAreasVision();
	vista.recibirInformacionAreasVision(areasVision,ids,tiposAreasVision);
}
void Controlador::obtenerStockProducto(std::string producto,std::string desde, std::string hasta){
	std::vector<int> stock = modelo.obtenerStockProducto(producto,desde,hasta);
	vista.recibirStockProducto(stock);
}
