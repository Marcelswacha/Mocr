#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsRectItem>

class ImageView: public QGraphicsView
{
public:
    ImageView(QGraphicsPixmapItem* image, QWidget* parent = NULL) : QGraphicsView(parent)
    {
        mBaseImage = image;
        isFirstAssigned = false;
        rect = NULL;
        topLeft = QPointF(0,0);
        bottomRight = QPointF(0,0);
    }

    void copy()
    {
        if (rect != NULL) {
            QPixmap copy = mBaseImage->pixmap().copy(QRectF(topLeft, bottomRight).toAlignedRect());
            mBaseImage->setPixmap(copy);
            update();
        }
    }

    void mouseMoveEvent( QMouseEvent* event )
    {
        QPointF pos =  mapToScene( event->pos() );
        qDebug() << "X: " << pos.x() << " Y: " << pos.y();


        if (!isFirstAssigned) {
            topLeft = pos;
            isFirstAssigned = true;
        } else {
            bottomRight = pos;
        }

        if (rect != NULL) {
            this->scene()->removeItem(rect);
        }

        rect = this->scene()->addRect(QRectF(topLeft, bottomRight));
        update();
    }

    void mousePressEvent(QMouseEvent* event) {
        QPointF pos =  mapToScene(event->pos());
        if (event->button() == Qt::LeftButton)
            topLeft = pos;

        if (event->button() == Qt::RightButton) {
            topLeft = QPointF(0,0);
            bottomRight = QPointF(0,0);
            if (rect != NULL) {
                this->scene()->removeItem(rect);
            }
        }
    }

    void mouseReleasevent(QMouseEvent* event) {
        QPointF pos =  mapToScene(event->pos());
        if (event->button() == Qt::LeftButton)
            bottomRight = pos;
    }


private:
    bool isFirstAssigned;
    QPointF topLeft;
    QPointF bottomRight;
    QGraphicsItem * rect;
    QGraphicsPixmapItem* mBaseImage;

};

#endif // IMAGEVIEW_H
