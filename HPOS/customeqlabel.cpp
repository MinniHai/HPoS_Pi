#include "customeqlabel.h"
#include <QDebug>

CustomeQlabel::CustomeQlabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    setText(text);
    connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void CustomeQlabel::slotClicked()
{
    qDebug() << "Clicked";
}

void CustomeQlabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
