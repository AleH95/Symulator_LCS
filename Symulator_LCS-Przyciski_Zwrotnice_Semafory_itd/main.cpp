#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}


/*
 * Some Code Examples
 *
        QWidget *window = new QWidget;
            QPushButton *button1 = new QPushButton("One");
            QPushButton *button2 = new QPushButton("Two");
            QPushButton *button3 = new QPushButton("Three");
            QPushButton *button4 = new QPushButton("Four");
            QPushButton *button5 = new QPushButton("Five");

            QGridLayout *layout = new QGridLayout;
            layout->addWidget(button1, 0, 0);
            layout->addWidget(button2, 0, 1);
            layout->addWidget(button3, 1, 0, 1, 2);
            layout->addWidget(button4, 2, 0);
            layout->addWidget(button5, 2, 1);

            window->setLayout(layout);
            window->show();
*
* void MainWindow::createLayout()
    {
        QGridLayout *layout = new QGridLayout(this);
        layout->setMargin(6);
        layout->setSpacing(6);

        for (int i = 0; i < 9; ++i)
            layout->addWidget(butt_zwr[i + 1], i / 3, i % 3);
        layout->addWidget(butt_zwr[0], 3, 1);
        }
*
*
*/
