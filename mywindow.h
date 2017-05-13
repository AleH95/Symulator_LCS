#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QPushButton>

class mywindow : public QPushButton
{
    Q_OBJECT
public:
    explicit mywindow(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *m_button;
};

#endif // MYWINDOW_H
