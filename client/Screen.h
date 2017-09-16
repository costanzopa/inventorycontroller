/*
 * Screen.h
 *
 *  Created on: May 29, 2015
 *      Author: horacio
 */

#ifndef TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_SCREEN_H_
#define TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_SCREEN_H_

#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include "Procesador.h"

class Screen {
 public:
  virtual ~Screen();
  virtual void show() = 0;
  virtual void hide() = 0;
 protected:
  Glib::RefPtr < Gtk::Application > app;
  Glib::RefPtr < Gtk::Builder > refBuilder;
};

#endif /* TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_SCREEN_H_ */
