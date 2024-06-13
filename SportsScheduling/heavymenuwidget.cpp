#include "heavymenuwidget.h"
#include "ui_heavymenuwidget.h"

HeavyMenuWidget::HeavyMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeavyMenuWidget)
{
    ui->setupUi(this);
    graphGenerator = new GraphGenerator();
    alpha = beta = f = cnt = 0;
    sa_flag = move_1 = move_2 = drawing = false;
    currentMoveType = 0;
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    gen = mt19937(rd());
    simulatedAnnealing();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HeavyMenuWidget::simulatedAnnealing);
    timer->start(10);
    tick = QTime::currentTime();
}

HeavyMenuWidget::~HeavyMenuWidget()
{
    delete ui;
}

void HeavyMenuWidget::on_pushButton_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбрать файл", "/home",
                       "All files (*.*);; Text (*.txt) ;;");
    ui->lineIn->setText(path);

    string inPath = ui->lineIn->text().toStdString();
    ifstream fin(inPath);
    fin >> n >> m;
    fin >> alpha >> beta;
    tn = n & 1 ? n : n - 1;
    q.resize(n, vector<ll>(m));
    b.resize(tn, vector<ll>(m));
    cost.resize(m);
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) fin >> q[i][j];
    for(int i = 0; i < tn; i++) for(int j = 0; j < m; j++) fin >> b[i][j];
    for(int i = 0; i < m; i++) fin >> cost[i];

    graph = vector<vector<int>>(n, vector<int>(n));
    //if (!drawing) qDebug() << "lol";
    if (drawing) emit initGraphSignal(n);

    setBestF(0);

}

long long HeavyMenuWidget::calc_func()
{
    auto get_match_ind = [&](int i, int j) {
        if (i > j) swap(i, j);
        return (2 * n - i - 1) * i / 2 + j - i - 1;
    };
    auto get_st_ind = [&](int s, int t) {
        return t * m + s;
    };
    auto get_c = [&](int i, int j, int s) {
        return alpha * (-q[i][s] - q[j][s]) + beta * cost[s];
    };
    int s = 2 + n * (n - 1) / 2 + m * tn;
    MCMFManager mcmf(s, 1e17);
    for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
        mcmf.add_edge(0, 1 + get_match_ind(i, j), 1, 0);
        for(int k = 0; k < m; k++) mcmf.add_edge(1 + get_match_ind(i, j), 1 + n * (n - 1) / 2 + get_st_ind(k, graph[i][j] - 1), 1, get_c(i, j, k));
    }
    for(int i = 0; i < m; i++) for(int j = 0; j < tn; j++) mcmf.add_edge(1 + n * (n - 1) / 2 + get_st_ind(i, j), s - 1, b[j][i], 0);
    return mcmf.calc(0, s - 1);
}

void HeavyMenuWidget::updateF(ll val)
{
    ui->lineCurrent->setText(QString::fromStdString(to_string(val)));
    ll best = stoi(ui->lineBest->text().toStdString());
    best = max(best, val);
    ui->lineBest->setText(QString::fromStdString(to_string(best)));
}

void HeavyMenuWidget::setBestF(ll val)
{
    ui->lineCurrent->setText(QString::fromStdString(to_string(val)));
    ui->lineBest->setText(QString::fromStdString(to_string(val)));
}

