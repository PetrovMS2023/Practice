#include "MyDraw.hpp"
#include <gtkmm.h>
#include <cairomm/context.h>
#include <sstream>
#define PI 3.14159265

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}
// конструктор с параметрами по умолчанию
MyArea::MyArea()
{
set_size_request(600,300);
a=1;
b=1;
c=30;
t=4;
}

MyArea::~MyArea()
{
}

// функция для нахождения сигнала
gfloat MyArea::f (gfloat x)
{
    return a * sin ((2*b*PI)*x+c*PI/180);
}

// для установки параметров функции сигнала
void MyArea::setParam(double a, double b, double c)
{
    this->a=a;
    this->b=b;
    this->c=c;
}

// задать время
void MyArea::setT(double t)
{
    this->t=t;
}

// основная функция отрисовки
bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  const int intX = 10,intY = 6,pX=t,pY=2;

  // масштабирование до прямоугольника (значения ширины и высоты рабочей области зависят от pX и pY)
  cr->translate(0,height/2);
  cr->scale(width/pX, height/pY);
  cr->set_line_width(0.01);

  // для задания осей
  cr->set_source_rgba(0, 0, 0, 1);
  cr->move_to(0, -1);
  cr->line_to(0,1);
  cr->stroke();
  cr->move_to(0, 0);
  cr->line_to(t, 0);
  cr->stroke();
  cr->select_font_face("Courier",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
  cr->set_font_size(0.15);

  // деления оси X
  for (int i = 1; i<intX; i++ )
  {
    cr->move_to(i*((float)pX/intX),0);
    cr->line_to(i*((float)pX/intX),(float)pY/20);
    cr->move_to(i*((float)pX/intX),1);
    cr->show_text(to_string_with_precision(i*((float)pX/intX)));
  }
  cr->stroke();

  // деления оси Y
  for (int i = 0; i<intY; i++ )
  {
    cr->move_to(0,pY/2-i*((float)pY/intY));
    cr->line_to((float)pX/40,pY/2-i*((float)pY/intY));
    cr->move_to(pX/40+0.02,(pY/2-i*((float)pY/intY))-0.02);
    cr->show_text(to_string_with_precision(-(pY/2-i*((float)pY/intY))));
  }
  cr->stroke();

  cr->set_source_rgba(1, 0.2, 0.2, 0.6);
  cr->move_to(0, f(0));

  // отрисовка сигнала
  for (double i = 0; i <= t; i += 0.0005)
        {
        cr->line_to(i,-f(i));
        cr->move_to(i,-f(i));
        }
  cr->stroke();

  return true;

}
