#ifndef HEAVYMENUWIDGET_H
#define HEAVYMENUWIDGET_H

#include <QWidget>
#include <fstream>
#include <string>
#include "mcmfmanager.h"
#include <QFileDialog>
#include "graphgenerator.h"
#include "mcmfmanager.h"
#include <QTimer>
#include <random>
#include <cmath>
#include <QDebug>

using namespace std;

namespace Ui {
class HeavyMenuWidget;
}

class HeavyMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeavyMenuWidget(QWidget *parent = nullptr);
    ~HeavyMenuWidget();
    long long calc_func();
    void updateF(ll val);
    void setBestF(ll val);
    void simulatedAnnealing();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::HeavyMenuWidget *ui;
    vector<vector<int>> graph;
    vector<vector<ll>> q, b;
    vector<ll> cost;
    ll alpha, beta;
    GraphGenerator* graphGenerator;
    int n, m, tn, f, cnt = 0;
    bool sa_flag, move_state;
    random_device rd;
    mt19937 gen;
    QTimer* timer;
signals:
    void initGraphSignal(int n);
    void setGraphSignal(vector<vector<int>> graph);
};

#endif // HEAVYMENUWIDGET_H
