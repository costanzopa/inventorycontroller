/*
 * VisionArea.h
 *
 *  Created on: 04/06/2015
 *      Author: pablito
 */

#ifndef VISIONAREA_H_
#define VISIONAREA_H_
#include <stdlib.h>
#include "../../common/StringUtils.h"
#include "../xmlConfig/XmlElement.h"
#include "../../common/Constants.h"

namespace catalog {

class VisionArea: public xml::XmlElement {
public:
	explicit VisionArea(const std::string& className);
	VisionArea(const std::string& id, const std::string& name,
			const std::string& type,const std::string& path,
			const std::string& pathProcess);
	VisionArea(const std::string& name, const std::string& type);
	virtual ~VisionArea();
	virtual void complete(const std::string& attributes);
	virtual const std::string& getClassName();
	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getType() const;
	const std::string& getPath() const;
	const std::string& getPathProcess() const;
	void setId(const std::string& id);
	void setName(const std::string& name);
	void setType(const std::string& type);
	void setPath(const std::string& path);
	void setPathProcess(const std::string& path);

private:
	std::string id;
	std::string name;
	std::string type;
	std::string path;
	std::string pathProcess;
};

} /* namespace config */
#endif /* VISIONAREA_H_ */
