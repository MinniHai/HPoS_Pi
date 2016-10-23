/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created: Wed Feb 29 21:59:51 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *backButton;
    QPushButton *clear;
    QGridLayout *gridLayout;
    QPushButton *Buttonq;
    QPushButton *Buttonw;
    QPushButton *Buttone;
    QPushButton *Buttonr;
    QPushButton *Buttont;
    QPushButton *Buttony;
    QPushButton *Buttonu;
    QPushButton *Buttoni;
    QPushButton *Buttono;
    QPushButton *Buttons;
    QPushButton *Buttond;
    QPushButton *Buttonf;
    QPushButton *Buttong;
    QPushButton *Buttonh;
    QPushButton *Buttonj;
    QPushButton *Buttonl;
    QPushButton *Buttonz;
    QPushButton *Buttonx;
    QPushButton *Buttonv;
    QPushButton *Buttonb;
    QPushButton *Buttonn;
    QPushButton *Buttonm;
    QPushButton *char_2;
    QPushButton *space;
    QPushButton *Button0;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *Button4;
    QPushButton *Button5;
    QPushButton *Button6;
    QPushButton *Button7;
    QPushButton *Button8;
    QPushButton *Button9;
    QPushButton *Buttonp;
    QPushButton *enterButton;
    QPushButton *Buttona;
    QPushButton *shift;
    QPushButton *Buttonc;
    QPushButton *Buttonk;

    void setupUi(QWidget *Keyboard)
    {
        if(Keyboard->objectName().isEmpty())
        {
            Keyboard->setObjectName(QString::fromUtf8("Keyboard"));
        }
        Keyboard->setWindowModality(Qt::NonModal);
        Keyboard->resize(480, 320);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Keyboard->sizePolicy().hasHeightForWidth());
        Keyboard->setSizePolicy(sizePolicy);
        Keyboard->setWindowTitle(QString::fromUtf8("Keyboard"));
        Keyboard->setStyleSheet(QString::fromUtf8(//"color: rgb(0,0,0);\n"
                                    "QToolTip{     border: 1px solid black;     background-color: #ffa02f;     padding: 1px;     border-radius: 3px;     opacity: 100;}QWidget{    color: #b1b1b1;    background-color: #323232;}QWidget:item:hover{    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);    color: #000000;}QWidget:item:selected{    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);}QMenuBar::item{    background: transparent;}QMenuBar::item:selected{    background: transparent;    border: 1px solid #ffaa00;}QMenuBar::item:pressed{    background: #444;    border: 1px solid #000;    background-color: QLinearGradient(        x1:0, y1:0,        x2:0, y2:1,        stop:1 #212121,        stop:0.4 #343434/*,        stop:0.2 #343434,        stop:0.1 #ffaa00*/    );    margin-bottom:-1px;    padding-bottom:1px;}QMenu{    border: 1px solid #000;}QMenu::item{    padding: 2px 20px 2px 20px;}QMenu::item:selected{    color: #000000;}QWidget:disabled{    color: #404040;    background-color: #323232;}QAbstractItemView{    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);}QWidget:focus{    /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/}QLineEdit{    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);    padding: 1px;    border-style: solid;    border: 1px solid #1e1e1e;    border-radius: 5;}QPushButton{    color: #b1b1b1;    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);    border-width: 1px;    border-color: #1e1e1e;    border-style: solid;    border-radius: 6;    padding: 3px;    font-size: 12px;    padding-left: 5px;    padding-right: 5px;}QPushButton:pressed{    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);}QComboBox{    selection-background-color: #ffaa00;    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);    border-style: solid;    border: 1px solid #1e1e1e;    border-radius: 5;}QComboBox:hover,QPushButton:hover{    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);}QComboBox:on{    padding-top: 3px;    padding-left: 4px;    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);    selection-background-color: #ffaa00;}QComboBox QAbstractItemView{    border: 2px solid darkgray;    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);}QComboBox::drop-down{     subcontrol-origin: padding;     subcontrol-position: top right;     width: 15px;     border-left-width: 0px;     border-left-color: darkgray;     border-left-style: solid; /* just a single line */     border-top-right-radius: 3px; /* same radius as the QComboBox */     border-bottom-right-radius: 3px; }QComboBox::down-arrow{     image: url(:/down_arrow.png);}QGroupBox:focus{border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);}QTextEdit:focus{    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);}QScrollBar:horizontal {     border: 1px solid #222222;     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);     height: 7px;     margin: 0px 16px 0 16px;}QScrollBar::handle:horizontal{      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);      min-height: 20px;      border-radius: 2px;}QScrollBar::add-line:horizontal {      border: 1px solid #1b1b19;      border-radius: 2px;      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);      width: 14px;      subcontrol-position: right;      subcontrol-origin: margin;}QScrollBar::sub-line:horizontal {      border: 1px solid #1b1b19;      border-radius: 2px;      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);      width: 14px;     subcontrol-position: left;     subcontrol-origin: margin;}QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal{      border: 1px solid black;      width: 1px;      height: 1px;      background: white;}QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal{      background: none;}QScrollBar:vertical{      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);      width: 7px;      margin: 16px 0 16px 0;      border: 1px solid #222222;}QScrollBar::handle:vertical{      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);      min-height: 20px;      border-radius: 2px;}QScrollBar::add-line:vertical{      border: 1px solid #1b1b19;      border-radius: 2px;      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);      height: 14px;      subcontrol-position: bottom;      subcontrol-origin: margin;}QScrollBar::sub-line:vertical{      border: 1px solid #1b1b19;      border-radius: 2px;      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);      height: 14px;      subcontrol-position: top;      subcontrol-origin: margin;}QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical{      border: 1px solid black;      width: 1px;      height: 1px;      background: white;}QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{      background: none;}QTextEdit{    background-color: #242424;}QPlainTextEdit{    background-color: #242424;}QHeaderView::section{    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);    color: white;    padding-left: 4px;    border: 1px solid #6c6c6c;}QCheckBox:disabled{color: #414141;}QDockWidget::title{    text-align: center;    spacing: 3px; /* spacing between items in the tool bar */    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);}QDockWidget::close-button, QDockWidget::float-button{    text-align: center;    spacing: 1px; /* spacing between items in the tool bar */    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);}QDockWidget::close-button:hover, QDockWidget::float-button:hover{    background: #242424;}QDockWidget::close-button:pressed, QDockWidget::float-button:pressed{    padding: 1px -1px -1px 1px;}QMainWindow::separator{    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);    color: white;    padding-left: 4px;    border: 1px solid #4c4c4c;    spacing: 3px; /* spacing between items in the tool bar */}QMainWindow::separator:hover{    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);    color: white;    padding-left: 4px;    border: 1px solid #6c6c6c;    spacing: 3px; /* spacing between items in the tool bar */}QToolBar::handle{     spacing: 3px; /* spacing between items in the tool bar */     background: url(:/images/handle.png);}QMenu::separator{    height: 2px;    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);    color: white;    padding-left: 4px;    margin-left: 10px;    margin-right: 5px;}QProgressBar{    border: 2px solid grey;    border-radius: 5px;    text-align: center;}QProgressBar::chunk{    background-color: #d7801a;    width: 2.15px;    margin: 0.5px;}QTabBar::tab {    color: #b1b1b1;    border: 1px solid #444;    border-bottom-style: none;    background-color: #323232;    padding-left: 10px;    padding-right: 10px;    padding-top: 3px;    padding-bottom: 2px;    margin-right: -1px;}QTabWidget::pane {    border: 1px solid #444;    top: 1px;}QTabBar::tab:last{    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */    border-top-right-radius: 3px;}QTabBar::tab:first:!selected{ margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */    border-top-left-radius: 3px;}QTabBar::tab:!selected{    color: #b1b1b1;    border-bottom-style: solid;    margin-top: 3px;    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);}QTabBar::tab:selected{    border-top-left-radius: 3px;    border-top-right-radius: 3px;    margin-bottom: 0px;}QTabBar::tab:!selected:hover{    /*border-top: 2px solid #ffaa00;    padding-bottom: 3px;*/    border-top-left-radius: 3px;    border-top-right-radius: 3px;    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);}QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{    color: #b1b1b1;    background-color: #323232;    border: 1px solid #b1b1b1;    border-radius: 6px;}QRadioButton::indicator:checked{    background-color: qradialgradient(        cx: 0.5, cy: 0.5,        fx: 0.5, fy: 0.5,        radius: 1.0,        stop: 0.25 #ffaa00,        stop: 0.3 #323232    );}QCheckBox::indicator{    color: #b1b1b1;    background-color: #323232;    border: 1px solid #b1b1b1;    width: 9px;    height: 9px;}QRadioButton::indicator{    border-radius: 6px;}QRadioButton::indicator:hover, QCheckBox::indicator:hover{    border: 1px solid #ffaa00;}QCheckBox::indicator:checked{    image:url(:/images/checkbox.png);}QCheckBox::indicator:disabled, QRadioButton::indicator:disabled{    border: 1px solid #444;}"
                                ));
        verticalLayout = new QVBoxLayout(Keyboard);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(Keyboard);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255); font-size: 25px; border: 1px solid #ffaa00;"));

        horizontalLayout->addWidget(lineEdit);

        backButton = new QPushButton(Keyboard);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setStyleSheet("QPushButton{ padding: 6px; background-color:#2658F5;color: #FFFFFF; border-color:#FFFFFF;height: 25px;width: 32px;font-size: 12px;}");

        horizontalLayout->addWidget(backButton);

        clear = new QPushButton(Keyboard);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setStyleSheet("  padding: 6px; border-color:#FFEFB8 ;background-color:#F5100E;color: #FFFFFF;border-color:#FFFFFF; height: 25px;width: 32px;font-size: 12px;");
        horizontalLayout->addWidget(clear);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Buttonq = new QPushButton(Keyboard);
        Buttonq->setObjectName(QString::fromUtf8("Buttonq"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Buttonq->sizePolicy().hasHeightForWidth());
        Buttonq->setSizePolicy(sizePolicy1);
        Buttonq->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonq, 1, 0, 1, 1);

        Buttonw = new QPushButton(Keyboard);
        Buttonw->setObjectName(QString::fromUtf8("Buttonw"));
        sizePolicy1.setHeightForWidth(Buttonw->sizePolicy().hasHeightForWidth());
        Buttonw->setSizePolicy(sizePolicy1);
        Buttonw->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonw, 1, 1, 1, 1);

        Buttone = new QPushButton(Keyboard);
        Buttone->setObjectName(QString::fromUtf8("Buttone"));
        sizePolicy1.setHeightForWidth(Buttone->sizePolicy().hasHeightForWidth());
        Buttone->setSizePolicy(sizePolicy1);
        Buttone->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttone, 1, 2, 1, 1);

        Buttonr = new QPushButton(Keyboard);
        Buttonr->setObjectName(QString::fromUtf8("Buttonr"));
        sizePolicy1.setHeightForWidth(Buttonr->sizePolicy().hasHeightForWidth());
        Buttonr->setSizePolicy(sizePolicy1);
        Buttonr->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonr, 1, 3, 1, 1);

        Buttont = new QPushButton(Keyboard);
        Buttont->setObjectName(QString::fromUtf8("Buttont"));
        sizePolicy1.setHeightForWidth(Buttont->sizePolicy().hasHeightForWidth());
        Buttont->setSizePolicy(sizePolicy1);
        Buttont->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttont, 1, 4, 1, 1);

        Buttony = new QPushButton(Keyboard);
        Buttony->setObjectName(QString::fromUtf8("Buttony"));
        sizePolicy1.setHeightForWidth(Buttony->sizePolicy().hasHeightForWidth());
        Buttony->setSizePolicy(sizePolicy1);
        Buttony->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttony, 1, 5, 1, 1);

        Buttonu = new QPushButton(Keyboard);
        Buttonu->setObjectName(QString::fromUtf8("Buttonu"));
        sizePolicy1.setHeightForWidth(Buttonu->sizePolicy().hasHeightForWidth());
        Buttonu->setSizePolicy(sizePolicy1);
        Buttonu->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonu, 1, 6, 1, 1);

        Buttoni = new QPushButton(Keyboard);
        Buttoni->setObjectName(QString::fromUtf8("Buttoni"));
        sizePolicy1.setHeightForWidth(Buttoni->sizePolicy().hasHeightForWidth());
        Buttoni->setSizePolicy(sizePolicy1);
        Buttoni->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttoni, 1, 7, 1, 1);

        Buttono = new QPushButton(Keyboard);
        Buttono->setObjectName(QString::fromUtf8("Buttono"));
        sizePolicy1.setHeightForWidth(Buttono->sizePolicy().hasHeightForWidth());
        Buttono->setSizePolicy(sizePolicy1);
        Buttono->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttono, 1, 8, 1, 1);

        Buttons = new QPushButton(Keyboard);
        Buttons->setObjectName(QString::fromUtf8("Buttons"));
        sizePolicy1.setHeightForWidth(Buttons->sizePolicy().hasHeightForWidth());
        Buttons->setSizePolicy(sizePolicy1);
        Buttons->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttons, 3, 1, 1, 1);

        Buttond = new QPushButton(Keyboard);
        Buttond->setObjectName(QString::fromUtf8("Buttond"));
        sizePolicy1.setHeightForWidth(Buttond->sizePolicy().hasHeightForWidth());
        Buttond->setSizePolicy(sizePolicy1);
        Buttond->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttond, 3, 2, 1, 1);

        Buttonf = new QPushButton(Keyboard);
        Buttonf->setObjectName(QString::fromUtf8("Buttonf"));
        sizePolicy1.setHeightForWidth(Buttonf->sizePolicy().hasHeightForWidth());
        Buttonf->setSizePolicy(sizePolicy1);
        Buttonf->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonf, 3, 3, 1, 1);

        Buttong = new QPushButton(Keyboard);
        Buttong->setObjectName(QString::fromUtf8("Buttong"));
        sizePolicy1.setHeightForWidth(Buttong->sizePolicy().hasHeightForWidth());
        Buttong->setSizePolicy(sizePolicy1);
        Buttong->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttong, 3, 4, 1, 1);

        Buttonh = new QPushButton(Keyboard);
        Buttonh->setObjectName(QString::fromUtf8("Buttonh"));
        sizePolicy1.setHeightForWidth(Buttonh->sizePolicy().hasHeightForWidth());
        Buttonh->setSizePolicy(sizePolicy1);
        Buttonh->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonh, 3, 5, 1, 1);

        Buttonj = new QPushButton(Keyboard);
        Buttonj->setObjectName(QString::fromUtf8("Buttonj"));
        sizePolicy1.setHeightForWidth(Buttonj->sizePolicy().hasHeightForWidth());
        Buttonj->setSizePolicy(sizePolicy1);
        Buttonj->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonj, 3, 6, 1, 1);

        Buttonl = new QPushButton(Keyboard);
        Buttonl->setObjectName(QString::fromUtf8("Buttonl"));
        sizePolicy1.setHeightForWidth(Buttonl->sizePolicy().hasHeightForWidth());
        Buttonl->setSizePolicy(sizePolicy1);
        Buttonl->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonl, 3, 8, 1, 1);

        Buttonz = new QPushButton(Keyboard);
        Buttonz->setObjectName(QString::fromUtf8("Buttonz"));
        sizePolicy1.setHeightForWidth(Buttonz->sizePolicy().hasHeightForWidth());
        Buttonz->setSizePolicy(sizePolicy1);
        Buttonz->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonz, 4, 1, 1, 1);

        Buttonx = new QPushButton(Keyboard);
        Buttonx->setObjectName(QString::fromUtf8("Buttonx"));
        sizePolicy1.setHeightForWidth(Buttonx->sizePolicy().hasHeightForWidth());
        Buttonx->setSizePolicy(sizePolicy1);
        Buttonx->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonx, 4, 2, 1, 1);

        Buttonv = new QPushButton(Keyboard);
        Buttonv->setObjectName(QString::fromUtf8("Buttonv"));
        sizePolicy1.setHeightForWidth(Buttonv->sizePolicy().hasHeightForWidth());
        Buttonv->setSizePolicy(sizePolicy1);
        Buttonv->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonv, 4, 4, 1, 1);

        Buttonb = new QPushButton(Keyboard);
        Buttonb->setObjectName(QString::fromUtf8("Buttonb"));
        sizePolicy1.setHeightForWidth(Buttonb->sizePolicy().hasHeightForWidth());
        Buttonb->setSizePolicy(sizePolicy1);
        Buttonb->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonb, 4, 5, 1, 1);

        Buttonn = new QPushButton(Keyboard);
        Buttonn->setObjectName(QString::fromUtf8("Buttonn"));
        sizePolicy1.setHeightForWidth(Buttonn->sizePolicy().hasHeightForWidth());
        Buttonn->setSizePolicy(sizePolicy1);
        Buttonn->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonn, 4, 6, 1, 1);

        Buttonm = new QPushButton(Keyboard);
        Buttonm->setObjectName(QString::fromUtf8("Buttonm"));
        sizePolicy1.setHeightForWidth(Buttonm->sizePolicy().hasHeightForWidth());
        Buttonm->setSizePolicy(sizePolicy1);
        Buttonm->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonm, 4, 7, 1, 1);

        char_2 = new QPushButton(Keyboard);
        char_2->setObjectName(QString::fromUtf8("char_2"));
        sizePolicy1.setHeightForWidth(char_2->sizePolicy().hasHeightForWidth());
        char_2->setSizePolicy(sizePolicy1);
        char_2->setMinimumSize(QSize(20, 0));
        char_2->setCheckable(true);
        char_2->setChecked(false);

        gridLayout->addWidget(char_2, 4, 8, 2, 1);

        space = new QPushButton(Keyboard);
        space->setObjectName(QString::fromUtf8("space"));
        space->setMinimumSize(QSize(20, 50));

        gridLayout->addWidget(space, 5, 1, 1, 7);

        Button0 = new QPushButton(Keyboard);
        Button0->setObjectName(QString::fromUtf8("Button0"));
        sizePolicy1.setHeightForWidth(Button0->sizePolicy().hasHeightForWidth());
        Button0->setSizePolicy(sizePolicy1);
        Button0->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button0, 0, 0, 1, 1);

        Button1 = new QPushButton(Keyboard);
        Button1->setObjectName(QString::fromUtf8("Button1"));
        sizePolicy1.setHeightForWidth(Button1->sizePolicy().hasHeightForWidth());
        Button1->setSizePolicy(sizePolicy1);
        Button1->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button1, 0, 1, 1, 1);

        Button2 = new QPushButton(Keyboard);
        Button2->setObjectName(QString::fromUtf8("Button2"));
        sizePolicy1.setHeightForWidth(Button2->sizePolicy().hasHeightForWidth());
        Button2->setSizePolicy(sizePolicy1);
        Button2->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button2, 0, 2, 1, 1);

        Button3 = new QPushButton(Keyboard);
        Button3->setObjectName(QString::fromUtf8("Button3"));
        sizePolicy1.setHeightForWidth(Button3->sizePolicy().hasHeightForWidth());
        Button3->setSizePolicy(sizePolicy1);
        Button3->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button3, 0, 3, 1, 1);

        Button4 = new QPushButton(Keyboard);
        Button4->setObjectName(QString::fromUtf8("Button4"));
        sizePolicy1.setHeightForWidth(Button4->sizePolicy().hasHeightForWidth());
        Button4->setSizePolicy(sizePolicy1);
        Button4->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button4, 0, 4, 1, 1);

        Button5 = new QPushButton(Keyboard);
        Button5->setObjectName(QString::fromUtf8("Button5"));
        sizePolicy1.setHeightForWidth(Button5->sizePolicy().hasHeightForWidth());
        Button5->setSizePolicy(sizePolicy1);
        Button5->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button5, 0, 5, 1, 1);

        Button6 = new QPushButton(Keyboard);
        Button6->setObjectName(QString::fromUtf8("Button6"));
        sizePolicy1.setHeightForWidth(Button6->sizePolicy().hasHeightForWidth());
        Button6->setSizePolicy(sizePolicy1);
        Button6->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button6, 0, 6, 1, 1);

        Button7 = new QPushButton(Keyboard);
        Button7->setObjectName(QString::fromUtf8("Button7"));
        sizePolicy1.setHeightForWidth(Button7->sizePolicy().hasHeightForWidth());
        Button7->setSizePolicy(sizePolicy1);
        Button7->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button7, 0, 7, 1, 1);

        Button8 = new QPushButton(Keyboard);
        Button8->setObjectName(QString::fromUtf8("Button8"));
        sizePolicy1.setHeightForWidth(Button8->sizePolicy().hasHeightForWidth());
        Button8->setSizePolicy(sizePolicy1);
        Button8->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button8, 0, 8, 1, 1);

        Button9 = new QPushButton(Keyboard);
        Button9->setObjectName(QString::fromUtf8("Button9"));
        sizePolicy1.setHeightForWidth(Button9->sizePolicy().hasHeightForWidth());
        Button9->setSizePolicy(sizePolicy1);
        Button9->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Button9, 0, 9, 1, 1);

        Buttonp = new QPushButton(Keyboard);
        Buttonp->setObjectName(QString::fromUtf8("Buttonp"));
        sizePolicy1.setHeightForWidth(Buttonp->sizePolicy().hasHeightForWidth());
        Buttonp->setSizePolicy(sizePolicy1);
        Buttonp->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonp, 1, 9, 1, 1);

        enterButton = new QPushButton(Keyboard);
        enterButton->setObjectName(QString::fromUtf8("enterButton"));
        sizePolicy1.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy1);
        enterButton->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(enterButton, 3, 9, 3, 1);

        Buttona = new QPushButton(Keyboard);
        Buttona->setObjectName(QString::fromUtf8("Buttona"));
        sizePolicy1.setHeightForWidth(Buttona->sizePolicy().hasHeightForWidth());
        Buttona->setSizePolicy(sizePolicy1);
        Buttona->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttona, 3, 0, 1, 1);

        shift = new QPushButton(Keyboard);
        shift->setObjectName(QString::fromUtf8("shift"));
        sizePolicy1.setHeightForWidth(shift->sizePolicy().hasHeightForWidth());
        shift->setSizePolicy(sizePolicy1);
        shift->setMinimumSize(QSize(20, 0));
        shift->setStyleSheet(QString::fromUtf8(""));
        shift->setCheckable(false);

        gridLayout->addWidget(shift, 4, 0, 2, 1);

        Buttonc = new QPushButton(Keyboard);
        Buttonc->setObjectName(QString::fromUtf8("Buttonc"));
        sizePolicy1.setHeightForWidth(Buttonc->sizePolicy().hasHeightForWidth());
        Buttonc->setSizePolicy(sizePolicy1);
        Buttonc->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonc, 4, 3, 1, 1);

        Buttonk = new QPushButton(Keyboard);
        Buttonk->setObjectName(QString::fromUtf8("Buttonk"));
        sizePolicy1.setHeightForWidth(Buttonk->sizePolicy().hasHeightForWidth());
        Buttonk->setSizePolicy(sizePolicy1);
        Buttonk->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(Buttonk, 3, 7, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        backButton->setText(QApplication::translate("Keyboard", "Back", 0));
        clear->setText(QApplication::translate("Keyboard", "Clear", 0));
        Buttonq->setText(QApplication::translate("Keyboard", "q", 0));
        Buttonw->setText(QApplication::translate("Keyboard", "w", 0));
        Buttone->setText(QApplication::translate("Keyboard", "e", 0));
        Buttonr->setText(QApplication::translate("Keyboard", "r", 0));
        Buttont->setText(QApplication::translate("Keyboard", "t", 0));
        Buttony->setText(QApplication::translate("Keyboard", "y", 0));
        Buttonu->setText(QApplication::translate("Keyboard", "u", 0));
        Buttoni->setText(QApplication::translate("Keyboard", "i", 0));
        Buttono->setText(QApplication::translate("Keyboard", "o", 0));
        Buttons->setText(QApplication::translate("Keyboard", "s", 0));
        Buttond->setText(QApplication::translate("Keyboard", "d", 0));
        Buttonf->setText(QApplication::translate("Keyboard", "f", 0));
        Buttong->setText(QApplication::translate("Keyboard", "g", 0));
        Buttonh->setText(QApplication::translate("Keyboard", "h", 0));
        Buttonj->setText(QApplication::translate("Keyboard", "j", 0));
        Buttonl->setText(QApplication::translate("Keyboard", "l", 0));
        Buttonz->setText(QApplication::translate("Keyboard", "z", 0));
        Buttonx->setText(QApplication::translate("Keyboard", "x", 0));
        Buttonv->setText(QApplication::translate("Keyboard", "v", 0));
        Buttonb->setText(QApplication::translate("Keyboard", "b", 0));
        Buttonn->setText(QApplication::translate("Keyboard", "n", 0));
        Buttonm->setText(QApplication::translate("Keyboard", "m", 0));
        char_2->setText(QApplication::translate("Keyboard", "Char", 0));
        space->setText(QApplication::translate("Keyboard", "Space", 0));
        Button0->setText(QApplication::translate("Keyboard", "0", 0));
        Button1->setText(QApplication::translate("Keyboard", "1", 0));
        Button2->setText(QApplication::translate("Keyboard", "2", 0));
        Button3->setText(QApplication::translate("Keyboard", "3", 0));
        Button4->setText(QApplication::translate("Keyboard", "4", 0));
        Button5->setText(QApplication::translate("Keyboard", "5", 0));
        Button6->setText(QApplication::translate("Keyboard", "6", 0));
        Button7->setText(QApplication::translate("Keyboard", "7", 0));
        Button8->setText(QApplication::translate("Keyboard", "8", 0));
        Button9->setText(QApplication::translate("Keyboard", "9", 0));
        Buttonp->setText(QApplication::translate("Keyboard", "p", 0));
        enterButton->setText(QApplication::translate("Keyboard", "Enter", 0));
        Buttona->setText(QApplication::translate("Keyboard", "a", 0));
        shift->setText(QApplication::translate("Keyboard", "Shift", 0));
        Buttonc->setText(QApplication::translate("Keyboard", "c", 0));
        Buttonk->setText(QApplication::translate("Keyboard", "k", 0));
        Q_UNUSED(Keyboard);
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
