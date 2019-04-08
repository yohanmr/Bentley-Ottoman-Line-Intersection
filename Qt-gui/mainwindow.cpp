#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "FindIntersections.h"
#include <fstream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Enable panning (translation of axes)
    ui->plot->setInteraction(QCP::iRangeDrag, true);

    // Enable zoon on scroll
//    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");

    ui->plot->xAxis->setRange(0,100);
    ui->plot->yAxis->setRange(0,100);

    ui->plot->replot();

    // Add points on double click
    connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{

    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();

}

void MainWindow::drawLine()
{
    QCPItemLine *line = new QCPItemLine(ui->plot);
    line->start->setCoords( qv_x[qv_x.size() - 2], qv_y[qv_y.size() - 2]);
    line->end->setCoords( qv_x[qv_x.size() - 1], qv_y[qv_y.size() - 1]);
    ui->plot->addItem(line);
    plot();
}


void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()), ui->plot->yAxis->pixelToCoord(point.y()));
    plot();
    if(qv_x.size() > 0 && qv_x.size()%2 == 0){
        drawLine();
    }

}

void MainWindow::on_btn_runAlgo_clicked()
{
    vector<lineSegment> segmentVector;

    for(int i = 0; i < qv_x.size(); i = i+2){
        lineSegment l;
        l.startX = qv_x[i];
        l.startY = qv_y[i];
        l.endX = qv_x[i+1];
        l.endY = qv_y[i+1];
        segmentVector.push_back(l);
    }

    for(unsigned int i = 0; i < segmentVector.size(); i++)
    {
        cout << segmentVector[i].startX << " " << segmentVector[i].startY << " " << segmentVector[i].endX << " " << segmentVector[i].endY << endl;
    }

    ofstream myfile;
    myfile.open ("../Qt-gui/lines.txt");

    for(int i = 0; i < segmentVector.size(); i++)
    {
        myfile << segmentVector[i].startX << " " << segmentVector[i].startY << " " << segmentVector[i].endX << " " << segmentVector[i].endY << endl;
    }
    myfile.close();
    QApplication::quit();
}

void MainWindow::on_btn_clear_clicked()
{
    ui->plot->clearItems();
    clearData();
    plot();
}
