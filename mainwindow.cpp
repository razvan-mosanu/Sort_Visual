#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QPainter>
#include <QCoreApplication>
#include <QPushButton>
#include <random>
#include <QSlider>

MainWindow::MainWindow(size_t elemente, const std::vector<int> &v, QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->elemente = elemente;
    this->v = v;
    viteza = 5;
    btnBubble = new QPushButton("Bubble Sort", this);
    btnMergeSort = new QPushButton("Merge Sort", this);
    btnCompSort = new QPushButton("Comp Sort", this);
    btnQuickSortRand = new QPushButton("Quick Sort Random", this);
    btnHeapSort = new QPushButton("Heap Sort", this);
    btnAmestecare = new QPushButton("Amestecare", this);
    speed = new QSlider(this);
    btnBubble->setGeometry(0, 0, 120, 40);
    btnMergeSort->setGeometry(120, 0, 120, 40);
    btnCompSort->setGeometry(240, 0, 120, 40);
    btnQuickSortRand->setGeometry(360, 0, 120, 40);
    btnHeapSort->setGeometry(480, 0, 120, 40);
    btnAmestecare->setGeometry(600, 0, 120, 40);
    speed->setGeometry(720, 0, 120, 40);
    speed->setOrientation(Qt::Horizontal);
    speed->setRange(1, 100);
    speed->setValue(viteza);
    connect(speed, &QSlider::valueChanged, this, [this](int val) { viteza = val; });
    connect(btnBubble, &QPushButton::clicked, this, &MainWindow::startBubbleSort);
    connect(btnMergeSort, &QPushButton::clicked, this, &MainWindow::startMergeSort);
    connect(btnCompSort, &QPushButton::clicked, this, &MainWindow::Sortarea_prin_comparare);
    connect(btnQuickSortRand, &QPushButton::clicked, this, &MainWindow::startRandomQuickSort);
    connect(btnHeapSort, &QPushButton::clicked, this, &MainWindow::heapSort);
    connect(btnAmestecare, &QPushButton::clicked, this, &MainWindow::Amestecare);
    this->showMaximized();
}

void MainWindow::Amestecare()
{
    OprireBtn();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    update();
    QCoreApplication::processEvents();
    PornireBtn();
}

void MainWindow::Sortarea_prin_comparare()
{
    OprireBtn();
    size_t i, j;
    for(i=0; i<elemente-1; i++)
        for(j=i+1; j<elemente; j++)
            if(v[i] > v[j])
            {
                std::swap(v[i], v[j]);
                update();
                QCoreApplication::processEvents();
                QThread::msleep(viteza);
            }
    PornireBtn();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OprireBtn()
{
    btnBubble->setEnabled(false);
    btnMergeSort->setEnabled(false);
    btnCompSort->setEnabled(false);
    btnQuickSortRand->setEnabled(false);
    btnAmestecare->setEnabled(false);
}

void MainWindow::PornireBtn()
{
    btnBubble->setEnabled(true);
    btnMergeSort->setEnabled(true);
    btnCompSort->setEnabled(true);
    btnQuickSortRand->setEnabled(true);
    btnAmestecare->setEnabled(true);
}

void MainWindow::startBubbleSort()
{
    OprireBtn();
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
                QThread::msleep(viteza);
            }
        pas++;
    }
    PornireBtn();
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
        QThread::msleep(viteza);
        k++;
    }
    while (i < n)
    {
        v[k++] = aux1[i++];
        update();
        QCoreApplication::processEvents();
        QThread::msleep(viteza);
    }
    while (j < l)
    {
        v[k++] = aux2[j++];
        update();
        QCoreApplication::processEvents();
        QThread::msleep(viteza);
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
    OprireBtn();
    MergeSort(0, elemente-1);
    PornireBtn();
}


void MainWindow::pivot_random(int st, int dr)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(st, dr);
    int idx = dist(gen);
    std::swap(v[idx], v[dr]);
    update();
    QCoreApplication::processEvents();
    QThread::msleep(viteza);
}

int MainWindow::Aranjare(int st, int dr)
{
    pivot_random(st, dr);
    int pivot = v[dr];
    int j, i = st;
    for(j=st; j<dr; j++)
        if(v[j] <= pivot)
        {
            std::swap(v[i], v[j]);
            update();
            QCoreApplication::processEvents();
            QThread::msleep(viteza);
            i++;
        }
    std::swap(v[i], v[dr]);
    update();
    QCoreApplication::processEvents();
    QThread::msleep(viteza);
    return i;
}

void MainWindow::QuickSort(int st, int dr)
{
    if(st >= dr) return;
    int pivotIndex = Aranjare(st, dr);
    QuickSort(st, pivotIndex - 1);
    QuickSort(pivotIndex + 1, dr);
}

void MainWindow::startRandomQuickSort()
{
    if(elemente == 0) return;
    OprireBtn();
    QuickSort(0, (int)elemente - 1);
    PornireBtn();
}


void MainWindow::make_heap(int n, int i)
{

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && v[l] > v[largest]) largest = l;
    if (r < n && v[r] > v[largest]) largest = r;
    if (largest != i)
    {
        std::swap(v[i], v[largest]);
        update();
        QCoreApplication::processEvents();
        QThread::msleep(viteza);
        make_heap(n, largest);
    }
}

void MainWindow::heapSort()
{
    if(elemente == 0) return;
    OprireBtn();
    int i, n;
    n = elemente;
    for (i = n / 2 - 1; i >= 0; i--)
        make_heap(n, i);
    for (i = n - 1; i > 0; i--)
    {

        std::swap(v[0], v[i]);
        update();
        QCoreApplication::processEvents();
        QThread::msleep(viteza);
        make_heap(i, 0);
    }
    PornireBtn();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter dreptunghi(this);
    QPen pen;
    pen.setWidth(0);
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
