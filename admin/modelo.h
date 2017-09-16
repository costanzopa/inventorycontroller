#ifndef MODELO
#define MODELO

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "../common/Communication.h"
#include "../common/Protocolo.h"

class Modelo{
	private:
		net::Communication* com;


		/*Lo siguiente, en la versión final NO VA.*/
		std::vector<std::string> ids;
		std::vector<std::string> areasVisionId;
		std::vector<std::string> areasVision;
		std::vector<std::string> tiposAreasVision;
		std::vector<std::string> productos;
		std::vector<std::string> descripcionesProductos;
		std::vector<std::string> iconosProductos;
		std::vector<std::string> imagenesProductos;
		std::vector<std::pair<std::string, int> > stockAreaVision1;
		std::vector<std::pair<std::string, int> > stockAreaVision2;
		std::vector<std::pair<std::string,int> > stockGeneral;
		std::vector<std::string> imagenes1;
		std::vector<std::string> imagenes2;
		std::vector<int> stockProducto1;
		std::vector<int> stockProducto2;

	public:

		/****** CONSTRUCTOR ******/

		Modelo(std::string puerto);

		/***** ABM DE ÁREAS DE VISIÓN ******/

		void modificarAreaVision(std::string id ,std::string areaVisionNuevo, std::string tipoNuevo);
		void bajaAreaVision(std::string id);
		void altaAreaVision(std::string areaVision, std::string tipo);

		/****** ABM DE PRODUCTOS ******/

		void altaProducto(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes);
		void bajaProducto(std::string producto);

		/****** CONSULTAS DE STOCK ******/

		std::vector<std::string> obtenerListadoProductos();
		std::vector<std::string> obtenerImagenesProducto(std::string id);
		std::vector<std::string> obtenerIconosProductos();
		std::vector<std::string> obtenerIdsProductos();
		std::vector<std::string> obtenerIdsAreasVision();
		std::vector<std::string> obtenerDescripcionesProductos();
		void obtenerInformacionProductos();
		std::vector<std::string> obtenerListadoAreasVision();
		std::vector<std::pair<std::string, int> > obtenerStockGeneral();
		std::vector<int> obtenerStockProducto(std::string producto, std::string desde, std::string hasta);
		std::vector< std::pair<std::string, int> > obtenerStockAreaVision(std::string aVision);
		std::vector<std::string> obtenerTiposAreasVision();
		void modificarProducto(std::string id,std::string nombre, std::string descripcion,std::string icono, std::vector<std::string> imagenes);
		
		/****** DESTRUCTOR ******/
		
		~Modelo();		

};

#endif
