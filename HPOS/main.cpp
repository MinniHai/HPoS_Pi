#include "s_waiting.h"
#include <QTimer>
#include <QApplication>
#include "s_login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    S_Waiting w;
    S_Login *login = S_Login::instance();
    w.showFullScreen();
    // sau 2500 ms sẽ close waiting  và bật lại login
    QTimer::singleShot(1500, login , SLOT(showFullScreen()));
    QTimer::singleShot(1500, &w, SLOT(close()));

    return a.exec();
}
