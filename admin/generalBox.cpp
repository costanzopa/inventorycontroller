#include "generalBox.h"

/****** CONSTRUCTOR ******/

GeneralBox::GeneralBox(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>&builder):Gtk::Box(cobject){
	builder -> get_widget_derived("stockGeneralIconos", productosIconos);
	Gtk::DrawingArea* dibujo;
	builder -> get_widget("stockGeneralDrawing", dibujo);
	grafico = new GraficoDeBarras(dibujo, GBARRAS_COMPARACION);
}

/****** ACTUALIZAR LOS PRODUCTOS ******/

void GeneralBox::actualizarDatos(std::vector<std::string> productos, std::vector<std::string> iconos, std::vector<int> stock){
	std::vector<std::string> labels;
	std::stringstream s;
	for(int i = 0; i < productos.size(); i++){
		s << stock[i];
		labels.push_back(productos[i]+"\n"+s.str());
		s.str("");
	}
	productosIconos -> setItems(labels,iconos);
	grafico -> setDatos(productos,stock);
}

/****** STOCK ******/

void GeneralBox::recibirStockGeneral(std::vector<std::pair<std::string, int> > stock){
	std::vector<int> stock2;
	for(int i = 0; i < stock.size(); i++){
		stock2.push_back(stock[i].second);
	}
	grafico -> setDatos(productos,stock2);
}

/****** DESTRUCTOR ******/

GeneralBox::~GeneralBox(){
	delete grafico;
}

