
#include "prWindow.hpp"
#include <gtkmm.h>
#include <iostream>
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

// создание интерфейса
mainWindow::mainWindow(int n,int t)
{
Gtk::Box *tBox1 = new Gtk::Box();
Gtk::Box *tBox2 = new Gtk::Box();
Gtk::Box *tBox3 = new Gtk::Box();

button1.add_label("Сохранить");
button2.add_label("Добавить");
label1.set_text("амплитуда, В");
label2.set_text("частота, Гц");
label3.set_text("начальный угол, °");
set_title("Практика");
set_border_width(10);
add(mainBox);
mainBox.pack_start(box1);
mainBox.pack_start(box2);
mainBox.pack_start(box3);

listBox1.set_selection_mode(Gtk::SelectionMode::SELECTION_SINGLE);
box1.pack_start(listBox1);
dArea.setT(t);
box2.pack_start(dArea);

// для описания параметров сигнала
grid1.attach(label1,0,0,1,1);
grid1.attach(label2,0,1,1,1);
grid1.attach(label3,0,2,1,1);
grid1.attach(entry1,1,0,1,1);
grid1.attach(entry2,1,1,1,1);
grid1.attach(entry3,1,2,1,1);
grid1.attach(button1,0,3,1,1);
grid1.attach(button2,1,3,1,1);
box3.pack_start(grid1);

// прикрепление обработчиков
button1.signal_clicked().connect([this](){on_button1_clicked();});
button2.signal_clicked().connect([this](){on_button2_clicked();});
listBox1.signal_row_activated().connect(sigc::mem_fun(*this,&mainWindow::listRowSelected));

// генерация сигналов по умолчанию
for(int i=0;i<n;i++)
{
    SignalA *temp = new SignalA();
    sgList.push_back(*temp);
}
refresh_list();
}

mainWindow::~mainWindow()
{
}

// обработчик кнопки "Сохранить", сохраняет изменения параметров, в случае если выбран сигнал из списка
void mainWindow::on_button1_clicked()
{
    std::cout << "b1";
    Gtk::Label *temp2 = static_cast<Gtk::Label*>(listBox1.get_selected_row()->get_children()[0]);
    SignalA* temp1 = findItem(temp2->get_text());
    temp1->Ampl = std::stof(entry1.get_text());
    temp1->Freq = std::stof(entry2.get_text());
    temp1->Angl = std::stof(entry3.get_text());
}

// обработчик кнопки "Добавить", добавляет сигнал с указанными параметрами
void mainWindow::on_button2_clicked()
{
    std::cout << "b2";
    SignalA *temp = new SignalA();
    temp->Ampl = std::stof(entry1.get_text());
    temp->Freq = std::stof(entry2.get_text());
    temp->Angl = std::stof(entry3.get_text());
    sgList.push_back(*temp);
    refresh_list();
}

// обновление списка сигналов 
void mainWindow::refresh_list()
{
    Gtk::Label *labelTemp;
    Gtk::ListBoxRow *temp;
    for (Gtk::Widget* element : listBox1.get_children ())
        listBox1.remove (*element);
    if (sgList.size() >= 0)for (int i = 0 ;i<sgList.size();i++)
    {
    temp = new Gtk::ListBoxRow();
    labelTemp = new Gtk::Label("signal " + std::to_string(sgList[i].id));
    temp->add(*labelTemp);
    listBox1.append(*temp);
    }
    show_all_children();

}

// обработка смены выбранного сигнала для перерисовки графика и заполнения текстовых полей
inline void mainWindow::listRowSelected(Gtk::ListBoxRow *lbr)
{
Gtk::Label *temp = static_cast<Gtk::Label*>(listBox1.get_selected_row()->get_children()[0]);
SignalA* temp1 = findItem(temp->get_text());
if (temp!=nullptr)
{
    entry1.set_text(to_string_with_precision(temp1->Ampl));
    entry2.set_text(to_string_with_precision(temp1->Freq,0));
    entry3.set_text(to_string_with_precision(temp1->Angl));
    show_all_children();
}
std::cout << "f1";
dArea.setParam(temp1->Ampl,temp1->Freq,temp1->Angl);
dArea.queue_draw();
show_all_children();
}

// поиск сигнала по имени в списке
SignalA* mainWindow::findItem(Glib::ustring str)
{
    if (sgList.size() >= 0)for (int i = 0 ;i<sgList.size();i++)
    {
        Glib::ustring stemp("signal " + std::to_string(sgList[i].id));
        if (str==stemp)
            return &sgList[i];
    }
    return nullptr;
}


bool mainWindow::onExposeEvent(GdkEventExpose* event)
{
 return true;
}
