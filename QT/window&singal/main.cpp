#include "widget.h"

#include <QApplication>
#include <QPushButton>

#include "mybutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle("test");

//    QPushButton *train_button = new QPushButton(&w);
//    train_button->setText("123");
//    train_button->move(200, 200);
//    train_button->show();

    w.show();






    return a.exec();
}
