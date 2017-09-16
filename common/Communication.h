/*
 * Communication.h
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#define BUFFERSIZE 1024

#include "Socket.h"
#include <stdlib.h>
#include "Exception.h"
#include <iostream>
#include <sstream>
#include "../common/StringUtils.h"


namespace net {

class Communication {
public:
	Communication();
	/**
	 * El constructor utilizado para iniciar el servidor.
	 * @param port puerto en el cual se conecta el servidor
	 * @param queue La cantidad de conexiones disponibles a esperar
	 * en el connect.
	 */
	Communication(const std::string &port, const int queue);
	/**
	 * El constructor utilizado para iniciar al cliente.
	 * @param host Host al cual se conestara el servidor
	 * @param port Puerto utilizado para conectarse al servidor
	 */
	Communication(const std::string &host, const std::string &puerto);
	/**
	 *
	 * @param
	 * @param
	 */
	 void accept(Communication* communication);

	 /**
	  * Destructor
	 */
	 virtual ~Communication();

	 void interrupt();

	 void sendFile(const std::string& extension);
     virtual void send(const std::string& size);
	 void receiveFile(std::string& path, int size);
	 virtual void receive(std::string& msj);
     virtual void receiveOfSize(ssize_t size,std::string& mensaje);

	 void sendFileWithName(const std::string& path);
	private:
	const Socket& getSocket() const;
	Socket* socket;
	std::string porcionMsjFaltante;
};

} /* namespace net */
#endif /* COMMUNICATION_H_ */
