#include "barcodescanner.h"
#include <algorithm>
#include <stdexcept>

using namespace zbar;
using namespace cv;
using namespace std;

CvCapture *capture;
BarcodeScanner *BarcodeScanner::s_instance;
BarcodeScanner *BarcodeScanner::instance()
{
    if(!s_instance)
    {
        s_instance = new BarcodeScanner();
    }
    return s_instance;
}

BarcodeScanner::BarcodeScanner()
{
    symbols = "";
    isCapture = false;
    timer = new QTimer(this);
    timer2 = new QTimer(this);
}


BarcodeScanner::~BarcodeScanner()
{
    cvReleaseCapture(&capture);
}

void BarcodeScanner::releaseCam()
{
    isCapture = true;
    if(timer->isActive()) {
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(processFrame()));
    }
    if(timer2->isActive()) {
        timer2->stop();
        disconnect(timer2, SIGNAL(timeout()), this, SLOT(processFrameForCapture()));
    }
    cvReleaseCapture(&capture);
}

void BarcodeScanner::setTimer(QTimer *timer)
{
    this->timer = timer;
}

//compare
bool compareContourArea(vector<Point> contour1, vector<Point> contour2){
    double i = fast_abs(contourArea(Mat(contour1)));
    double j = fast_abs(contourArea(Mat(contour2)));
    return (i < j);
}

