#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QStyle>
#include <QGraphicsScene>


#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QImage image("/home/m-swacha/Pulpit/q.bmp");
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


    layout->addLayout(buttonLayout);

    setLayout(layout);
    setWindowTitle("Mocr");
    resize(800, 600);
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
