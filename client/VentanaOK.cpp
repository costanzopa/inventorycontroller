/*
 * VentanaOK.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: horacio
 */

#include "VentanaOK.h"

#include <glibmm/signalproxy.h>
#include <gtkmm/builder.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>

VentanaOK::VentanaOK(Glib::RefPtr<Gtk::Application> app, Screen* padre) {
  this->app = app;
  this->padre = padre;
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/ventanaOK.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonOK);
  refBuilder->get_widget("label1", label);
  botonOK->signal_clicked().connect(
      sigc::mem_fun(*this, &VentanaOK::on_botonOK_clicked));
}

void VentanaOK::on_botonOK_clicked() {
  padre->show();
  this->hide();
}

void VentanaOK::setLabel(const std::string &mensaje) {
  label->set_text(mensaje);
}
void VentanaOK::show() {
  app->add_window(*window);
  window->show();
}

void VentanaOK::hide() {
  window->hide();
  app->remove_window(*window);
}

