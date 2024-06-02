#include "middlemenuwidget.h"
#include "ui_middlemenuwidget.h"

MiddleMenuWidget::MiddleMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiddleMenuWidget)
{
    ui->setupUi(this);
}

MiddleMenuWidget::~MiddleMenuWidget()
{
    delete ui;
}

void MiddleMenuWidget::on_pushButton_clicked()
{
    string inPath = ui->lineIn->text().toStdString(), outPath = ui->lineOut->text().toStdString();
    ifstream fin(inPath);
    ofstream fout(outPath);
    int n, m;
    fin >> n >> m;
    int tn = n & 1 ? n : n - 1;

    vector<vector<ll>> c(tn, vector<ll>(m)), b = c, res = c;
    for(int i = 0; i < tn; i++) for(int j = 0; j < m; j++) fin >> c[i][j];
    for(int i = 0; i < tn; i++) for(int j = 0; j < m; j++) fin >> b[i][j];

    int s = tn + m + 2;
    MCMFManager mcmf(s, 1e17);
    for(int i = 0; i < tn; i++) mcmf.add_edge(0, i + 1, n / 2, 0);
    for(int i = 0; i < m; i++) mcmf.add_edge(i + 1 + tn, s - 1, 1e17, 0);
    for(int i = 0; i < tn; i++) for(int j = 0; j < m; j++) mcmf.add_edge(i + 1, j + 1 + tn, b[i][j], -c[i][j]);

    ll val = mcmf.calc(0, s - 1);
    vector<pair<pair<int, int>, ll>> edges = mcmf.getEdges();

    for(auto e: edges) res[e.fst.fst - 1][e.fst.snd - 1 - tn] = e.snd;

    fout << val << '\n';
    for(int i = 0; i < tn; i++) {
        for(int j = 0; j < m; j++) fout << res[i][j] << " ";
        fout << '\n';
    }
}

void MiddleMenuWidget::on_pushButton_2_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбрать файл", "/home",
                       "All files (*.*);; Text (*.txt) ;;");
    ui->lineIn->setText(path);
}

void MiddleMenuWidget::on_pushButton_3_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбрать файл", "/home",
                       "All files (*.*);; Text (*.txt) ;;");
    ui->lineOut->setText(path);
}
