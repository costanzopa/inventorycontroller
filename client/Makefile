client: ./../common/StringUtils.o ./../common/Exception.o ./../common/Socket.o  ./../common/Communication.o ./../common/Protocolo.o Enviados.o Enviar.o ControladorOpenCV.o DescargarImagenes.o GenerarVideo.o CrearVideo.o ReproductorDeVideo.o VentanaOK.o Home.o Procesador.o Screen.o main.o 
	g++ -O0 -g3 -o  client ./../common/StringUtils.o ./../common/Exception.o ./../common/Socket.o  ./../common/Communication.o ./../common/Protocolo.o Enviados.o Enviar.o CrearVideo.o DescargarImagenes.o VentanaOK.o GenerarVideo.o ReproductorDeVideo.o Home.o ControladorOpenCV.o Procesador.o Screen.o main.o `pkg-config gtkmm-3.0 opencv --cflags --libs`

main.o: Home.h main.cpp 
	g++ -c main.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

Home.o: Screen.h Procesador.h Enviados.h Enviar.h GenerarVideo.h CrearVideo.h VentanaOK.h Home.h ControladorOpenCV.h Home.cpp
	g++ -c Home.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`


Screen.o: Screen.h Procesador.h Enviados.h Enviar.h CrearVideo.h VentanaOK.h GenerarVideo.h Home.h ControladorOpenCV.h Screen.cpp
	g++ -c Screen.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`


Procesador.o: ../common/Protocolo.h ../common/Communication.h ../common/StringUtils.h Screen.h Procesador.h Enviados.h Enviar.h GenerarVideo.h ControladorOpenCV.h Home.h Procesador.cpp
	g++ -c Procesador.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

DescargarImagenes.o: ../common/StringUtils.h Screen.h Procesador.h Enviados.h DescargarImagenes.h Enviar.h VentanaOK.h DescargarImagenes.cpp
	g++ -c DescargarImagenes.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

Enviados.o: ../common/StringUtils.h Screen.h Procesador.h DescargarImagenes.h Enviados.h Enviar.h VentanaOK.h Enviados.cpp
	g++ -c Enviados.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

Enviar.o: Screen.h Procesador.h Enviados.h Enviar.h CrearVideo.h VentanaOK.h GenerarVideo.h ControladorOpenCV.h Home.h Enviar.cpp
	g++ -c Enviar.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

ReproductorDeVideo.o: ../common/StringUtils.h Screen.h Procesador.h Enviar.h VentanaOK.h GenerarVideo.h ControladorOpenCV.h ReproductorDeVideo.h ReproductorDeVideo.cpp
	g++ -c ReproductorDeVideo.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

GenerarVideo.o: ../common/StringUtils.h Screen.h Procesador.h Enviados.h CrearVideo.h VentanaOK.h Enviar.h GenerarVideo.h ControladorOpenCV.h Home.h GenerarVideo.cpp
	g++ -c GenerarVideo.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

ControladorOpenCV.o: Screen.h Procesador.h Enviados.h CrearVideo.h VentanaOK.h Enviar.h GenerarVideo.h Home.h ControladorOpenCV.h ControladorOpenCV.cpp
	g++ -c ControladorOpenCV.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

CrearVideo.o: Screen.h Procesador.h Enviados.h VentanaOK.h Enviar.h GenerarVideo.h Home.h ControladorOpenCV.h CrearVideo.h CrearVideo.cpp
	g++ -c CrearVideo.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

VentanaOK.o: Screen.h Procesador.h Enviados.h VentanaOK.h Enviar.h GenerarVideo.h Home.h ControladorOpenCV.h CrearVideo.h VentanaOK.cpp
	g++ -c VentanaOK.cpp -std=c++98 `pkg-config gtkmm-3.0 opencv --cflags --libs`

clean:
	rm -f client *.o
