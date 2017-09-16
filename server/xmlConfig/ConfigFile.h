/*
 * ConfigFile.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include "XmlFile.h"
#include "Configuration.h"

namespace config {

class ConfigFile: public xml::XmlFile {
public:
	ConfigFile();
	explicit ConfigFile(const std::string& filename);
	virtual ~ConfigFile();
	virtual void add(xml::XmlElement* element);
	Configuration* getConfig() const;

private:
	Configuration* config;
};

} /* namespace config */
#endif /* CONFIGFILE_H_ */
