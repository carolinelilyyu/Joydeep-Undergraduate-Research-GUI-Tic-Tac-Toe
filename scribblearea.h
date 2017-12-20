#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H
#include <QtCore>
#include <QtDebug>
#include <QSettings>
#include <QDialog>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QString>
#include <QCloseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QInputDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QByteArray>
#include <QImageWriter>
#include <QResizeEvent>
#include <QRect>
#include <QPoint>
#include <QPen>
#include <QSize>
#include <QPainterPath>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent=0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    bool openOverlayImage(const QString &fileName, const int num);
    bool isModified() const{return modified;}
    QColor penColor() const{return myPenColor;}
    int penWidth() const {return myPenWidth;}
    int convert_num_to_array(const int num);


public slots:
    void clearImage();
    //void print();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


private:
    void drawLineTo(const QPoint &endpoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void resizeOverlayImage(QImage *image, const QSize &newSize, const int num);

    //modified is true if there are unsaved changes displayed in the scribble area
    bool modified;
    // scribbling is true while the user is pressing left mouse button in scribble area
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    //image stores the image drawn by the user
    QImage image;
    //lastpoint holds the position of the cursor at the last mouse press or mouse move event
    QPoint lastPoint;
    QPoint mBegin;  //initial
    QPoint mEnd;    //final
    bool mEnabled; //active
    int canvasheight;
    int canvaswidth;

};
#endif // SCRIBBLEAREA_H
