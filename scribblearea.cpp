#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{

    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::blue;
    mEnabled = false;
    canvasheight = 500;
    canvaswidth = 500;
}
//load given image and resize image to be at least as large as the widget in both directions using the private resizeImage() function and we set the image member
//variable to be the loaded image.
bool ScribbleArea::openImage(const QString &filename){
    QImage loadedImage;
    if(!loadedImage.load(filename))
        //qDebug()<<"failed to load this filename";
        //qDebug()<<filename;
        return false;
    //qDebug()<<"success!";
    QSize newSize = loadedImage.size().expandedTo(size());
    qDebug()<<"The newSize inside openImage is:";
    qDebug()<<newSize;
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::openOverlayImage(const QString &filename, const int num){
    QImage loadedImage;
    if(!loadedImage.load(filename))
        //qDebug()<<"failed to load this filename";
        //qDebug()<<filename;
        return false;
    //qDebug()<<"success!";
    QSize newSize = loadedImage.size().expandedTo(size());
    qDebug()<<"The newSize inside openOverlayImage is:";
    qDebug()<<newSize;

    resizeOverlayImage(&loadedImage, newSize, num);
    image = loadedImage;
    modified = false;
    update();
    return true;
}


bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat){
    //cut the image into 9 pieces. save each image into a folder
    QImage originalimage = image;
    QImage firstbox;
    QImage secondbox;
    QImage thirdbox;
    QImage fourthbox;
    QImage fifthbox;
    QImage sixthbox;
    QImage seventhbox;
    QImage eigthbox;
    QImage ninthbox;

    resizeImage(&originalimage, size());

    QStringList cropped_fileName_and_extension=fileName.split(".",QString::SkipEmptyParts);
    QString cropped_fileName = cropped_fileName_and_extension.at(0);
    QString cropped_extension = cropped_fileName_and_extension.at(1);

    //QRect::QRect(int x, int y, int width, int height)

    firstbox = originalimage.copy( 0, 0, canvaswidth/3, canvasheight/3);
    if(firstbox.save(cropped_fileName + "1." + cropped_extension , fileFormat)){

        secondbox = originalimage.copy( canvaswidth/3, 0, canvaswidth/3, canvasheight/3);
        secondbox.save(cropped_fileName + "2." + cropped_extension , fileFormat);

        thirdbox = originalimage.copy( canvaswidth/3*2, 0, canvaswidth/3, canvasheight/3);
        thirdbox.save(cropped_fileName + "3." + cropped_extension , fileFormat);

        fourthbox = originalimage.copy( 0, canvasheight/3, canvaswidth/3, canvasheight/3);
        fourthbox.save(cropped_fileName + "4." + cropped_extension , fileFormat);

        fifthbox = originalimage.copy( canvaswidth/3, canvasheight/3, canvaswidth/3, canvasheight/3);
        fifthbox.save(cropped_fileName + "5." + cropped_extension , fileFormat);

        sixthbox = originalimage.copy( canvaswidth/3*2, canvasheight/3, canvaswidth/3, canvasheight/3);
        sixthbox.save(cropped_fileName + "6." + cropped_extension , fileFormat);

        seventhbox = originalimage.copy( 0, canvasheight/3*2, canvaswidth/3, canvasheight/3);
        seventhbox.save(cropped_fileName + "7." + cropped_extension , fileFormat);

        eigthbox= originalimage.copy( canvaswidth/3, canvasheight/3*2, canvaswidth/3, canvasheight/3);
        eigthbox.save(cropped_fileName + "8." + cropped_extension , fileFormat);

        ninthbox = originalimage.copy( canvaswidth/3*2, canvasheight/3*2, canvaswidth/3, canvasheight/3);
        ninthbox.save(cropped_fileName + "9." + cropped_extension , fileFormat);

        modified = false;

        return true;
    }
    return false;
}

//create brand new qimage, fill with white, draw old image on it using QPainter
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize){
    //if(image->size() == newSize)
    //    return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    //qDebug()<<"I'm drawing new image on top";
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}



void ScribbleArea::resizeOverlayImage(QImage *image, const QSize &newSize, const int num){ //image is one square
    int num_minus_one = num - 1;
    int row = (num_minus_one / 3);
    qDebug()<<"This is the row";
    qDebug()<<row;
    int column = (num_minus_one % 3);
    qDebug()<<"This is the column";
    qDebug()<<column;


    if(image->size() == newSize)
        return;
    qDebug()<<newSize;
    QImage newImage(newSize, QImage::Format_RGB32);
    //newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint((canvasheight/3*column), (canvaswidth/3)*row), *image);
    //qDebug()<<"I'm drawing new image on top";
    *image = newImage;
}
void ScribbleArea::setPenColor(const QColor &newColor){
    myPenColor= newColor;
}

void ScribbleArea::setPenWidth(int newWidth){
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage(){
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}



void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

//simply create QPainter for the scribble area and draw the image
void ScribbleArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
    //qDebug()<<image.width();
    //row1
    painter.drawLine(0, canvasheight/3, canvaswidth,canvasheight/3);
    //row2
    painter.drawLine(0, (canvasheight/3)*2, canvaswidth, (canvasheight/3)*2);
    //column1
    painter.drawLine(canvaswidth/3, 0, canvaswidth/3, canvasheight);
    //column2
    painter.drawLine(canvaswidth/3*2, 0, canvaswidth/3*2, canvasheight);


    event->accept();


}


void ScribbleArea::mousePressEvent(QMouseEvent *event){
//    if(event->button() == Qt::LeftButton){
//        lastPoint = event->pos();
//        scribbling = true;
//    }
    mEnabled = true;
    mBegin = event->pos();
    event->accept();
}

void ScribbleArea:: mouseMoveEvent(QMouseEvent *event){
//    if((event->button() & Qt::LeftButton) && scribbling){
//        drawLineTo(event->pos());
//    }
    if(!mEnabled){
        event->accept();
        return;
    }

    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    mEnd = event->pos();
    painter.drawLine(mBegin, mEnd);
    mBegin = mEnd;
    modified = true;
    update();
    event->accept();
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event){
//    if(event->button() == Qt::LeftButton && scribbling){
//        drawLineTo(event->pos());
//        scribbling = false;
//    }
    mEnabled = false;
    event->accept();
}


void ScribbleArea::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPainterPath path;
    path.moveTo(lastPoint);
    modified = true;

    int rad= (myPenWidth/2)+2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
    path.lineTo(lastPoint);
    painter.drawPath(path);
}

//construct high res qprinter object for required output format, using qprintoutdialog to ask user to specify a page size and indicate how the output
//should be formatted on the page
//if accepted, we perform the task to print the paint device. printing an image to file in this way is simply a matter of painting onto qprinter. scale it first
//void ScribbleArea::print()
//{
//#if QT_CONFIG(printdialog)
//    QPrinter printer(QPrinter::HighResolution);

//    QPrintDialog printDialog(&printer, this);
//    if (printDialog.exec() == QDialog::Accepted) {
//        QPainter painter(&printer);
//        QRect rect = painter.viewport();
//        QSize size = image.size();
//        size.scale(rect.size(), Qt::KeepAspectRatio);
//        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
//        painter.setWindow(image.rect());
//        painter.drawImage(0, 0, image);
//    }
//#endif // QT_CONFIG(printdialog)
//}
