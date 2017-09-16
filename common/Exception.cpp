/*
 * Exception.cpp
 *
 *  Created on: 02/06/2015
 *      Author: pablito
 */

#include "Exception.h"

namespace exceptions {

// Excepcion Base

Exception::Exception() {
	this->reason = "Excepcion Desconocida.";
}

Exception::Exception(const std::string& reason) {
	this->reason = reason;
}

Exception::~Exception() throw() {
	// TODO Auto-generated destructor stub
}

const char* Exception::what() const throw() {
    std::string exception = this->className() + this->getReason();
	return exception.c_str();
}

const std::string Exception::className() const {
	std::string className("[Exception]-- ");
	return className;
}

const std::string& Exception::getReason() const{
	return reason;
}

//Excepcion Socket
SocketException::SocketException():Exception() {
}

SocketException::SocketException(const std::string& reason):Exception(reason) {
}

SocketException::~SocketException() throw() {
	// TODO Auto-generated destructor stub
}

const std::string SocketException::className() const {
	std::string className("[SocketException]-- ");
	return className;
}

//Excepcion Thread
ThreadException::ThreadException():Exception() {
}

ThreadException::ThreadException(const std::string& reason):Exception(reason) {
}

ThreadException::~ThreadException() throw() {
	// TODO Auto-generated destructor stub
}

const std::string ThreadException::className() const {
	std::string className("[ThreadException]-- ");
	return className;
}

//Excepcion File
FileException::FileException():Exception() {
}

FileException::FileException(const std::string& reason):Exception(reason) {
}

FileException::~FileException() throw() {
	// TODO Auto-generated destructor stub
}

const std::string FileException::className() const {
	std::string className("[FileException]-- ");
	return className;
}

//Excepcion XML
XmlException::XmlException():Exception() {
}

XmlException::XmlException(const std::string& reason):Exception(reason) {
}

XmlException::~XmlException() throw() {
	// TODO Auto-generated destructor stub
}

const std::string XmlException::className() const {
	std::string className("[XmlException]-- ");
	return className;
}

//Excepcion Directorio
DirectoryException::DirectoryException():Exception() {
}

DirectoryException::DirectoryException(const std::string& reason):Exception(reason) {
}

DirectoryException::~DirectoryException() throw() {
	// TODO Auto-generated destructor stub
}

const std::string DirectoryException::className() const {
	std::string className("[DirectoryException]-- ");
	return className;
}
} /* namespace exceptions */
