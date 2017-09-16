/*
 * Product.h
 *
 *  Created on: 04/06/2015
 *      Author:
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_
#include <stdlib.h>
#include "../../common/StringUtils.h"
#include "../xmlConfig/XmlElement.h"
#include <iostream>
#include "../../common/Constants.h"
#include "../../common/Directory.h"

namespace catalog {

class Product: public xml::XmlElement {
public:
	explicit Product(const std::string& className);
	Product(const std::string& id, const std::string& name,
			const std::string& des,const std::string& path,
			const std::string& pathIcon,const std::string& pathStock);
	virtual ~Product();
	virtual void complete(const std::string& attributes);
	virtual const std::string& getClassName();
	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getDescription() const;
	const std::string& getPath() const;
	const std::string& getPathIcon() const;
	const std::string& getPathStock() const;
	void setId(const std::string& id);
	void setPath(const std::string& path);
	void setPathIcon(const std::string& path);
	void setPathStock(const std::string& path);

	void setName(const std::string& s);
	void setDescription(const std::string& s);
	private:
	std::string id;
	std::string name;
	std::string description;
	std::string path;
	std::string pathIcon;
	std::string pathStock;
};

} /* namespace config */
#endif /* PRODUCT_H_ */
