#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout* layout1 = new QHBoxLayout();
    lightGraphPainter = new GraphPainter();
    layout1->addWidget(lightGraphPainter, 1);
    lightMenuWidget = new LightMenuWidget();
    layout1->addWidget(lightMenuWidget, 1);
    ui->lightTab->setLayout(layout1);
    connect(lightMenuWidget, &LightMenuWidget::nChangedSignal, lightGraphPainter, &GraphPainter::init);

    graphGen = new GraphGenerator();
    connect(lightMenuWidget, &LightMenuWidget::generateGraphSignal, this, &MainWindow::generateLightGraph);

    middleMenuWidget = new MiddleMenuWidget();
    QHBoxLayout* layout2 = new QHBoxLayout();
    layout2->addWidget(middleMenuWidget);
    ui->mediumTab->setLayout(layout2);

    heavyMenuWidget = new HeavyMenuWidget();
    heavyGraphPainter = new GraphPainter();
    QHBoxLayout* layout3 = new QHBoxLayout();
    layout3->addWidget(heavyGraphPainter, 1);
    layout3->addWidget(heavyMenuWidget, 1);
    ui->heavyTab->setLayout(layout3);
    connect(heavyMenuWidget, &HeavyMenuWidget::initGraphSignal, heavyGraphPainter, &GraphPainter::init);
    connect(heavyMenuWidget, &HeavyMenuWidget::setGraphSignal, heavyGraphPainter, &GraphPainter::setGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateLightGraph(int n)
{
    vector<vector<int>> graph = graphGen->buildGraph(n);
    lightGraphPainter->setGraph(graph);
}
