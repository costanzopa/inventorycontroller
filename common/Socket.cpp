/*
 * Socket.cpp
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#include "Socket.h"

namespace net {

Socket::Socket() {
	this->initializeSocket();
}

Socket::Socket(const std::string &port, const unsigned int queue) {
	try {
		this->initializeSocket();
		this->configServer(port, queue);
	} catch (exceptions::SocketException& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

Socket::Socket(const std::string &host, const std::string &port) {
	try {
		this->initializeSocket();
		this->configClient(host,port);
	} catch (exceptions::SocketException& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

void Socket::initializeSocket() {
	 this->setInterrupt(false);
	 this->setSocketId(INVALID_SOCKET);
	 this->setSocketInfo(NULL);
	 this->setSocketInfoUsed(NULL);
}

void Socket::configServer(const std::string &port, const int queue) {
	struct addrinfo protocol;
	initializeProtocol(&protocol);
	protocol.ai_flags |= AI_PASSIVE;

	int error = ::getaddrinfo(NULL, port.c_str(), &protocol, &socketInfo);

	if (error != VALID_RETURN) {
		throw exceptions::SocketException("Error al generar el addrinfo.");
	}
	for (socketInfoUsed = socketInfo; socketInfoUsed != NULL;
			socketInfoUsed = socketInfoUsed->ai_next) {
		try {
			this->bindServer(queue);
		}catch (exceptions::SocketException &excepcion) {
			continue;
		}
		break;
		if (socketInfoUsed == NULL) {
			::freeaddrinfo(socketInfo);
			socketInfo = NULL;
			std::string error("Error al conectar el socket Servidor.");
			throw exceptions::SocketException(error);
		}
	}
}

void Socket::configClient(const std::string &host,
		const std::string &port) {
	struct addrinfo protocol;
	initializeProtocol(&protocol);
	protocol.ai_flags |= AI_PASSIVE;

	int error = ::getaddrinfo(host.c_str(), port.c_str(),
			&protocol, &socketInfo);

	if (error != VALID_RETURN) {
		throw exceptions::SocketException("Error al generar el addrinfo.");
	}
	for (socketInfoUsed = socketInfo; socketInfoUsed != NULL;
			socketInfoUsed = socketInfoUsed->ai_next) {
		try {
			this->connectClient();
		}catch (exceptions::SocketException &exception) {
			continue;
		}
		break;
		if (socketInfoUsed == NULL) {
			::freeaddrinfo(socketInfo);
			socketInfo = NULL;
			throw exceptions::SocketException("Error al conectar el cliente.");
		}
	}
}

void Socket::bindServer(const int queue) {
	try {
		this->create();
		this->bind();
		this->listen(queue);
	} catch( exceptions::SocketException &exception) {
		int validId = this->getSocketId();
		if (validId != INVALID_SOCKET) {
			::close(validId);
			this->setSocketId(INVALID_SOCKET);
		}
		throw;
	}
}

void Socket::connectClient() {
	try {
		this->create();
		this->connect();
	}catch(exceptions::SocketException& excepcion) {
		int idValido = this->getSocketId();
		if (idValido != INVALID_SOCKET) {
		    ::close(idValido);
			this->setSocketId(INVALID_SOCKET);
		}
		throw;
	}
}

Socket::~Socket() {
	try {
		this->close();
	} catch (exceptions::SocketException& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

void Socket::create() {
	int family = socketInfoUsed->ai_family;
	int type = socketInfoUsed->ai_socktype;
	int protocol = socketInfoUsed ->ai_protocol;
	socketId = socket(family, type, protocol);
	if (socketId < VALID_RETURN)
		throw exceptions::SocketException("ERROR al crear el socket.");
}

void Socket::connect() {
	int id = this->getSocketId();
	int error = 0;
	error = ::connect(id, socketInfoUsed->ai_addr,
			socketInfoUsed->ai_addrlen);
	if (error != VALID_RETURN) {
	    throw exceptions::SocketException("ERROR al conectar.");
	}
}

void Socket::bind() {
	int id = this->getSocketId();
	int yes = 1;
	const int opcionesError = ::setsockopt(id, SOL_SOCKET,
			SO_REUSEADDR, &yes, sizeof(int));
	    if (opcionesError != VALID_RETURN) {
	    	throw exceptions::SocketException("ERROR en las opciones al bindear.");
	    }
	    int error = ::bind(id, socketInfoUsed->ai_addr,
	    		socketInfoUsed->ai_addrlen);
	    if (error != VALID_RETURN) {
	      throw exceptions::SocketException("ERROR al realizar bind");
	    }
}

void Socket::accept(Socket* socket) {
		struct sockaddr_in cliSockAddr;
	    socklen_t cliSockAddrSize = sizeof (cliSockAddr);
	    int id = this->getSocketId();
	    int acceptError = ::accept(id, (struct sockaddr*) &cliSockAddr,
	    		&cliSockAddrSize);
	    if (acceptError >= VALID_RETURN) {
	    	socket->setSocketId(acceptError);
	    } else {
	    	throw exceptions::SocketException("ERROR al aceptar una conexion.");
	    }
}

void Socket::listen(const int queue) {
	 int id = this->getSocketId();
	 const int listenError = ::listen(id, queue);
	 if (listenError != VALID_RETURN) {
		 throw exceptions::SocketException("Error al excuchar una conexion.");
	 }
}


ssize_t Socket::send(const void * const buffer, const size_t bufferSize) const {
   const int id = this->getSocketId();
   ssize_t bytesEnviados = ::send(id, buffer, bufferSize, ::MSG_NOSIGNAL);
   if (bytesEnviados==-1) {
	   if ((errno==EBADF) || (errno==EPIPE)) {
		   bytesEnviados = 0;
	   } else {
		   throw exceptions::SocketException("Error al enviar datos.");
	   }
   }
   return bytesEnviados;
 }

ssize_t Socket::receive(void * const buffer, const size_t bufferSize) const {
   const int id = this->getSocketId();
   ssize_t recvBytes = ::recv(id, buffer, bufferSize, 0);
   if (recvBytes==-1) {
 	   if ((errno==EBADF) || (errno==EPIPE)) {
 		  recvBytes = 0;
 	   } else {
 		   throw exceptions::SocketException("ERROR al recibir bytes.");
 	   }
   }
   return recvBytes;
}


void Socket::interrupt() {
	if (!this->hasInterrupt()) {
		this->setInterrupt(true);
		const int id = this->getSocketId();
		const int interrumpirError = ::shutdown(id, SHUT_RDWR);
		if (interrumpirError != VALID_RETURN) {
			throw exceptions::SocketException("ERROR al interrumpir un socket.");
		}
	}
}

void Socket::close() {
	 if (socketInfo != NULL) {
	      ::freeaddrinfo(socketInfo);
	      socketInfo = NULL;
	    }
	    socketInfoUsed = NULL;
	    const int id = this->getSocketId();
	    if (id != INVALID_SOCKET) {
	    	try {
	    		this->interrupt();
	    	} catch (exceptions::SocketException &exception) {
	    		const int closeError = ::close(id);
	    	    this->setSocketId(INVALID_SOCKET);
	    	    if (closeError != VALID_RETURN) {
	    	    	throw exceptions::SocketException("ERROR en el cierre de un socket.");
	    	    }
	    	}

	      const int closeError = ::close(id);
	      this->setSocketId(INVALID_SOCKET);
	      if (closeError != VALID_RETURN) {
	        throw exceptions::SocketException("ERROR en el cierre de un socket.");
	      }
	    }
}

void Socket::initializeProtocol(struct addrinfo* const protocol) {
	::memset(protocol, 0, sizeof *protocol);
	protocol->ai_flags = (AI_V4MAPPED | AI_ADDRCONFIG);
	// Familia de direcciones IPv4 o IPv6.
	protocol->ai_family = AF_UNSPEC;
	// Tipo de socket STREAM.
	protocol->ai_socktype = SOCK_STREAM;
}

const int& Socket::getSocketId() const {
	return (this->socketId);
}

void Socket::setSocketId(const int socketId) {
	this->socketId = socketId;
}

const bool& Socket::hasInterrupt() const {
	return (this->isInterrupt);
}

void Socket::setInterrupt(const bool isInterrupt) {
	this->isInterrupt = isInterrupt;
}

void Socket::setSocketInfo(struct addrinfo* const socketInfo) {
	this->socketInfo = socketInfo;
}

void Socket::setSocketInfoUsed(struct addrinfo* const socketInfoUsado) {
	this->socketInfoUsed = socketInfoUsado;
}
}
