#include "widget.h"
#include "ui_widget.h"
#include "mybutton.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myButton *btn = new myButton(this);

    btn->setText("my customer button");
    btn->move(200, 400);

    //connect(btn, &myButton::clicked, this, &Widget::close);

    // 自定义信号和卡槽
    teacher = new Teacher(this);
    stu = new Student(this);


    //函数指针操作
    void (Teacher::*tmethod)(QString) = &Teacher::hungry;
    void (Student::*entertain)(QString) = &Student::entertain;


    //connect(btn, &myButton::clicked, teacher, tmethod);
    connect(teacher, tmethod, stu, entertain);

    classIsOver();

}

void Widget::classIsOver()
{
    emit teacher->hungry("小炒肉");
}


Widget::~Widget()
{

    qDebug("析构widget");
    delete ui;
}

