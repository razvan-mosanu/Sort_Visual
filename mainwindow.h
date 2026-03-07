#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <vector>

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
    void MergeSort(size_t st, size_t dr);
    void Interclasare(size_t st, size_t mij, size_t dr);
public:
    MainWindow(size_t elemente, const std::vector<int> &v, QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void startBubbleSort();
    void startMergeSort();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
