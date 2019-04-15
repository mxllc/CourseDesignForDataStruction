#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QInputDialog>
#include "mgraph.h"
#include "qregistrationdialog.h"
#include "personinforwindow.h"



#define polygonX 150

namespace Ui {
class NetWork;
}

class NetWork : public QWidget
{
    Q_OBJECT

public:
    explicit NetWork(QWidget *parent = nullptr);
    ~NetWork();

private:
    Ui::NetWork *ui;
    MGraph mg;
    PersonInforWindow piw;

public slots:
    void exitSlot();
    void backSlot();
    void tableOutSlot();
    void addNodeButtonSlot();
    void PersonInfoBackSlot();
    void DeInfoSlot();
signals:
    void returnMain();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // NETWORK_H
