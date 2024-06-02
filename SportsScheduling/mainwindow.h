#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphpainter.h"
#include <QHBoxLayout>
#include "lightmenuwidget.h"
#include "graphgenerator.h"
#include "middlemenuwidget.h"
#include "heavymenuwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    GraphPainter* lightGraphPainter, *heavyGraphPainter;
    LightMenuWidget* lightMenuWidget;
    GraphGenerator* graphGen;
    MiddleMenuWidget* middleMenuWidget;
    HeavyMenuWidget* heavyMenuWidget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void generateLightGraph(int n);
};
#endif // MAINWINDOW_H
