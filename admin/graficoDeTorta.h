#ifndef GRAFICO_TORTA
#define GRAFICO_TORTA
#include <gtkmm.h>
#include <cairomm/context.h>
#include <vector>
class GraficoDeTorta{
	private:
		std::vector<std::pair<std::string,int> > stock;
		Gtk::DrawingArea* dibujo;	
		Glib::RefPtr<Gdk::Window> win;
		int width;
		int anti;
		std::vector<float> red;
		std::vector<float> green;
		std::vector<float> blue;
	public:
		void mezclarColores();
		void setearDatos(std::vector<std::pair<std::string, int> > stock);
		GraficoDeTorta(Gtk::DrawingArea* dibujo);
		void dibujarArco(const Cairo::RefPtr<Cairo::Context>& c,int x, int y, int radio,float angulo0,float angulo1,float r, float g, float b);
		bool dibujar(const Cairo::RefPtr<Cairo::Context>& contexto);
		void dibujarStock();
};
#endif
