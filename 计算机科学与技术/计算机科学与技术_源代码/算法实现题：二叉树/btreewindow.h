#ifndef BTREEWINDOW_H
#define BTREEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <btree.h>

#define MyRadius 30
#define PreviousMode 1
#define PreOrderThreadMode 2
#define InOrderThreadMode 3
#define PostOrderThreadMode 4


namespace Ui {
class BtreeWindow;
}


class BtreeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BtreeWindow(QWidget *parent = nullptr);
    ~BtreeWindow();
    void Initial(QString &iniStr);
    bool TreeEst(QString qstr);
    void MyDrawTriangle(QPainter &, QPoint end, QPoint arrow);


private:
    Ui::BtreeWindow *ui;
    QString iniString;
    BTree bt;
    void PreOrderTraRecurPaint(QPainter &, BTreeNode *);
    int paintMode;
    void PreOrderThrPaint(QPainter &, BTreeNode *);
    void InOrderThrPaint(QPainter &, BTreeNode *);
    void PostOrderThrPaint(QPainter &, BTreeNode *);

public slots:
    void exitSlot();
    void backSlot();
    void PreOrdTraSlot();
    void InOrdTraSlot();
    void PostOrdTraSlot();
    void CountLeafNodeSlot();
    void InOrdThrSlot();
    void PostOrdThrSlot();
    void PreOrdThrSlot();
signals:
    void returnMain();

protected:
    void paintEvent(QPaintEvent *);
//    void repaint(int x, int y, int w, int h, bool erase = true);

};

#endif // BTREEWINDOW_H
