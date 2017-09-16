/*
 * Enviar.cpp
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#include "Enviar.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/main.h>
#include <glibmm/refptr.h>
#include <glibmm/signalproxy.h>
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <sigc++/functors/slot.h>
#include <iterator>
#include <string>
#include <vector>

Enviar::Enviar(Glib::RefPtr<Gtk::Application> app, Procesador* procesador,
               Screen* padre)/*: rep(imagen)*/{
  this->app = app;
  this->procesador = procesador;
  this->padre = padre;
  videoActivo = false;
  ventanaOK = new VentanaOK(app, this);
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/enviar.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonEnviar);
  refBuilder->get_widget("button2", botonPlay);
  refBuilder->get_widget("button3", botonPause);
  refBuilder->get_widget("button4", botonStop);
  refBuilder->get_widget("button5", botonHome);
  refBuilder->get_widget("box4", boxVideo);
  refBuilder->get_widget("progressbar1", progressbar);
  refBuilder->get_widget("filechooserbutton1", botonDireccion);
  refBuilder->get_widget("comboboxtext1", comboMetodo);
  refBuilder->get_widget("comboboxtext2", comboAreaVision);
  refBuilder->get_widget("comboboxtext6", comboDia);
  refBuilder->get_widget("comboboxtext7", comboMes);
  refBuilder->get_widget("comboboxtext8", comboAnio);
  refBuilder->get_widget("comboboxtext9", comboHora);
  refBuilder->get_widget("comboboxtext10", comboMinutos);

  refBuilder->get_widget("image1", imagen);
  Gtk::Image* imagenAux;
  refBuilder->get_widget("image2", imagenAux);
  imagenAux->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/enviar.png", 25, 25,
              true));

  botonEnviar->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviar::on_botonEnviar_clicked));
  botonHome->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviar::on_botonHome_clicked));
  botonPlay->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviar::on_botonPlay_clicked));
  botonStop->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviar::on_botonStop_clicked));
  botonPause->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviar::on_botonPause_clicked));
  botonDireccion->signal_file_set().connect(
      sigc::mem_fun(*this, &Enviar::on_botonDireccion_file_set));
  comboMetodo->signal_changed().connect(
      sigc::mem_fun(*this, &Enviar::on_comboMetodo_changed));
  comboMetodo->append("Template matching");
  comboMetodo->append("Feature matching");
  comboAreaVision->signal_changed().connect(
      sigc::mem_fun(*this, &Enviar::on_comboAreaVision_changed));

  rep = new ReproductorDeVideo(imagen);
  boxVideo->hide();
}

bool Enviar::on_video_timeout() {
  if (!videoActivo)
    return false;
  rep->update();
  progressbar->set_fraction((double) rep->getFraccionProgreso());
  return true;
}

void Enviar::setVideo(const std::string &dir) {
  videoActivo = true;
  boxVideo->show_all();
  rep->setVideo(dir);
  int fps = rep->getFps();
  slot = sigc::mem_fun(*this, &Enviar::on_video_timeout);
  Glib::signal_timeout().connect(slot, ((float) 1 / fps) * 1000);
  rep->play();
}

void Enviar::desactivarVideo() {
  videoActivo = false;
  boxVideo->hide();
}

void Enviar::on_botonPlay_clicked() {
  rep->play();
}
void Enviar::on_botonPause_clicked() {
  rep->pause();
}
void Enviar::on_botonStop_clicked() {
  rep->stop();
}

void Enviar::on_botonHome_clicked() {
  padre->show();
  this->hide();
}

void Enviar::on_botonEnviar_clicked() {
  if (direccionArchivo.empty() || areaDeVisionElegida.empty()
      || comboMetodo->get_active_text() == "" || getFechaHora() == "") {
    ventanaOK->setLabel("Complete todos los campos");
    ventanaOK->show();
  } else {
    std::vector<std::string> respuesta;
    bool exito;
    if (procesador->getFileExtension(direccionArchivo) == "mpg")
      exito = procesador->enviarVideo(respuesta, areaDeVisionElegida,
                                      templateMatching, getFechaHora(),
                                      direccionArchivo);
    else
      exito = procesador->enviarImagen(respuesta, areaDeVisionElegida,
                                       templateMatching, getFechaHora(),
                                       direccionArchivo);
    if (exito) {
      std::string label;
      for (unsigned int i = 0; i < respuesta.size(); i++) {
        label = label + respuesta[i] + " ";
      }
      ventanaOK->setLabel(label);
      ventanaOK->show();
    } else {
      ventanaOK->setLabel("Error al enviar");
      ventanaOK->show();
    }
  }
}

void Enviar::on_comboMetodo_changed() {
  if (comboMetodo->get_active_text() == "Template matching")
    templateMatching = true;
  else
    templateMatching = false;
}

void Enviar::on_comboAreaVision_changed() {
  areaDeVisionElegida = comboAreaVision->get_active_text();
}

void Enviar::on_botonDireccion_file_set() {
  direccionArchivo = botonDireccion->get_filename();
  std::string extension = procesador->getFileExtension(direccionArchivo);

  if ((extension != "png") && (extension != "jpg") && (extension != "mpg")
      && (extension != "avi")) {
    direccionArchivo = "";
    botonDireccion->unselect_all();
    ventanaOK->setLabel("El archivo debe ser de formato JPG, PNG, MPEG");
    ventanaOK->show();
  } else {

    if ((extension == "png") || (extension == "jpg")) {
      desactivarVideo();
      imagen->set(Gdk::Pixbuf::create_from_file(direccionArchivo));
    } else {
      this->setVideo(direccionArchivo);
    }
  }
}

void Enviar::show() {
  app->add_window(*window);
  window->show();
  cargarAreasDeVision();
}

std::string Enviar::getFechaHora() {
  std::string res;
  if (comboDia->get_active_text() == "" || comboMes->get_active_text() == ""
      || comboAnio->get_active_text() == ""
      || comboHora->get_active_text() == ""
      || comboMinutos->get_active_text() == "")
    res = "";

  else
    res = comboDia->get_active_text() + "/" + comboMes->get_active_text() + "/"
		+ comboAnio->get_active_text().substr(2, 3) + "/"
		+ comboHora->get_active_text() + "/" + comboMinutos->get_active_text();
  return res;
}

void Enviar::cargarAreasDeVision() {
  comboAreaVision->remove_all();
  std::vector<std::string> areas;
  try {
    procesador->getAreasDeVision(areas);
  } catch (...) {
    ventanaOK->setLabel("No se pudo obtener las areas de vision");
    ventanaOK->show();
  }
  std::vector<std::string>::iterator areasIt;
  for (areasIt = areas.begin(); areasIt != areas.end(); ++areasIt) {
    comboAreaVision->append(*areasIt);
  }
}
void Enviar::hide() {
  window->hide();
  app->remove_window(*window);
  desactivarVideo();
  clear();
}

void Enviar::clear() {
  imagen->clear();
  direccionArchivo.clear();
  areaDeVisionElegida.clear();
  comboMetodo->unset_active();
  comboAreaVision->remove_all();
  comboAnio->unset_active();
  comboMes->unset_active();
  comboDia->unset_active();
  comboHora->unset_active();
  comboMinutos->unset_active();
  botonDireccion->unselect_all();
}

Enviar::~Enviar() {
  delete ventanaOK;
  delete rep;
}
