#ifndef CUSTOMEQLABEL_H
#define CUSTOMEQLABEL_H

#include <QLabel>

class CustomeQlabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomeQlabel(const QString &text = "", QWidget *parent = 0);
    ~CustomeQlabel() {}
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
public slots:
    void slotClicked();
};

#endif // CUSTOMEQLABEL_H
