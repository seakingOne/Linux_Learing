#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "student_test.h"
#include "teacher_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void classIsOver();

private:
    Ui::Widget *ui;
    Student *stu;
    Teacher *teacher;

};
#endif // WIDGET_H
