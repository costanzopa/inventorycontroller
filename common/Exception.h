/*
 * Exception.h
 *
 *  Created on: 02/06/2015
 *      Author: pablito
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <string>

#include <exception>

namespace exceptions {

class Exception: public std::exception {
public:
	Exception();
	Exception(const std::string& reason);
	virtual ~Exception() throw();
	virtual const char* what() const throw();
	virtual const std::string className() const;

private:
	//Metodos Privados
	const std::string& getReason() const;

	//Miembros privados
	std::string reason;
};

class SocketException: public Exception {
public:
	SocketException();
	SocketException(const std::string& reason);
	virtual ~SocketException() throw();
	virtual const std::string className() const;
};

class ThreadException:public Exception {
public:
	ThreadException();
	ThreadException(const std::string& reason);
	virtual ~ThreadException() throw();
	virtual const std::string className() const;
};

class FileException: public Exception {
public:
	FileException();
	FileException(const std::string& reason);
	virtual ~FileException() throw();
	virtual const std::string className() const;
};

class XmlException: public Exception {
public:
	XmlException();
	XmlException(const std::string& reason);
	virtual ~XmlException() throw();
	virtual const std::string className() const;
};

class DirectoryException: public Exception {
public:
	DirectoryException();
	DirectoryException(const std::string& reason);
	virtual ~DirectoryException() throw();
	virtual const std::string className() const;
};

} /* namespace exceptions */
#endif /* EXCEPTION_H_ */
