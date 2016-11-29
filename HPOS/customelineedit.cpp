#include "customelineedit.h"
#include <QDebug>
#include "keyboard.h"


CustomeLineEdit::CustomeLineEdit( QWidget *parent)
    : QLineEdit(parent)
{

    connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
    clickCount = 0;
    timer = new QTimer(this);
}

void CustomeLineEdit::slotClicked()
{
    qDebug() << "Clicked";
    clickCount++;
    if(clickCount == 2) runKeyboard();

    if( !timer->isActive()){
        timer->singleShot(1000, this , SLOT(catchClick()));
    }
}

void CustomeLineEdit::catchClick()
{
    clickCount = 0;
}

void CustomeLineEdit::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

void CustomeLineEdit::setValidate(TextType type){
//    if(type == Password) {

//    } else if ()
    switch (type) {
    case Password:
        regex = "^(?=.*[^a-zA-Z])(?=.*[a-z])(?=.*[A-Z])\S{8,}$";
        break;
    case Name:
        regex = "/^[a-z ,.'-]+$/i";
        break;
    case Number:
        regex = "^\d$";
        break;
    case PhoneNumber:
        regex = "^(\+\d{1,2}\s)?\(?\d{3}\)?[\s.-]?\d{3}[\s.-]?\d{4}$";
        break;
    case Money:
        regex = "^-?(?:0|[1-9]\d{0,2}(?:,?\d{3})*)(?:\.\d+)?$";
        break;
    case DOB:
        break;
    default:
        break;
    }
}

void CustomeLineEdit::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = (QLineEdit *)sender();
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}
