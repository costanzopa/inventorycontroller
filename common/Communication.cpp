/*
 * Communication.cpp
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#include "Communication.h"

#include <sys/types.h>
#include <cstring>
#include <string>

namespace net {

Communication::Communication() {
  socket = new Socket();
  porcionMsjFaltante = "";
}
Communication::Communication(const std::string &port, const int queue) {
  socket = new Socket(port, queue);
}

Communication::Communication(const std::string& host, const std::string& port) {
  socket = new Socket(host, port);
}

Communication::~Communication() {
  delete socket;
}

void Communication::accept(Communication* communication) {
  this->socket->accept(communication->socket);
}

void Communication::interrupt() {
  socket->interrupt();
}
//TODO Implementar protocolo de comunicacion.

void Communication::sendFile(const std::string& path) {
	std::string extension = (path).substr((path).find_last_of('.') + 1);
	utils::StringUtils util;
	std::string bytes,answer;
	unsigned int fsize = util.fileToString(path,bytes);
	std::string size = util.toString(fsize);
	std::string toSend = util.getExtension(extension)+utils::separator+size+ utils::endline;
	this->send(toSend);
	this->receive(answer);
	if (answer == utils::OK_MESSAGE)
		this->send(bytes);
		answer.clear();
		this->receive(answer);
}

void Communication::sendFileWithName(const std::string& path) {
	std::string extension = (path).substr((path).find_last_of('.') + 1);
	std::vector<std::string> vec;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(path,vec,'/');
	std::string bytes,answer;
	unsigned int fsize = util.fileToString(path,bytes);
	std::string size = util.toString(fsize);
	std::string nombre = vec.back();
	std::string toSend = util.getExtension2(extension)+utils::separator+nombre+"|"+size+ utils::endline;
	this->send(toSend);
	this->receive(answer);
	if (answer == utils::OK_MESSAGE)
		this->send(bytes);
		answer.clear();
		this->receive(answer);
}


void Communication::receiveFile(std::string& path,int size) {
	std::string bytes;
	receiveOfSize(size,bytes);
	utils::StringUtils utils;
	utils.stringTofile(bytes,path);
	this->send(utils::OK_MESSAGE);
}

void Communication::send(const std::string& data) {
	ssize_t length = data.length();
	ssize_t send = 0;
	ssize_t error = 0;
	while (length > 0) {
		try {
			error = socket->send(data.c_str() + send, length);
		}catch (exceptions::SocketException &exception) {
			continue;
		}
		if (error == 0) {
			length=0;
			throw exceptions::SocketException("Error en el envio de informacion.");
		}
		send += error;
		length -= error;
	}
}

void Communication::receive(std::string& size) {
  char auxBuffer[BUFFERSIZE];
  memset(auxBuffer, 0, BUFFERSIZE);
  bool exit = false;
  ssize_t received = 0;
  ssize_t error = 0;
  char terminador = '\n';
  std::string mensaje = porcionMsjFaltante;
  while (!exit) {
    try {
      error = socket->receive(auxBuffer + received, BUFFERSIZE - received);
    } catch (exceptions::SocketException &excepcion) {
      continue;
    }
    if (error == 0) {
      throw exceptions::SocketException(
          "ERROR han cerrado el socket al recibir.");
    }
    received += error;
    mensaje += auxBuffer;
    if (mensaje.find(terminador) != std::string::npos) {
      exit = true;
      // recibio de mas :
      if (mensaje.find(terminador) != (mensaje.size() - 1)) {
        this->porcionMsjFaltante = mensaje.substr(
            mensaje.find(terminador) + 1,
            mensaje.size() - (mensaje.find(terminador) + 1));
        mensaje = mensaje.substr(0, mensaje.find(terminador) + 1);
      } else {
        this->porcionMsjFaltante = "";
      }
    }
  }

  size += mensaje;
}


void Communication::receiveOfSize(ssize_t size,std::string& mensajeRecibido) {
  char auxBuffer[size];
  memset(auxBuffer, 0, size);
  bool exit = false;
  ssize_t received = 0;
  ssize_t error = 0;
  while (!exit) {
    try {
      error = socket->receive(auxBuffer + received,size-received);
    } catch(exceptions::SocketException &excepcion) {
      continue;
    }
    if (error == 0) {
      throw exceptions::SocketException(
          "ERROR han cerrado el socket al recibir un tamaño determinado.");
    }
    received += error;
    if (received == size) {
      exit = true;
    }
  }
  std::string aux(auxBuffer,size);
  mensajeRecibido += aux;
}

} /* namespace net */
