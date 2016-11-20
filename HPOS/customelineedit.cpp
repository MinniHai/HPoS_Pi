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
void CustomeLineEdit::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = (QLineEdit *)sender();

    line->setPlaceholderText("Product Name");
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}
