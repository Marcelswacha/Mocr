#include "ImageView.h"

#include <tesseract/baseapi.h>

const char* const IM_PATH = "/home/m-swacha/Pulpit/sample.jpg";

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent),
      isFirstAssigned(false),
      mTopLeft(QPointF(0,0)),
      mBottomRight(QPointF(0,0)),
      mRectangle(nullptr)
{
    QPixmap image(IM_PATH);
    mBaseImage = new QGraphicsPixmapItem(image);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(mBaseImage);
    setScene(scene);
}

void ImageView::load(const QString &path)
{

}

void ImageView::copy()
{
    if (mRectangle != NULL) {
        QPixmap copy = mBaseImage->pixmap().copy(QRectF(mTopLeft, mBottomRight).toAlignedRect());
        mBaseImage->setPixmap(copy);
        update();
    }
}

void ImageView::rotate()
{
    QPixmap basePix = mBaseImage->pixmap();
    QTransform transform;
    QTransform trans = transform.rotate(90);
    QPixmap *transPixmap = new QPixmap(basePix.transformed(trans));

    mBaseImage->setPixmap(*transPixmap);

    update();
}

QString ImageView::getText()
{
    QImage image = mBaseImage->pixmap().toImage();
    PIX* pix = qImage2PIX(image);

    // Pass data to tesseract
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "pol", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_AUTO);
    tess.SetImage(pix);

    // Get text
    char* out = tess.GetUTF8Text();
    return QString(out);
}


void ImageView::mouseMoveEvent( QMouseEvent* event )
{
    QPointF pos =  mapToScene(event->pos());

    if (!isFirstAssigned) {
        mTopLeft = pos;
        isFirstAssigned = true;
    } else {
        mBottomRight = pos;
    }

    if (mRectangle != nullptr) {
        this->scene()->removeItem(mRectangle);
    }

    mRectangle = this->scene()->addRect(QRectF(mTopLeft, mBottomRight));
    update();
}

void ImageView::mousePressEvent(QMouseEvent* event)
{
    QPointF pos =  mapToScene(event->pos());

    if (event->button() == Qt::LeftButton)
        mTopLeft = pos;

    if (event->button() == Qt::RightButton) {
        mTopLeft = QPointF(0,0);
        mBottomRight = QPointF(0,0);
        if (mRectangle != nullptr) {
            this->scene()->removeItem(mRectangle);
        }
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent* event) {
    QPointF pos =  mapToScene(event->pos());
    if (event->button() == Qt::LeftButton) {
        mBottomRight = pos;
        isFirstAssigned = false;
    }
}

PIX* ImageView::qImage2PIX(const QImage& qImage) {
  PIX * pixs;

  QImage myImage = qImage.rgbSwapped();
  int width = myImage.width();
  int height = myImage.height();
  int depth = myImage.depth();
  int wpl = myImage.bytesPerLine() / 4;

  pixs = pixCreate(width, height, depth);
  pixSetWpl(pixs, wpl);
  pixSetColormap(pixs, NULL);
  l_uint32 *datas = pixs->data;

  for (int y = 0; y < height; y++) {
    l_uint32 *lines = datas + y * wpl;
    QByteArray a((const char*)myImage.scanLine(y), myImage.bytesPerLine());
    for (int j = 0; j < a.size(); j++) {
      *((l_uint8 *)lines + j) = a[j];
    }
  }

  const qreal toDPM = 1.0 / 0.0254;
  int resolutionX = myImage.dotsPerMeterX() / toDPM;
  int resolutionY = myImage.dotsPerMeterY() / toDPM;

  if (resolutionX < 300) resolutionX = 300;
  if (resolutionY < 300) resolutionY = 300;
  pixSetResolution(pixs, resolutionX, resolutionY);

  return pixEndianByteSwapNew(pixs);
}