QList<IplImage *> BarcodeScanner::getListBarcode (IplImage *image)
{
    QList<IplImage *> list ;
    if(image){
        Mat threshold_output,src,gradX,gradY,gradient,blured,kernel,closed,src_gray;
        src = cvarrToMat(image);
        //        src= imread("7.jpg");
        //    namedWindow( "Hull demo", CV_WINDOW_NORMAL);
        cvtColor(src,src_gray,COLOR_BGR2GRAY);
        Sobel(src_gray,gradX,CV_32F,1,0,-1);
        Sobel(src_gray,gradY,CV_32F,0,1,-1);

        subtract(gradX,gradY,gradient);
        convertScaleAbs(gradient,gradient);
        blur(gradient,blured,Size(9,9));

        threshold(blured,threshold_output,140,255,THRESH_BINARY);

        kernel = getStructuringElement(MORPH_RECT,Size(21,7));
        morphologyEx(threshold_output,closed,MORPH_CLOSE,kernel);

        erode(closed,closed,kernel,Point(-1,-1),4);
        dilate(closed,closed,kernel,Point(-1,-1),4);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours( closed, contours, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        sort(contours.begin(),contours.end(),compareContourArea);
        int size = contours.size();
        if(!contours.empty()){
            for (int i =0; i <  qty ;i ++) {
                if((size - i) > 0) {
                    Rect rect = boundingRect( Mat(contours[contours.size() -i - 1]) );
                    Mat crop = src(rect);
                    IplImage img = IplImage(crop);
                    list.append(cvCloneImage(&img));
                    //            rectangle( src, rect.tl(), rect.br(), Scalar( 0, 55, 255 ), +1, 4 );
                    cvRectangle(image,rect.tl(), rect.br(), Scalar( 0, 55, 255 ), +1, 4);
                }
            }
        }
        gradX.release();
        gradY.release();
        src_gray.release();
        gradient.release();
        blured.release();
        closed.release();
        kernel.release();
        //        cvReleaseMat(gradX);
        //        cvReleaseMat(gradY);
        //        cvReleaseMat(src_gray);
        //        cvReleaseMat(gradient);
        //        cvReleaseMat(blured);
        //        cvReleaseMat(closed);
        //        cvReleaseMat(kernel);
        if(lblScan)
        {
            img_show = QImage((unsigned char *)(image->imageData), image->width, image->height, QImage::Format_RGB888).rgbSwapped();
            lblScan->setPixmap(QPixmap::fromImage(img_show, Qt::AutoColor).scaled(lblScan->size()));
        }
    }
    return list;
}


bool BarcodeScanner::checkCam()
{
    if(capture == 0)
    {
        capture = cvCaptureFromCAM(CV_CAP_ANY);
        if(capture)
        {
            symbols = "Camera Allready!";
            cvReleaseCapture(&capture);
            return true;
        }
        else
        {
            symbols = "Cannot connect to Camera!";
            cvReleaseCapture(&capture);
            return false;
        }
    }
    return false;
}



void BarcodeScanner::scanBarcode()
{
    if(!capture)
    {
        capture = cvCreateCameraCapture(CV_CAP_ANY);
        if(capture)
        {
        //capture = cvCaptureFromCAM(CV_CAP_ANY);
            qDebug() << "start Cam";
//            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
//            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
            connect(timer, SIGNAL(timeout()), this, SLOT(processFrame()));
            timer->start(1000 / 30);
        }
        else
        {
            symbols = "Cannot connect to Camera!";
        }
    }
}

void BarcodeScanner::capturePicture(QString path, QLabel *label)
{
    isCapture = false;
    if(!capture)
    {
        qDebug() << "start Cam";
        capture = cvCaptureFromCAM(CV_CAP_ANY);
        if(capture)
        {
            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
            cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
            lblScan = label;
            this->imagePath = path;
            connect(timer2, SIGNAL(timeout()), SLOT(processFrameForCapture()));
            timer2->start(1000 / 30);
        }
        else
        {
            qDebug() << "Cannot connect to Camera!";
        }
    }
    else
    {
    }
}

void BarcodeScanner::movePicture(QString inputPath, QString outputPath)
{
    Mat picture = imread(inputPath.toStdString());
    imwrite(outputPath.toStdString(), picture);
}

void BarcodeScanner::processFrameForCapture()
{
    imSrc = cvQueryFrame(capture);

    if(isCapture)
    {
        releaseCam();
        Mat picture = cvarrToMat(imSrc);
        imwrite(imagePath.toStdString(), picture);
        isCapture = false;
    }
}

void BarcodeScanner::setLableScan(QLabel *scan)
{
    lblScan = scan;
}
void BarcodeScanner::setLableQty(QLabel *qty)
{
    lblQty = qty;
}

void BarcodeScanner::setSymbols(QString blank)
{
    symbols = blank;
}

void BarcodeScanner::processFrame()
{
    imSrc = cvQueryFrame(capture);
    if(lblScan && imSrc)
    {
        //        img_show = QImage((unsigned char *)(imSrc->imageData), imSrc->width, imSrc->height, QImage::Format_RGB888).rgbSwapped();
        //        lblScan->setPixmap(QPixmap::fromImage(img_show, Qt::AutoColor).scaled(lblScan->size()));
        QList<IplImage *> listImage = getListBarcode(imSrc);
        if(!listImage.isEmpty()){
            foreach (IplImage *img, listImage) {
                int n = scanSymbol(img);
                if(n)
                {
                    if(listBarcode.size() == qty) {
                        releaseCam();
                    }
                }
            }
        }

    }
}


int BarcodeScanner::scanSymbol(IplImage *src)
{
    IplImage *img = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
    cvCvtColor(src, img, CV_RGB2GRAY);

    //Su dung thu vien Zbar de giai ma

    ImageScanner * scanner = new ImageScanner();
    uchar *raw = (uchar *)img->imageData;
    int width = img->width;
    int height = img->height;
    Image *zimg = new Image(width, height, "Y800", raw, width * height);

    scanner->set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    int n = scanner->scan(*zimg);

    if(n > 0)
    {
        for(Image::SymbolIterator symbol = zimg->symbol_begin(); symbol != zimg->symbol_end(); ++symbol)
        {
            symbols = QString::fromStdString(symbol->get_data());
        }
        if( isValidBarcode(symbols) && !listBarcode.contains(symbols)) {
            listBarcode.append(symbols);
        }
        qDebug() << "barcode : " + symbols;

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
bool BarcodeScanner::isValidBarcode(QString barcode)
{
    int sum = 0;
    if(barcode.length()>1){
        for(int i = 0; i < barcode.length() - 1; i++)
        {
            if(i % 2 == 0)
            {
                sum += barcode.at(i).digitValue() * 1;
            }
            else
            {
                sum += barcode.at(i).digitValue() * 3;
            }
        }
        return ((((sum / 10) + 1) * 10 - sum) == barcode.at(barcode.length() - 1).digitValue() ? true : false); //"s= " + ((sum / 10) + 1) * 10 - sum;
    }
    return false;
}
