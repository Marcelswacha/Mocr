#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QStyle>
#include <QGraphicsScene>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


#include "MainWindow.h"

const char* const IM_PATH = "/home/m-swacha/Pulpit/sample.jpg";
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QImage image(IM_PATH);
    mBaseImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(mBaseImage);

    mImageView = new QGraphicsView(scene);
    //mImageView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);

    layout->addWidget(mImageView);

    // Button layout
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    // Load button
    QToolButton* loadButton = new QToolButton();
    loadButton->setText("Load image");
    connect(loadButton, SIGNAL(clicked()), this, SLOT(onLoadButtonClicked()));
    buttonLayout->addWidget(loadButton);

    // Zoom in button
    QToolButton* zoomInButton = new QToolButton();
    zoomInButton->setText("ZoomIn");
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(onZoomInButtonClicked()));
    buttonLayout->addWidget(zoomInButton);

    // Zoom out button
    QToolButton* zoomOutButton = new QToolButton();
    zoomOutButton->setText("ZoomOut");
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(onZoomOutButtonClicked()));
    buttonLayout->addWidget(zoomOutButton);

    // GetText button
    QToolButton* getTextButton = new QToolButton();
    getTextButton->setText("get Text");
    connect(getTextButton, SIGNAL(clicked()), this, SLOT(onGetTextButtonClicked()));
    buttonLayout->addWidget(getTextButton);

    layout->addLayout(buttonLayout);

    // Text area
    mTextView = new QPlainTextEdit(this);
    mTextView->setReadOnly(false);

    layout->addWidget(mTextView);



    setLayout(layout);
    setWindowTitle("Mocr");
    resize(1280, 1024);
    move(QPoint(0,0));
    show();
}

MainWindow::~MainWindow() {

}

void MainWindow::onLoadButtonClicked()
{

}

void MainWindow::onZoomInButtonClicked()
{
    mImageView->scale(1.25, 1.25);
}

void MainWindow::onZoomOutButtonClicked()
{
    mImageView->scale(0.8, 0.8);
}


PIX* qImage2PIX(const QImage& qImage) {
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
void MainWindow::onGetTextButtonClicked()
{
    // Get Image
    QImage image = mBaseImage->pixmap().toImage();
    PIX* pix = qImage2PIX(image);

    // Pass data to tesseract
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "pol", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_AUTO);
    tess.SetImage(pix);

    // Get text
    char* out = tess.GetUTF8Text();
    mTextView->setPlainText(out);

}
