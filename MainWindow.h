#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

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

private:
    QGraphicsView* mImageView;
    QGraphicsPixmapItem* mBaseImage;
};

#endif // MAINWINDOW_H

