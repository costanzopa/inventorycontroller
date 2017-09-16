/*
 * CrearVideo.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: horacio
 */

#include "CrearVideo.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/signalproxy.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <string>

CrearVideo::CrearVideo(Glib::RefPtr<Gtk::Application> app,
                       Procesador* procesador, Screen* padre) {
  this->app = app;
  this->padre = padre;
  this->procesador = procesador;
  ventanaOK = new VentanaOK(app, this);
  ventanaCreado = new VentanaOK(app, padre);
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/crearVideo.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonCrear);
  refBuilder->get_widget("spinbutton1", spinFPS);
  refBuilder->get_widget("spinbutton2", spinAncho);
  refBuilder->get_widget("spinbutton3", spinAlto);
  Gtk::Image* imagenAux;
  refBuilder->get_widget("image1", imagenAux);
  imagenAux->set(
      Gdk::Pixbuf::create_from_file("./ui/imagenes/video.png", 20, 20, true));
  refBuilder->add_from_file("./ui/glade/guardar.glade");
  refBuilder->get_widget("button1", botonCancelar);
  refBuilder->get_widget("button2", botonAceptar);
  refBuilder->get_widget("filechooserdialog1", fileChooser);

  fileChooser->set_current_name(".mpg");
  botonCrear->signal_clicked().connect(
      sigc::mem_fun(*this, &CrearVideo::on_botonCrear_clicked));
  botonAceptar->signal_clicked().connect(
      sigc::mem_fun(*this, &CrearVideo::on_botonAceptar_clicked));
  botonCancelar->signal_clicked().connect(
      sigc::mem_fun(*this, &CrearVideo::on_botonCancelar_clicked));
}

CrearVideo::~CrearVideo() {
  delete ventanaOK;
  delete ventanaCreado;
}

void CrearVideo::on_botonCrear_clicked() {
  fileChooser->run();
}

void CrearVideo::on_botonAceptar_clicked() {

  std::string extension = procesador->getFileExtension(
      fileChooser->get_filename());
  if (extension != "mpg") {
    ventanaOK->setLabel("El video debe ser de extension mpg");
    ventanaOK->show();
    fileChooser->hide();
    return;
  }
  std::string direccion = procesador->getFilePath(fileChooser->get_filename());
  std::string nombre = procesador->getFileName(fileChooser->get_filename())
      .substr(
      0,
      procesador->getFileName(fileChooser->get_filename()).find_last_of("."));
  openCV.crearVideo(dirImagenes, direccion, nombre, (int) spinFPS->get_value(),
                    spinAncho->get_value(), spinAlto->get_value());

  ventanaCreado->setLabel("Se ha creado el video");
  ventanaCreado->show();
  fileChooser->hide();
  this->hide();
}

void CrearVideo::on_botonCancelar_clicked() {
  fileChooser->hide();
  fileChooser->set_filename("");
  fileChooser->set_current_name(".mpg");
}

void CrearVideo::show() {
  app->add_window(*window);
  window->show();
}

void CrearVideo::hide() {
  window->hide();
  app->remove_window(*window);
}
