server: ./../common/StringUtils.o ./../common/Exception.o ./../common/Socket.o  ./../common/Communication.o ./../common/Stock.o  ./../common/Directory.o Matcher.o XmlElement.o VisionArea.o Product.o XmlElementFactory.o XmlFile.o ServerConfig.o CatalogConfig.o CatalogFile.o Catalog.o Configuration.o ConfigFile.o Mutex.o Lock.o Thread.o Request.o Server.o main.o 
	g++ -O0 -g3 -o  server  ./../common/StringUtils.o ./../common/Exception.o ./../common/Socket.o  ./../common/Communication.o ./../common/Stock.o ./../common/Directory.o Matcher.o XmlElement.o VisionArea.o Product.o XmlElementFactory.o  XmlFile.o ServerConfig.o CatalogConfig.o CatalogFile.o Catalog.o Configuration.o ConfigFile.o Mutex.o Lock.o Thread.o Request.o Server.o main.o -lpthread -pthread `pkg-config --libs libxml++-2.6 opencv`

main.o: xmlConfig/ConfigFile.h ../common/Constants.h xmlConfig/Configuration.h Server.h main.cpp 
	g++ -c main.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags libxml++-2.6`


Server.o: ../common/Exception.h  ../common/Communication.h threads/Thread.h xmlConfig/ConfigFile.h  xmlConfig/CatalogFile.h catalog/Catalog.h xmlConfig/CatalogConfig.h Request.h Server.h Server.cpp
	g++ -c Server.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags libxml++-2.6`



Request.o: threads/Thread.h ../common/Communication.h ../common/Stock.h catalog/Catalog.h Matcher.h Request.h Request.cpp
	g++ -c Request.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags opencv`


Matcher.o: ../common/Directory.h ../common/Constants.h Matcher.h Matcher.cpp
	g++ -c Matcher.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags opencv`

CatalogFile.o: ../common/Constants.h xmlConfig/XmlElement.h xmlConfig/XmlFile.h catalog/Catalog.h xmlConfig/CatalogFile.h xmlConfig/CatalogFile.cpp
	g++ -c xmlConfig/CatalogFile.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags libxml++-2.6`


ConfigFile.o: ../common/Constants.h xmlConfig/XmlElement.h xmlConfig/XmlFile.h xmlConfig/Configuration.h xmlConfig/ConfigFile.h xmlConfig/ConfigFile.cpp
	g++ -c xmlConfig/ConfigFile.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags libxml++-2.6`


Catalog.o: xmlConfig/XmlElement.h catalog/Product.h catalog/VisionArea.h  threads/Mutex.h ../common/Directory.h catalog/Catalog.h catalog/Catalog.cpp
	g++ -c catalog/Catalog.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 	
	
Configuration.o: xmlConfig/ServerConfig.h xmlConfig/CatalogConfig.h xmlConfig/XmlElement.h  xmlConfig/Configuration.h xmlConfig/Configuration.cpp
	g++ -c xmlConfig/Configuration.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 



XmlElementFactory.o: ../common/Exception.h xmlConfig/XmlElement.h catalog/VisionArea.h catalog/Product.h xmlConfig/CatalogConfig.h xmlConfig/ServerConfig.h xmlConfig/XmlElementFactory.h xmlConfig/XmlElementFactory.cpp
	g++ -c xmlConfig/XmlElementFactory.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98



Product.o: ../common/StringUtils.h  ../common/Constants.h xmlConfig/XmlElement.h ../common/Directory.h catalog/Product.h  catalog/Product.cpp
	g++ -c catalog/Product.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98


VisionArea.o: ../common/StringUtils.h  ../common/Constants.h xmlConfig/XmlElement.h catalog/VisionArea.h  catalog/VisionArea.cpp
	g++ -c catalog/VisionArea.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98



XmlElement.o: xmlConfig/XmlElement.h xmlConfig/XmlElement.cpp
	g++ -c xmlConfig/XmlElement.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98



ServerConfig.o: ../common/StringUtils.h   xmlConfig/XmlElement.h xmlConfig/ServerConfig.h xmlConfig/ServerConfig.cpp
	g++ -c xmlConfig/ServerConfig.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98


CatalogConfig.o: ../common/StringUtils.h xmlConfig/XmlElement.h xmlConfig/CatalogConfig.h xmlConfig/CatalogConfig.cpp
	g++ -c xmlConfig/CatalogConfig.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98


XmlFile.o: ../common/Constants.h xmlConfig/XmlElement.h xmlConfig/XmlElementFactory.h xmlConfig/XmlFile.h xmlConfig/XmlFile.cpp
	g++ -c xmlConfig/XmlFile.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98 `pkg-config --cflags libxml++-2.6`
 
Thread.o: ../common/Exception.h  threads/Thread.h threads/Thread.cpp
	g++ -c threads/Thread.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98

Lock.o: threads/Mutex.h threads/Lock.h threads/Lock.cpp 
	g++ -c threads/Lock.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98

Mutex.o: ../common/Exception.h threads/Mutex.h threads/Mutex.cpp
	g++ -c threads/Mutex.cpp -O0 -g3 -pedantic -Wall -Wextra -Wconversion  -std=c++98
clean:
	rm -f server *.o
