#ifndef QREGISTRATIONDIALOG_H
#define QREGISTRATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QRadioButton>
#include <QButtonGroup>

class QLineEdit;

class QRegistrationDialog:public QDialog
{
    Q_OBJECT
public:
    QRegistrationDialog(QWidget *parent=0);
    ~QRegistrationDialog();
    QString ** getQString();
    bool Isvalid();
    void messageSet();
    void friendSet();
    void hobbySet();
    bool *getHobbyMes();
    bool *getFriendList();
//public slots:
//    virtual void accept();
//public slots:
//    void onButtonHobbyClicked(QAbstractButton *);
//    void onButtonFriendClicked();

private:
    QLabel * nameLabel;
    QLabel * regionLabel;
    QLabel * primarySchoolLabel;
    QLabel * middleSchoolLabel;
    QLabel * highSchoolLabel;
    QLabel * workOrginizationLabel;


    QLineEdit* nameLineEdit;
    QLineEdit* regionLineEdit;
    QLineEdit* primarySchoolLineEdit;
    QLineEdit* middleSchoolLineEdit;
    QLineEdit* highSchoolLineEdit;
    QLineEdit* workOrginizationLineEdit;



    QPushButton *okBtn;
    QPushButton *cancelBtn;

    QHBoxLayout *btnLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *dlgLayout;

    QString *message[6];
    bool hobbyMes[8];
    bool friendMes[10];


    //兴趣爱好
    QButtonGroup *HobbyGroup;

    QRadioButton *SwimmingButton;
    QRadioButton *BasketballButton;
    QRadioButton *FootballButton;
    QRadioButton *TaichiButton;
    QRadioButton *TennisButton;
    QRadioButton *ReadingButton;
    QRadioButton *GamingButton;
    QRadioButton *TravellingButton;


    QLabel *spaceLabel1;
    QLabel *TitleHobby;



    //好友列表
    QButtonGroup *FriendListGroup;

    QRadioButton *Friend1;
    QRadioButton *Friend2;
    QRadioButton *Friend3;
    QRadioButton *Friend4;
    QRadioButton *Friend5;
    QRadioButton *Friend6;
    QRadioButton *Friend7;
    QRadioButton *Friend8;
    QRadioButton *Friend9;
    QRadioButton *Friend10;

    QLabel *spaceLabel2;
    QLabel *TitleFriendList;


};

#endif // QREGISTRATIONDIALOG_H
