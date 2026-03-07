#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QPainter>
#include <QCoreApplication>
#include <QPushButton>

MainWindow::MainWindow(size_t elemente, const std::vector<int> &v, QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->elemente = elemente;
    this->v = v;
    QPushButton *btnBubble = new QPushButton("Start Bubble Sort", this);
    QPushButton *btnMergeSort = new QPushButton("Start Merge Sort", this);
    btnBubble->setGeometry(0, 0, 120, 40);
    btnMergeSort->setGeometry(120, 0, 120, 40);
    connect(btnBubble, &QPushButton::clicked, this, &MainWindow::startBubbleSort);
    connect(btnMergeSort, &QPushButton::clicked, this, &MainWindow::startMergeSort);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startBubbleSort()
{
    bool sortat = false;
    size_t pas = 0;
    while(sortat == false)
    {
        sortat = true;
        for(size_t j = 0; j < elemente - pas  - 1; j++)
            if (v[j] > v[j+1])
            {
                sortat = false;
                std::swap(v[j], v[j+1]);
                update();
                QCoreApplication::processEvents();
                QThread::msleep(20);
            }
        pas++;
    }
}

void MainWindow::Interclasare(size_t st, size_t mij, size_t dr)
{
    int i, j, n, l;
    n = mij - st + 1;
    l = dr - mij;
    std::vector<int> aux1(n), aux2(l);
    for (i = 0; i < n; i++)
        aux1[i] = v[st + i];
    for (j = 0; j < l; j++)
        aux2[j] = v[mij + 1 + j];
    i = j = 0;
    int k = st;
    while (i < n && j < l)
    {
        if(aux1[i] <= aux2[j]) v[k] = aux1[i++];
        else v[k] = aux2[j++];
        update();
        QCoreApplication::processEvents();
        QThread::msleep(20);
        k++;
    }
    while (i < n)
    {
        v[k++] = aux1[i++];
        update();
        QCoreApplication::processEvents();
        QThread::msleep(20);
    }
    while (j < l)
    {
        v[k++] = aux2[j++];
        update();
        QCoreApplication::processEvents();
        QThread::msleep(20);
    }
}

void MainWindow::MergeSort(size_t st, size_t dr)
{
    if(st >= dr) return;
    size_t mij = (st + dr) / 2;
    MergeSort(st, mij);
    MergeSort(mij + 1, dr);
    Interclasare(st, mij, dr);
}

void MainWindow::startMergeSort()
{
    if(elemente == 0) return;
    MergeSort(0, elemente-1);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter dreptunghi(this);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    dreptunghi.setBrush(Qt::gray);
    dreptunghi.setPen(pen);
    if(elemente == 0) return;
    int maxim = *std::max_element(v.begin(), v.end());
    int w = this->width();
    int h = this->height();
    double latime_coloana = (double)w / elemente;
    size_t i;
    for(size_t i = 0; i < elemente; i++)
    {
        double inaltime_coloana = ((double)v[i] / maxim) * (h - 50);
        double x = i * latime_coloana;
        double y = h - inaltime_coloana;
        dreptunghi.drawRect(QRectF(x, y, latime_coloana, inaltime_coloana));
    }
}
