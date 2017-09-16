#ifndef CONTROLADOR
#define CONTROLADOR

#include <iostream>
#include "vista.h"
#include "modelo.h"
#include <string>
#include <vector>

class Controlador{
	Modelo& modelo;
	Vista& vista;
	
	public:

		/****** CONSTRUCTOR ******/
		void iniciar();

		Controlador(Modelo& modelo,Vista& vista);

		/****** ABM DE ÁREAS DE VISIÓN ******/
		std::vector<std::string> obtenerIdsAreasVision();
		void altaAreaVision(std::string areaVision, std::string tipo);
		void modificarAreaVision(std::string id, std::string areaVisionNuevo, std::string tipoNuevo);
		void bajaAreaVision(std::string producto);

		/****** ABM DE PRODUCTOS ******/

		void obtenerInformacionProductos();
		void bajaProducto(std::string id);
		void altaProducto(std::string id, std::string descripcion, std::string icono, std::vector<std::string> imagenes);

		/****** CONSULTAS DE STOCK ******/

		void obtenerStockProducto(std::string producto, std::string desde, std::string hasta);
		void obtenerStockGeneral();
		void obtenerStockAreaVision(std::string areaVision);
		void imagenesProducto(std::string id);
		void obtenerInformacionAreasVision();
		void modificarProducto(std::string id,std::string nombre, std::string descripcion, std::string icono,std::vector<std::string> imagenes);
};

#endif
