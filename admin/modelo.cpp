#include "modelo.h"

/****** CONSTRUCTOR ******/

Modelo::Modelo(std::string puerto){
	com = new net::Communication("localhost",puerto);
}

/****** ABM DE ÁREAS DE VISIÓN ******/

void Modelo::modificarAreaVision(std::string id,std::string areaVisionNuevo,std::string tipoNuevo){

	Protocolo protocolo(com);
	protocolo.modificarAreaVision(id,areaVisionNuevo,tipoNuevo);
} 
void Modelo::altaAreaVision(std::string areaVision, std::string tipo){

	Protocolo protocolo (com);
	protocolo.altaAreaVision(areaVision,tipo);
}
void Modelo::bajaAreaVision(std::string id){

	Protocolo protocolo(com);

	protocolo.bajaAreaVision(id);
}

/****** ABM DE PRODUCTOS ******/

void Modelo::bajaProducto(std::string id){
	Protocolo protocolo(com);
	protocolo.bajaProducto(id);
}
void Modelo::altaProducto(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes){
	Protocolo protocolo (com);
	protocolo.altaProducto(producto,descripcion,icono,imagenes);
}

/****** CONSULTAS DE STOCK ******/

std::vector<std::pair<std::string,int> > Modelo::obtenerStockGeneral(){
	stockGeneral.clear();
	Protocolo protocolo(com);
	protocolo.getStockGeneral(stockGeneral);
	return stockGeneral;
}
std::vector<int> Modelo::obtenerStockProducto(std::string producto, std::string desde, std::string hasta){
	Protocolo protocolo(com);
	std::vector<int> stockProducto;
	protocolo.getHistorico(producto,desde,hasta,stockProducto);
	return stockProducto;
}
std::vector<std::pair<std::string, int> > Modelo::obtenerStockAreaVision(std::string aVision){
	std::vector<std::pair<std::string, int> > stockAreaVision;
	if(aVision == areasVision[0]) stockAreaVision = stockAreaVision1;
	else if(aVision == areasVision[1]) stockAreaVision = stockAreaVision2;
	return stockAreaVision;
}

/****** LISTADOS E INFORMACIÓN DE PRODUCTOS Y ÁREAS DE VISIÓN ******/

void Modelo::obtenerInformacionProductos(){
	//Acá se piden los nombres, descripciones e íconos de los productos al servidor. Con los métodos que están a continuación,
	//el controlador se los envía a la vista.
}

std::vector<std::string> Modelo::obtenerImagenesProducto(std::string id){
	Protocolo protocolo(com);
	std::vector<std::string> imagenes;
	protocolo.getImagenesProducto(id,imagenes);
	return imagenes;
}
std::vector<std::string> Modelo::obtenerListadoProductos(){

	Protocolo protocolo(com);
	productos.clear();
	descripcionesProductos.clear();
	iconosProductos.clear();
	ids.clear();
	protocolo.getDetallesProductos(productos,ids,descripcionesProductos,iconosProductos);
	return productos;
}

std::vector<std::string> Modelo::obtenerIconosProductos(){
	return iconosProductos;
}

std::vector<std::string> Modelo::obtenerIdsProductos()
{
	return ids;
}

std::vector<std::string> Modelo::obtenerIdsAreasVision()
{
	return areasVisionId;
}
std::vector<std::string> Modelo::obtenerDescripcionesProductos(){
	return descripcionesProductos;
}

std::vector<std::string> Modelo::obtenerListadoAreasVision(){
	Protocolo protocolo(com);
	areasVision.clear();
	tiposAreasVision.clear();
	areasVisionId.clear();
	protocolo.getTiposAreasVision(areasVision,areasVisionId,tiposAreasVision);
	return areasVision;
}
std::vector<std::string> Modelo::obtenerTiposAreasVision(){
	return tiposAreasVision;
}

void Modelo::modificarProducto(std::string id, std::string nombre, std::string descripcion, std::string icono, std::vector<std::string> imagenes)
{
	Protocolo protocolo(com);
	protocolo.modificarProducto(id,nombre,descripcion,icono,imagenes);
}

/****** DESTRUCTOR ******/

Modelo::~Modelo(){
	//delete com;
}
