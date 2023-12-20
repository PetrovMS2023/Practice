#pragma once
#include <gtkmm.h>
#include <vector>
#include "MyDraw.hpp"
static int counter = 0;

// структура для описания сигнала
struct SignalA
{
int id; // уникальный id
float Ampl;
float Freq;
float Angl;
SignalA()
{
Ampl = 1;
Freq = 1;
Angl = 30;
id = counter;
counter++;
};
};

class mainWindow : public Gtk::Window
{
public:
mainWindow(int n = 1,int t = 4);
virtual ~mainWindow();

protected:
std::vector<SignalA> sgList; // список сигналов

// обработчики сигналов интерфейса
void on_button1_clicked();
void on_button2_clicked();
void refresh_list();
void listRowSelected(Gtk::ListBoxRow *lbr);

SignalA* findItem(Glib::ustring str);

// элементы интерфейса
Gtk::Button button1, button2,button3;
Gtk::Box box1,box2,box3,mainBox;
Gtk::Label label1,label2,label3;
Gtk::ListBox listBox1;
Gtk::Entry entry1,entry2,entry3;
Gtk::Grid grid1;
MyArea dArea; // элемент для отрисовки графика
bool onExposeEvent(GdkEventExpose* event);
};

