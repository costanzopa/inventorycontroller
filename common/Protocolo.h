/*
 * Protocolo.h
 *
 *  Created on: Jun 9, 2015
 *      Author: horacio
 */

#ifndef TPFINAL_COMMON_PROTOCOLO_H_
#define TPFINAL_COMMON_PROTOCOLO_H_

#include <string>
#include <vector>

#include "StringUtils.h"

namespace net {
class Communication;
} /* namespace net */

class Protocolo {
	public:
	Protocolo(net::Communication *comunicador);
	std::string concatenarMensaje(std::vector<std::string>& parametros);
		void tokenizarMensaje(std::string mensaje,std::vector<std::string> &vectorMensaje);
		void getAreasDeVision(std::vector<std::string> &areasDeVision);
		void getProductos(std::vector<std::string> &productos);
		void modificarAreaVision(std::string id, std::string nombre, std::string tipo);
		void modificarProducto(std::string id, std::string nombre, std::string descripcion, std::string icono,std::vector<std::string> imagenes);
		void enviarImagen(bool png, bool featureMatching,
		const std::string &areaDeVision,
		const std::string &fechaYHora,
		const std::string &bytesImagen);
		void getHistorico(std::string idProducto, std::string desde, std::string hasta, std::vector<int>& hist);
		void enviarVideo(bool featureMatching, const std::string &areaDeVision,
		const std::string &fechaYHora,
		const std::string &bytesImagen);
		void getImagenesDeProducto(const std::string &producto, std::vector<std::string> &imagenes, std::vector<std::string> &extensiones);
		void getImagenesProducto(const std::string &id, std::vector<std::string> &imagenes);
		void getStockGeneral(std::vector<std::pair<std::string, int> >& stock);
		void getTiposAreasVision(std::vector<std::string>& areasVision, std::vector<std::string>& ids,std::vector<std::string>& tipos);
		void altaAreaVision(std::string nombre, std::string tipo);
		void bajaAreaVision(std::string id);
		void altaProducto(std::string nombre, std::string descripcion, std::string icono, std::vector<std::string> imagenes);
		void bajaProducto(std::string id);
		void getDetallesProductos(std::vector<std::string>& productos, std::vector<std::string>& ids, std::vector<std::string>& descripciones, std::vector<std::string>& iconos);
	private:
		net::Communication *comunicador;
		utils::StringUtils stringUtils;
};

#endif /* TPFINAL_COMMON_PROTOCOLO_H_ */
