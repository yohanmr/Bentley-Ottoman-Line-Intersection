#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPoint(double x, double y);
    void clearData();
    void plot();
    void drawLine();

private slots:

    void clickedGraph(QMouseEvent *event);

    void on_btn_runAlgo_clicked();

    void on_btn_clear_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;
};

#endif // MAINWINDOW_H
