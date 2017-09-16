9/*
 * Server.h
 *
 *  Created on: 27/05/2015
 *      Author: pablito
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "threads/Thread.h"
#include "Request.h"
#include "../common/Communication.h"
#include <vector>
#include "../common/Exception.h"
#include "xmlConfig/ConfigFile.h"
#include "xmlConfig/CatalogFile.h"
#include "catalog/Catalog.h"
#include "xmlConfig/CatalogConfig.h"


namespace inventory {

class Server: public threads::Thread {
public:
	Server(const std::string& port, const int queue, config::CatalogConfig* catalogConfig);
	virtual ~Server();
	virtual void stop();

private:
	//Metodos privados
	virtual void* process();
	Server(const Server &Server);
	Server& operator=(const Server &server);

	//Miembros de la clase
	std::vector<requests::Request*> requests;
	net::Communication serverSocket;
	catalog::Catalog* catalog;
	std::string catalogPath;
};

} /* namespace inventory */
#endif /* SERVER_H_ */
