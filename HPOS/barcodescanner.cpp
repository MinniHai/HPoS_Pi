#include "barcodescanner.h"


/*

using namespace zbar;
using namespace cv;

CvCapture *capture;
*/
BarcodeScanner::BarcodeScanner()
{
    symbols = "";
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(processFrame()));
}

/*
BarcodeScanner::~BarcodeScanner()
{
    cvReleaseCapture(&capture);
}

void BarcodeScanner::releaseCam()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    cvReleaseCapture(&capture);
}

void BarcodeScanner::setTimer(QTimer *timer)
{
    this->timer = timer;
}

void BarcodeScanner::checkCam()
{
    if(capture == 0)
    {
        capture = cvCaptureFromCAM(CV_CAP_ANY);
        if(capture)
        {
            symbols = "Camera Allready!";
        }
        else
        {
            symbols = "Cannot connect to Camera!";
        }
        releaseCam();
    }
}

IplImage *img;
uchar *raw;
ImageScanner *scanner;
Image *zimg;
void BarcodeScanner::scanBarcode()
{
    if(capture == 0)
    {
        capture = cvCaptureFromCAM(CV_CAP_ANY);
        if(capture)
        {
            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 1600);
            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1600);
            scanner = new ImageScanner();


            timer->start(1000 / 60);
        }
        else
        {
            symbols = "Cannot connect to Camera!";
        }
    }
}

void BarcodeScanner::setLableScan(QLabel *scan)
{
    lblScan = scan;
}

void BarcodeScanner::setSymbols(QString blank)
{
    symbols = blank;
}

void BarcodeScanner::processFrame()
{
    src = cvQueryFrame(capture);
    if(lblScan)
    {
        img_show = QImage((unsigned char *)(src->imageData), src->width, src->height, QImage::Format_RGB888).rgbSwapped();
        lblScan->setPixmap(QPixmap::fromImage(img_show, Qt::AutoColor).scaled(lblScan->size()));
    }
    int n = scanSymbol(src);

    if(n)
    {
        timer->stop();
        cvReleaseCapture(&capture);
    }
}


int BarcodeScanner::scanSymbol(IplImage *src)
{
    img = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
    cvCvtColor(src, img, CV_RGB2GRAY);

    //Su dung thu vien Zbar de giai ma
    raw = (uchar *)img->imageData;
    int width = img->width;
    int height = img->height;
    zimg = new Image(width, height, "Y800", raw, width * height);


    scanner->set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);


    int n = scanner->scan(*zimg);

    if(n > 0)
    {
        for(Image::SymbolIterator symbol = zimg->symbol_begin(); symbol != zimg->symbol_end(); ++symbol)
        {
            symbols = QString::fromStdString(symbol->get_data());
            qDebug() << "barcode : " + symbols;
        }

    }
    else
    {
        //        ui->lineNik->setText("Cannot Detect Code!");
        //this->tampilkanHasil("CHIGAU_DETA");
    }

    //Giai phong tai nguyen
    cvReleaseImage(&img);
    zimg->set_data(NULL, 0);
    return n;
}

*/
