#ifndef CUSTOMECOMBOBOX_H
#define CUSTOMECOMBOBOX_H

#include <QComboBox>
#include <QTimer>
#include <QLineEdit>

class CustomeLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    enum TextType{
        Password,
        Name,
        Number,
        PhoneNumber,
        Money,
        DOB
    };

    QString regex;
    void setValidate(TextType type);
    explicit CustomeLineEdit(QWidget *parent = 0);
    ~CustomeLineEdit() {}
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
public slots:
    void slotClicked();

private slots:
    void runKeyboard();
    void catchClick();
private :
     int clickCount;
     QTimer *timer;
};

#endif // CUSTOMECOMBOBOX_H
