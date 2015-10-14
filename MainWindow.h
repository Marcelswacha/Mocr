#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPlainTextEdit>

#include "ImageView.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void onLoadButtonClicked();
    void onZoomInButtonClicked();
    void onZoomOutButtonClicked();
    void onGetTextButtonClicked();
    void onRotateButtonClicked();
    void onCutButtonClicked();

private:
    ImageView* mImageView;
    QPlainTextEdit* mTextView;
};

#endif // MAINWINDOW_H

