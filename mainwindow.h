#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include <QPushButton>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    size_t elemente;
    std::vector<int> v;
    QPushButton *btnBubble;
    QPushButton *btnMergeSort;
    QPushButton *btnCompSort;
    QPushButton *btnQuickSortRand;
    QPushButton *btnHeapSort;
    QPushButton *btnAmestecare;
    QSlider *speed;
    QPushButton *stop;
    int viteza = 5;
    bool oprit = false;
    int activ1 = -1;
    int activ2 = -1;
    int verde = -1;
    void MergeSort(size_t st, size_t dr);
    void Interclasare(size_t st, size_t mij, size_t dr);
    int Aranjare(int st, int dr);
    void QuickSort(int st, int dr);
    void pivot_random(int st, int dr);
    void Amestecare();
    void OprireBtn();
    void PornireBtn();
    void make_heap(int n, int i);
    void OprireAnimatie();
    void Verde();
public:
    MainWindow(size_t elemente, const std::vector<int> &v, QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void startBubbleSort();
    void startMergeSort();
    void Sortarea_prin_comparare();
    void startRandomQuickSort();
    void heapSort();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
