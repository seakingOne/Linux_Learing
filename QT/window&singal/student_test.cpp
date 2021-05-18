#include "student_test.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::entertain()
{
    qDebug() << "请老师吃饭";
}

void Student::entertain(QString foodName)
{
    qDebug() << "请老师吃饭, 要吃:" << foodName.toUtf8().data();
}
