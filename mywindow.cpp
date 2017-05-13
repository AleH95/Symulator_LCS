#include "mywindow.h"

mywindow::mywindow(QWidget *parent) :
    QWidget(parent)
{
    // Set size of the window
    setFixedSize(1280, 720);
    // Create and position the button
    m_button = new QPushButton("Hello World", this);
    m_button->setGeometry(10, 10, 80, 30);
}
