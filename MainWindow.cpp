#include <QFileDialog>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "ImageView.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    mImageView = new ImageView();

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

    // Rotate button
    QToolButton* rotateButton = new QToolButton();
    rotateButton->setText("Rotate");
    connect(rotateButton, SIGNAL(clicked()), this, SLOT(onRotateButtonClicked()));
    buttonLayout->addWidget(rotateButton);

    // GetText button
    QToolButton* getTextButton = new QToolButton();
    getTextButton->setText("get Text");
    connect(getTextButton, SIGNAL(clicked()), this, SLOT(onGetTextButtonClicked()));
    buttonLayout->addWidget(getTextButton);

    // Cut button
    QToolButton* cutButton = new QToolButton();
    cutButton->setText("Copy");
    connect(cutButton, SIGNAL(clicked()), this, SLOT(onCutButtonClicked()));
    buttonLayout->addWidget(cutButton);

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

MainWindow::~MainWindow()
{
}

void MainWindow::onLoadButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/m-swacha/Pulpit", tr("Image Files (*.png *.jpg *.bmp)"));
    mImageView->load(fileName);
}

void MainWindow::onZoomInButtonClicked()
{
    mImageView->scale(1.25, 1.25);
}

void MainWindow::onZoomOutButtonClicked()
{
    mImageView->scale(1/1.25, 1/1.25);
}

void MainWindow::onGetTextButtonClicked()
{
    mTextView->setPlainText(mImageView->getText());
}

void MainWindow::onRotateButtonClicked()
{
    mImageView->rotate();
}

void MainWindow::onCutButtonClicked()
{
    mImageView->copy();
}
