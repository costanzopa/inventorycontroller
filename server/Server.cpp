/*
 * Server.cpp
 *
 *  Created on: 27/05/2015
 *      Author:
 */

#include "Server.h"

namespace inventory {

Server::Server(const std::string& port, const int queue, config::CatalogConfig* catalogConfig)
			  :serverSocket(port,queue) {
	try {
		this->catalogPath = catalogConfig->getCatalogPath();
		catalog::CatalogFile file(catalogPath);
		this->catalog = file.getCatalog();
		this->catalog->setProductsPath(catalogConfig->getProductsPath());
		this->catalog->setVisionAreasPath(catalogConfig->getVisionAreasPath());
		std::cout<<"Se ha cargado el archivo de configuracion."<<std::endl;
	} catch (std::exception& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

Server::~Server() {
	try {
		std::vector< requests::Request * >::iterator it = requests.begin();
		while (it != requests.end()) {
			delete (*it);
			it++;
		}
	} catch(std::exception& e) {
		e.what();
	}
}

void* Server::process() {
	net::Communication* clientSocket = NULL;
	try {
		while(this->isRunning()) {
			clientSocket = new net::Communication();
			this->serverSocket.accept(clientSocket);
			requests::Request* request = new requests::Request(clientSocket,this->catalog);
			this->requests.push_back(request);
			request->start();
		}
	} catch(std::exception  &e) {
		e.what();
		if (clientSocket!=NULL)
			delete clientSocket;
		return (void*) NULL;
	}
	return (void*) NULL;
}

void Server::stop() {
	try {
		this->serverSocket.interrupt();
	} catch(exceptions::SocketException& e) {
		e.what();
	}
}



} /* namespace inventory */
