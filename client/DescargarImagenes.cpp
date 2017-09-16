/*
 * DescargarImagenes.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: horacio
 */

#include "DescargarImagenes.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/signalproxy.h>
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <iostream>
#include <string>
#include <vector>

#include "../common/StringUtils.h"

DescargarImagenes::DescargarImagenes(Glib::RefPtr<Gtk::Application> app,
                                     Procesador* procesador, Screen* padre) {
  this->app = app;
  this->padre = padre;
  this->procesador = procesador;
  ventanaOK = new VentanaOK(app, this);
  ventanaDescargado = new VentanaOK(app, padre);
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/descargar.glade");
  refBuilder->get_widget("window1", window);

  refBuilder->add_from_file("./ui/glade/guardar.glade");
  refBuilder->get_widget("button1", botonCancelar);
  refBuilder->get_widget("button2", botonAceptar);
  refBuilder->get_widget("filechooserdialog1", fileChooser);

  botonAceptar->signal_clicked().connect(
      sigc::mem_fun(*this, &DescargarImagenes::on_botonAceptar_clicked));
  botonCancelar->signal_clicked().connect(
      sigc::mem_fun(*this, &DescargarImagenes::on_botonCancelar_clicked));

}

void DescargarImagenes::on_botonAceptar_clicked() {

  std::string direccion;
  utils::StringUtils stringUtils;

  std::string extension = procesador->getFileExtension(
      fileChooser->get_filename());
  if (extension != "png" && extension != "jpg") {
    ventanaOK->setLabel("La imagen debe ser de extension jpg o png");
    ventanaOK->show();
    fileChooser->hide();
    return;
  }

  for (unsigned int i = 0; i < imagenes.size(); i++) {
    if (imagenes.size() == 1) {
      direccion = fileChooser->get_filename();
    } else {
      direccion = fileChooser->get_filename().substr(
          0, fileChooser->get_filename().find_last_of("."))
          + stringUtils.toString(i) + "." + extension;
      std::cout << direccion << std::endl;
    }
    if (extension == "jpg")
      imagenes[i]->save(direccion, "jpeg");
    else
      imagenes[i]->save(direccion, "png");
  }

  ventanaDescargado->setLabel("Descarga completa");
  ventanaDescargado->show();
  fileChooser->hide();

}

void DescargarImagenes::on_botonCancelar_clicked() {
  fileChooser->hide();
  fileChooser->set_filename("");
}

void DescargarImagenes::setImagenes(
    std::vector<Glib::RefPtr<Gdk::Pixbuf> > &imagenes) {
  this->imagenes = imagenes;
}

void DescargarImagenes::show() {
  fileChooser->set_current_name(".png");
  fileChooser->run();
}

void DescargarImagenes::hide() {
  fileChooser->set_current_name("");
  fileChooser->hide();
}

DescargarImagenes::~DescargarImagenes() {
  delete ventanaOK;
  delete ventanaDescargado;
}
