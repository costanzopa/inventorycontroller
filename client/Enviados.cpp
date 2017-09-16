/*
 * Enviados.cpp
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#include "Enviados.h"

#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/signalproxy.h>
#include <glibmm/ustring.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/window.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>

#include "../common/StringUtils.h"
#include "Procesador.h"

#define TAMANIO_ICONOS 50

Enviados::Enviados(Glib::RefPtr<Gtk::Application> app, Procesador* procesador,
                   Screen* padre) {
  this->procesador = procesador;
  this->padre = padre;
  this->app = app;
  cargados = false;
  ventanaOK = new VentanaOK(app, this);
  descargar = new DescargarImagenes(app, procesador,this);
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/enviados.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonHome);
  refBuilder->get_widget("button2", botonDescargar);
  refBuilder->get_widget("iconview1", iconView);
  refBuilder->get_widget("treeview1", treeView);

  Gtk::Image* imagenAux;
  refBuilder->get_widget("image1", imagenAux);
  imagenAux->set(Gdk::Pixbuf::create_from_file("./ui/imagenes/descargar.png", 25, 25,
              true));

  botonHome->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviados::on_botonHome_clicked));
  botonDescargar->signal_clicked().connect(
      sigc::mem_fun(*this, &Enviados::on_botonDescargar_clicked));
  treeView->signal_row_activated().connect(
      sigc::mem_fun(*this, &Enviados::on_productos_row_activated));

  Gtk::TreeModel::ColumnRecord columnaImagenesRecord;
  columnaImagenesRecord.add(columnaImagen);
  columnaImagenesRecord.add(columnaNombreImagen);
  treeModelIcons = Gtk::ListStore::create(columnaImagenesRecord);
  filtroImagenes = Gtk::TreeModelFilter::create(treeModelIcons);
  filtroImagenes->set_visible_func(
      sigc::mem_fun(*this, &Enviados::on_filter_row_visible));
  iconView->set_model(filtroImagenes);
  iconView->set_pixbuf_column(columnaImagen);

  Gtk::TreeModel::ColumnRecord columnaProductosRecord;
  columnaProductosRecord.add(columnaProducto);
  treeModelProductos = Gtk::ListStore::create(columnaProductosRecord);
  treeView->set_model(treeModelProductos);
  treeView->append_column("Productos", columnaProducto);
}

void Enviados::agregarProducto(const std::string &s) {
  Gtk::TreeModel::Row row = *(treeModelProductos->append());
  row[columnaProducto] = s;
}

bool Enviados::on_filter_row_visible(
    const Gtk::TreeModel::const_iterator& iter) {
  if (iter) {
    Gtk::TreeModel::Row row = *iter;
    if (row[columnaNombreImagen] == productoElegido)
      return true;
  }
  return false;
}

void Enviados::agregarImagen(const std::string &producto,
                             Glib::RefPtr<Gdk::Pixbuf> img) {
  Gtk::TreeModel::Row row = *(treeModelIcons->append());
  row[columnaNombreImagen] = producto;
  row[columnaImagen] = img;
}

void Enviados::on_botonHome_clicked() {
  padre->show();
  this->hide();

}

void Enviados::on_botonDescargar_clicked() {

  std::vector<Gtk::TreeModel::Path> selected = iconView->get_selected_items();
  if (selected.empty()) {
    ventanaOK->setLabel("Seleccione alguna imagen");
    ventanaOK->show();
    return;
  }

  std::vector<Glib::RefPtr<Gdk::Pixbuf> > imagenes;
  for (unsigned int i = 0; i < selected.size(); i++) {
    const Gtk::TreeModel::Path& path = selected[i];
    Gtk::TreeModel::iterator iter = treeModelIcons->get_iter(path);
    Gtk::TreeModel::Row row = *iter;
    imagenes.push_back(row[columnaImagen]);
  }
  descargar->setImagenes(imagenes);
  descargar->show();
}

void Enviados::on_productos_row_activated(const Gtk::TreeModel::Path& path,
                                          Gtk::TreeViewColumn*c) {
  Glib::RefPtr<Gtk::TreeSelection> selection = treeView->get_selection();
  Gtk::TreeModel::iterator selectedRow = selection->get_selected();
  Gtk::TreeModel::Row row = *selectedRow;
  std::string dir;
  row.get_value(0, dir);
  productoElegido = dir;
  filtroImagenes->refilter();
}

void Enviados::show() {
  app->add_window(*window);
  window->show();
  if (!cargados){
  cargarProductos();
  //  cargarValoresPrueba();
  }
}

void Enviados::hide() {
  window->hide();
  app->remove_window(*window);
}

void Enviados::cargarProductos() {
  cargados = true;
  std::vector<std::string> productos;
  std::vector<std::string> imagenes;
  std::vector<std::string> extensiones;
  // direccion de la carpeta temporal:
  char const *carpetaTemporal = getenv("TMPDIR");
  if (carpetaTemporal == 0)
    carpetaTemporal = "/tmp";
  std::string temp = carpetaTemporal;

  utils::StringUtils stringUtils;
  if (!procesador->getProductos(productos)) {
    ventanaOK->setLabel("Error al obtener los productos");
    ventanaOK->show();
    return;
  }
  for (unsigned int i = 0; i < productos.size(); i++) {
    agregarProducto(productos[i]);

    if (!procesador->getImagenesDeProducto(productos[i], imagenes,
                                           extensiones)) {
      ventanaOK->setLabel("Error al obtener las imagenes de los productos");
      ventanaOK->show();
      return;
    }
    for (unsigned int j = 0; j < imagenes.size(); j++) {
      std::string dir = temp + "/" + "tptaller" + stringUtils.toString(i)
          + stringUtils.toString(j) + extensiones[j];
      procesador->stringTofile(imagenes[j], dir);

      agregarImagen(productos[i],
                    Gdk::Pixbuf::create_from_file(dir,
                    TAMANIO_ICONOS,
                                                  TAMANIO_ICONOS, true));
    }
    imagenes.clear();
  }
}

void Enviados::cargarValoresPrueba() {
  cargados = true;
  agregarProducto("prueba1");
  agregarProducto("prueba2");
  agregarProducto("prueba3");

  agregarImagen("prueba1",
                      Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba2.png",
                      TAMANIO_ICONOS,
                                                    TAMANIO_ICONOS, true));
  agregarImagen("prueba1",
                        Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                        TAMANIO_ICONOS,
                                                      TAMANIO_ICONOS, true));
  agregarImagen("prueba1",
                        Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                        TAMANIO_ICONOS,
                                                      TAMANIO_ICONOS, true));
  agregarImagen("prueba1",
                        Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                        TAMANIO_ICONOS,
                                                      TAMANIO_ICONOS, true));
  agregarImagen("prueba1",
                        Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba2.png",
                        TAMANIO_ICONOS,
                                                      TAMANIO_ICONOS, true));
  agregarImagen("prueba1",
                        Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                        TAMANIO_ICONOS,
                                                      TAMANIO_ICONOS, true));
  agregarImagen("prueba2",
                          Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                          TAMANIO_ICONOS,
                                                        TAMANIO_ICONOS, true));
  agregarImagen("prueba2",
                          Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba2.png",
                          TAMANIO_ICONOS,
                                                        TAMANIO_ICONOS, true));
  agregarImagen("prueba3",
                          Gdk::Pixbuf::create_from_file("./ui/imagenes/imagenPrueba.png",
                          TAMANIO_ICONOS,
                                                        TAMANIO_ICONOS, true));
 }

Enviados::~Enviados() {
  delete ventanaOK;
  delete descargar;
}

