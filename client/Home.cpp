/*
 * Home.cpp
 *
 *  Created on: May 29, 2015
 *      Author: horacio
 */

#include "Home.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/signalproxy.h>
#include <gtkmm/builder.h>
#include <gtkmm/image.h>
#include <gtkmm/window.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>

#include "Procesador.h"

#define TAMANIO_ICONOS 50

Home::Home(Glib::RefPtr<Gtk::Application> app) {
  procesador = new Procesador();
  this->app = app;
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/home.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonEnviar);
  refBuilder->get_widget("button2", botonEnviados);
  refBuilder->get_widget("button3", botonConvertir);
  botonEnviar->signal_clicked().connect(
      sigc::mem_fun(*this, &Home::on_botonEnviar_clicked));
  botonEnviados->signal_clicked().connect(
      sigc::mem_fun(*this, &Home::on_botonEnviados_clicked));
  botonConvertir->signal_clicked().connect(
      sigc::mem_fun(*this, &Home::on_botonConvertir_clicked));
  enviar = 0;
  enviados = 0;
  generarVideo = 0;
  cargarImagenes();
}

void Home::on_botonEnviar_clicked() {
  if (enviar == 0)
    enviar = new Enviar(app, procesador, this);
  enviar->show();
  this->hide();
}

void Home::on_botonEnviados_clicked() {
  if (enviados == 0)
    enviados = new Enviados(app, procesador, this);
  enviados->show();
  this->hide();
}

void Home::on_botonConvertir_clicked() {
  if (generarVideo == 0)
    generarVideo = new GenerarVideo(app, procesador, this);
  generarVideo->show();
  this->hide();
}

void Home::ejecutar() {
  app->run(*window);
}

void Home::show() {
  app->add_window(*window);
  window->show();
}

void Home::hide() {
  window->hide();
  app->remove_window(*window);
}

void Home::cargarImagenes() {
  Gtk::Image* imagen;
  refBuilder->get_widget("image1", imagen);
  imagen->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/menuPrincipal.png"));
  refBuilder->get_widget("image2", imagen);
  imagen->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/enviar.png",TAMANIO_ICONOS,TAMANIO_ICONOS,false));
  refBuilder->get_widget("image3", imagen);
  imagen->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/descargar.png",TAMANIO_ICONOS,TAMANIO_ICONOS,false));
  refBuilder->get_widget("image4", imagen);
  imagen->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/video.png",TAMANIO_ICONOS,TAMANIO_ICONOS,false));
}
Home::~Home() {
  if (enviar != 0)
    delete enviar;
  if (generarVideo != 0)
    delete generarVideo;
  if (enviados != 0)
    delete enviados;
  delete procesador;
}

