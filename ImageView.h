#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <leptonica/allheaders.h>

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMouseEvent>

class ImageView: public QGraphicsView
{
public:
    ImageView(QWidget* parent = NULL);

    void load(const QString& path);
    void copy();
    void rotate();
    QString getText();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    PIX* qImage2PIX(const QImage& qImage);

    bool isFirstAssigned;

    QPointF mTopLeft;
    QPointF mBottomRight;
    QGraphicsItem * mRectangle;
    QGraphicsPixmapItem* mBaseImage;
};

#endif // IMAGEVIEW_H