void HeavyMenuWidget::simulatedAnnealing()
{
    if (!sa_flag) {
        return;
    }
    if (-f == 50404381LL) {
        auto get_ms = [&](QTime tm) {
            return (ll)tm.minute() * 60 * 1000 + (ll)tm.second() * 1000 + tm.msec();
        };
        qDebug() << get_ms(QTime::currentTime()) - get_ms(tick);
    }
    long double temp = stold(ui->lineTemp->text().toStdString());
    long double cooling = stold(ui->lineCool->text().toStdString());
    temp *= cooling;
    cnt++;
    ui->lineTemp->setText(QString::fromStdString(to_string(temp)));
    if (currentMoveType == 0) {
        currentMoveType ^= 1;
        if (!move_1) {return;}
        currentMoveType ^= 1;
        int i = gen() % n, j;
        while ((j = gen() % n) == i) continue;
        for(int mid = 0; mid < n; mid++) {
            if (mid == i || mid == j) continue;
            swap(graph[min(i, mid)][max(i, mid)], graph[min(j, mid)][max(j, mid)]);
        }
        ll nf = calc_func();
        if (nf < f) {
            updateF(-nf), f = nf;
            if (drawing) emit setGraphSignal(graph);
            return;
        }
        if (temp != 0 && (long double)gen() / gen.max() < exp((f - nf) / temp)) {
            updateF(-nf), f = nf;
            if (drawing) emit setGraphSignal(graph);
            return;
        }
        for(int mid = 0; mid < n; mid++) {
            if (mid == i || mid == j) continue;
            swap(graph[min(i, mid)][max(i, mid)], graph[min(j, mid)][max(j, mid)]);
        }
    }
    else {
        currentMoveType ^= 1;
        if (!move_2) {return;}
        currentMoveType ^= 1;
        int ti = gen() % tn, tj;
        while ((tj = gen() % tn) == ti) continue;
        ti += 1, tj += 1;
        vector<vector<int>> adj(n);
        for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++)
            if (graph[i][j] == ti || graph[i][j] == tj) adj[i].push_back(j), adj[j].push_back(i);
        vector<vector<int>> cycles;
        vector<bool> used(n);
        for(int i = 0; i < n; i++) {
            if (used[i]) continue;
            cycles.push_back(vector<int>());
            function<void(int, int)> dfs = [&](int v, int from) {
                used[v] = true;
                for(auto& to: adj[v]) {
                    if (to == from) continue;
                    if (!used[to]) dfs(to, v);
                    break;
                }
                cycles.back().push_back(v);
            };
            dfs(i, -1);
        }
        int cycles_ind = gen() % sz(cycles);
        for(int i = 0; i < cycles[cycles_ind].size(); i++) {
            int v1 = cycles[cycles_ind][i], v2 = cycles[cycles_ind][(i + 1) % cycles[cycles_ind].size()];
            if (graph[min(v1, v2)][max(v1, v2)] == ti) graph[min(v1, v2)][max(v1, v2)] = tj;
            else graph[min(v1, v2)][max(v1, v2)] = ti;
        }
        ll nf = calc_func();
        if (nf < f) {
            updateF(-nf), f = nf;
            if (drawing) emit setGraphSignal(graph);
            return;
        }
        if (temp != 0 && (long double)gen() / gen.max() < exp((f - nf) / temp)) {
            updateF(-nf), f = nf;
            if (drawing) emit setGraphSignal(graph);
            return;
        }
        for(int i = 0; i < cycles[cycles_ind].size(); i++) {
            int v1 = cycles[cycles_ind][i], v2 = cycles[cycles_ind][(i + 1) % cycles[cycles_ind].size()];
            if (graph[min(v1, v2)][max(v1, v2)] == ti) graph[min(v1, v2)][max(v1, v2)] = tj;
            else graph[min(v1, v2)][max(v1, v2)] = ti;
        }
    }
}


void HeavyMenuWidget::on_pushButton_3_clicked()
{
    graph = graphGenerator->buildGraph(n);
    if (drawing) emit setGraphSignal(graph);
    f = calc_func();
    updateF(-f);
}


void HeavyMenuWidget::on_pushButton_2_clicked()
{
    if (!sa_flag) {
        ui->pushButton_2->setText("Пауза");
        tick = QTime::currentTime();
    }
    else {
        ui->pushButton_2->setText("Запуск");
        auto get_ms = [&](QTime tm) {
            return (ll)tm.minute() * 60 * 1000 + (ll)tm.second() * 1000 + tm.msec();
        };
        qDebug() << get_ms(QTime::currentTime()) - get_ms(tick);
    }
    sa_flag = !sa_flag;
}

void HeavyMenuWidget::on_checkBox_stateChanged(int arg1)
{
    drawing = !drawing;
    if (!drawing) {
        emit setGraphSignal(vector<vector<int>>());
    }
}

void HeavyMenuWidget::on_checkBox_3_stateChanged(int arg1)
{
    move_1 = !move_1;
}

void HeavyMenuWidget::on_checkBox_2_stateChanged(int arg1)
{
    move_2 = !move_2;
}
