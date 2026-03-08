#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <fstream>
#include <random>

int main(int argc, char *argv[])
{
    std::ifstream fin("D:/QT_STUDENT/Sort_Visual/input.in");
    size_t n, i;
    n = 100;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    std::vector<int> v(n);
    for(i = 0;i < n; i++)
        v[i] = distrib(gen);
    std::ofstream fout("D:/QT_STUDENT/Sort_Visual/output.out");
    for(i = 0; i < n; i++)
        fout << v[i] << " ";
    fin.close();
    fout.close();
    QApplication a(argc, argv);
    MainWindow w(n, v);
    w.show();
    return a.exec();
}
