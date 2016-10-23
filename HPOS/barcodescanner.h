
#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H

/*
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <zbar.h>
#include "zbar/Image.h"
#include "zbar/ImageScanner.h"
#include "zbar/Video.h"
*/
#include <QDebug>
#include <QTimer>
#include <QLabel>

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    BarcodeScanner();
    /*
    ~BarcodeScanner();
    void scanBarcode();
    void setLableScan(QLabel *scan);
    void setTimer(QTimer *timer);
    void releaseCam();
    void checkCam();
    QString getSymbols()
    {
        return symbols;
    }
    void setSymbols(QString blank);
    */
private slots:
    //void processFrame();

private:

    //IplImage *src;
    QImage img_show;

    QLabel *lblScan;
    //    int scanSymbol(IplImage *src);
    QString symbols;
    QTimer *timer;
};

#endif // SCANNER_H
