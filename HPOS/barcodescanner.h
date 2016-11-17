
#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H


//#include "opencv/cv.h"
//#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <zbar.h>
#include "zbar/Image.h"
#include "zbar/ImageScanner.h"
#include "zbar/Video.h"

#include <QDebug>
#include <QTimer>
#include <QLabel>

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    BarcodeScanner();

    static BarcodeScanner *s_instance;
    static BarcodeScanner *instance();

    ~BarcodeScanner();
    void scanBarcode();
    void setLableScan(QLabel *scan);
    void setLableQty(QLabel *qty);
    void setTimer(QTimer *timer);
    void releaseCam();
    void capturePicture(QString imagePath, QLabel *label);
    void movePicture(QString inputPath, QString outputPath);
    void checkCam();
    bool isValidBarcode(QString barcode);
    QList<IplImage *> getListBarcode (IplImage *image);
    QList<QString> listBarcode;
    QString getSymbols()
    {
        return symbols;
    }
    void setSymbols(QString blank);
    int qty;
    QTimer *timer;
    QTimer *timer2;
    bool isCapture;
    QString imagePath;
private slots:
    void processFrame();
    void processFrameForCapture();

private:

    IplImage *imSrc;
    QImage img_show;

    QLabel *lblScan;
    QLabel *lblQty;
    int scanSymbol(IplImage *src);
    QString symbols;
};

#endif // SCANNER_H
