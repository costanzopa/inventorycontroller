/*
 * Socket.h
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstddef>  /* Tipo "size_t". */
#include <netdb.h>  /* Struct "addrinfo". */
#include <sys/socket.h>
#include "Exception.h"
#include <cstring>
#include <iostream>
#include <cerrno>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>


#define INVALID_SOCKET -1
#define VALID_RETURN 0

namespace net {

class Socket {
public:

	Socket();
    /*
	* Intenta crear y abrir un socket en modo "server".
	*/
	Socket(const std::string &puerto, const unsigned int conexiones);
	/*
	 * Intenta crear y abrir un socket en modo "client".
	 */
	Socket(const std::string &host, const std::string &puerto);
	/*
	 * Libera los recursos del socket y lo cierra.
	 */
	virtual ~Socket();
	/*
	 * Acepta una nueva conexion por parte del cliente.
	 */
	void accept(Socket* socket);
	/*
	 *Intenta interrumpir la conexion de un socket.
	 */
	void interrupt();
	/*
	 * SI el socket no se interrupio, lo interrumpe y luego lo cierra.
	 */
	void close();
	/*
	 * Metodos obstractos que deben definir el
	 * protocolo de envio y recepcion del cliente-servidor.
	 */

	ssize_t send(const void * const buffer, const size_t bufferSize) const;
	ssize_t receive(void*  const buffer, const size_t bufferSize) const;


private:
	//Metodos privados
	/*Constructor por copia declarado privado pero no definido
	 * no se deben copiar las instancias de "Socket").
	 */
	Socket(const Socket &socket);
	/*
	 * Operador asignacion de copia declarado privado pero no definido
	 * (no se deben copiar las instancias de "Socket").
	 */
	Socket& operator=(const Socket &socket);
	void create();
	void bind();
	void listen(const int queue);
	void connect();
	/* Carga la información de pre-configuracion del socket
	 * (flags, familia de direcciones, tipo de socket, y protocolo).
	 * Es virtual para que se pueda elegir cuales clases derivadas la redefinen y cuales no.
	*/
	virtual void initializeProtocol(struct addrinfo* const protocol);
	void initializeSocket();
	void configServer(const std::string &port,const int queue);
	void bindServer(const int conexiones);
	void configClient(const std::string &host, const std::string &puerto);
	void connectClient();
	const bool& hasInterrupt() const;

	//Setters
	void setInterrupt(const bool interrupt);
	void setSocketId(const int socketId);
	void setSocketInfo(struct addrinfo* const socketInfo);
	void setSocketInfoUsed(struct addrinfo* const socketInfoUsed);
	const int& getSocketId() const;


	//Miembros de clase
	int socketId;
	struct addrinfo* socketInfo;
	struct addrinfo* socketInfoUsed;
	bool isInterrupt;
};

} /* namespace net */
#endif /* SOCKET_H_ */
