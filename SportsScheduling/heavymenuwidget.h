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
#include <QTime>

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

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::HeavyMenuWidget *ui;
    vector<vector<int>> graph;
    vector<vector<ll>> q, b;
    vector<ll> cost;
    ll alpha, beta;
    GraphGenerator* graphGenerator;
    int n, m, tn, cnt = 0;
    ll f = 0;
    bool sa_flag, move_1, move_2, drawing;
    int currentMoveType = 0;
    random_device rd;
    mt19937 gen;
    QTimer* timer;
    QTime tick;
signals:
    void initGraphSignal(int n);
    void setGraphSignal(vector<vector<int>> graph);
};

#endif // HEAVYMENUWIDGET_H
