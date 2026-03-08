#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <random>

int main(int argc, char *argv[])
{
    size_t n, i;
    n = 100;
    std::vector<int> v(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    for(i = 0;i < n; i++)
        v[i] = distrib(gen);
    QApplication a(argc, argv);
    MainWindow w(n, v);
    w.show();
    return a.exec();
}
