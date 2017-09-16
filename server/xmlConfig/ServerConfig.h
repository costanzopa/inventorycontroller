/*
 * ServerConfig.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef SERVERCONFIG_H_
#define SERVERCONFIG_H_

#include "XmlElement.h"
#include "../../common/StringUtils.h"
#include <stdlib.h>

namespace config {

class ServerConfig: public xml::XmlElement {
public:
	ServerConfig();
	explicit ServerConfig(const std::string& className);
	virtual ~ServerConfig();
	virtual void complete(const std::string& attributes);
	virtual const std::string& getClassName();
	unsigned int getQueue() const;
	const std::string& getHost() const;
	const std::string& getPort() const;

private:
	unsigned int queue;
	std::string host;
	std::string port;
};

} /* namespace config */
#endif /* SERVERCONFIG_H_ */
