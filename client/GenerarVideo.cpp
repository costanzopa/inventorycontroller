/*
 * GenerarVideo.cpp
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#include "GenerarVideo.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/signalproxy.h>
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treeview.h>
#include <gtkmm/window.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <string>
#include <vector>

GenerarVideo::GenerarVideo(Glib::RefPtr<Gtk::Application> app,
                           Procesador* procesador, Screen* padre) {
  this->padre = padre;
  this->procesador = procesador;
  this->app = app;
  ventanaOK = new VentanaOK(app, this);
  crearVideo = new CrearVideo(app, procesador, this);
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/generarVideo.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button3", botonHome);
  refBuilder->get_widget("button4", botonBorrar);
  refBuilder->get_widget("button1", botonGenerar);
  refBuilder->get_widget("button2", botonAgregar);
  refBuilder->get_widget("filechooserbutton1", botonDireccionArchivo);
  refBuilder->get_widget("image1", imagen);
  refBuilder->get_widget("treeview1", treeView);

  Gtk::Image* imagenAux;
  refBuilder->get_widget("image2", imagenAux);
  imagenAux->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/agregar.png", 20, 20,
              true));
  refBuilder->get_widget("image3", imagenAux);
  imagenAux->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/remover.png", 20, 20,
              true));
  refBuilder->get_widget("image4", imagenAux);
  imagenAux->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/video.png", 25, 25,
              true));

  botonGenerar->signal_clicked().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_botonGenerar_clicked));
  botonAgregar->signal_clicked().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_botonAgregar_clicked));
  botonHome->signal_clicked().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_botonHome_clicked));
  botonDireccionArchivo->signal_file_set().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_botonDireccion_file_set));
  botonBorrar->signal_clicked().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_botonBorrar_clicked));
  treeView->signal_row_activated().connect(
      sigc::mem_fun(*this, &GenerarVideo::on_row_activated));

  Gtk::TreeModel::ColumnRecord columnaRecord;
  columnaRecord.add(columnaNombre);
  columnaRecord.add(columnaDir);
  treeModel = Gtk::ListStore::create(columnaRecord);
  treeView->set_model(treeModel);
  treeView->append_column("Imagen", columnaNombre);
}

void GenerarVideo::on_botonHome_clicked() {
  padre->show();
  this->hide();

}

void GenerarVideo::on_botonAgregar_clicked() {
  if (direccionImagenElegida != "") {
    Gtk::TreeModel::Row row = *(treeModel->append());
    row[columnaNombre] = procesador->getFileName(direccionImagenElegida);
    row[columnaDir] = direccionImagenElegida;
  }
}

void GenerarVideo::on_botonBorrar_clicked() {
  Glib::RefPtr<Gtk::TreeSelection> selection = treeView->get_selection();
  Gtk::TreeModel::iterator selectedRow = selection->get_selected();
  if (selectedRow) {
    treeModel->erase(selectedRow);
    imagen->clear();
  }
}

void GenerarVideo::on_botonDireccion_file_set() {
  std::string direccionArchivo = botonDireccionArchivo->get_filename();
  std::string extension = procesador->getFileExtension(direccionArchivo);

  if ((extension != "png") && (extension != "jpg")) {
    direccionArchivo = "";
    botonDireccionArchivo->unselect_all();
    ventanaOK->setLabel("El archivo debe ser de formato JPG o PNG");
    ventanaOK->show();
  } else {
    direccionImagenElegida = direccionArchivo;
    imagen->set(Gdk::Pixbuf::create_from_file(direccionArchivo));
  }
}

void GenerarVideo::on_botonGenerar_clicked() {
  Gtk::TreeModel::Children children = treeModel->children();
  std::vector<std::string> dirImagenes;
  for (Gtk::TreeModel::Children::iterator iter = children.begin();
      iter != children.end(); ++iter) {
    Gtk::TreeModel::Row row = *iter;
    std::string dir;
    row.get_value(1, dir);
    dirImagenes.push_back(dir);
  }
  crearVideo->setDirImagenes(dirImagenes);
  crearVideo->show();
}

void GenerarVideo::on_row_activated(const Gtk::TreeModel::Path& path,
                                    Gtk::TreeViewColumn*c) {
  Glib::RefPtr<Gtk::TreeSelection> selection = treeView->get_selection();
  Gtk::TreeModel::iterator selectedRow = selection->get_selected();
  Gtk::TreeModel::Row row = *selectedRow;
  std::string dir;
  row.get_value(1, dir);
  imagen->set(Gdk::Pixbuf::create_from_file(dir));
}

void GenerarVideo::show() {
  app->add_window(*window);
  window->show();
}

void GenerarVideo::hide() {
  window->hide();
  app->remove_window(*window);
}

GenerarVideo::~GenerarVideo() {
  delete ventanaOK;
}

