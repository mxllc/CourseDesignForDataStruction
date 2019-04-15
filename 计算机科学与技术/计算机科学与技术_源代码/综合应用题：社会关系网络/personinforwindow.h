#ifndef PERSONINFORWINDOW_H
#define PERSONINFORWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTransform>
#include "mgraph.h"
#include <math.h>

#define mypi 3.14159265359
#define polygonX 150

namespace Ui {
class PersonInforWindow;
}

class PersonInforWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PersonInforWindow(QWidget *parent = nullptr);
    ~PersonInforWindow();
    void SetMGraph(MGraph *);
    void setIdNum(int );

private:
    Ui::PersonInforWindow *ui;
    QLabel *desLabel;
    MGraph *mg;
    int IdNum;




public slots:
    void exitSlot();
    void backSlot();
signals:
    void returnNetwork();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // PERSONINFORWINDOW_H
