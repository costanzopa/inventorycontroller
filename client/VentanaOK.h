/*
 * VentanaOK.h
 *
 *  Created on: Jun 15, 2015
 *      Author: horacio
 */

#ifndef VENTANAOK_H_
#define VENTANAOK_H_

#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <string>

#include "Screen.h"

class VentanaOK : public Screen {
 public:
  VentanaOK(Glib::RefPtr<Gtk::Application> app, Screen* padre);
  void show();
  void hide();
  void setLabel(const std::string &mensaje);

 private:
  void on_botonOK_clicked();
  Gtk::Window* window;
  Gtk::Button* botonOK;
  Gtk::Label* label;
  Screen* padre;
};

#endif /* VENTANAOK_H_ */
