/*
 * Request.h
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "threads/Thread.h"
#include "../common/Communication.h"
#include "catalog/Catalog.h"
#include "Matcher.h"
#include <stdlib.h>
#include "../common/Stock.h"
#include "catalog/VisionArea.h"

namespace requests {

class Request: public threads::Thread {
public:
	Request(net::Communication* const socket,
			catalog::Catalog* const config);
	virtual ~Request();
	void executeRequest(const std::string& request);
	net::Communication* getCommunication() const;
	virtual void stop();

	void getAreas();
	void receiveImage(std::string path);
	void detallesProductos();
	void imagenesDeProducto(const std::vector<std::string>& splitVector);
	private:
	//Metodos privados
	virtual void* process();
	//Request
	void createVisionArea(const std::vector<std::string> &splitVector);
	void modifyVisionArea(const std::vector<std::string> &splitVector);
	void deleteVisionArea(const std::vector<std::string> &splitVector);
	void createProduct(const std::vector<std::string> &splitVector);
	void modifyProduct(const std::vector<std::string> &splitVector);
	void deleteProduct(const std::vector<std::string> &splitVector);
	void listAreas();
	void listProducts();
	void listProductImages(const std::vector<std::string> &splitVector);
	void detailsProduct(catalog::Product& producto);
	void listStockGeneral(const std::vector<std::string> &splitVector);
	void listStockArea(const std::vector<std::string> &splitVector);
	void listStockHistoric(const std::vector<std::string> &splitVector);
	void processFile(const std::vector<std::string> &splitVector);
	void processVideo(const std::vector<std::string> &splitVector);

	//Miembros de clase privados
	net::Communication* socket;
	catalog::Catalog* catalog;
	utils::Stock file;

	Request(const Request &request);
	Request& operator=(const Request &request);
};

} /* namespace requests */
#endif /* REQUEST_H_ */
