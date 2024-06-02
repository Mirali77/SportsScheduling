#ifndef MIDDLEMENUWIDGET_H
#define MIDDLEMENUWIDGET_H

#include <QWidget>
#include <fstream>
#include <string>
#include "mcmfmanager.h"
#include <QFileDialog>

using namespace std;

namespace Ui {
class MiddleMenuWidget;
}

class MiddleMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MiddleMenuWidget(QWidget *parent = nullptr);
    ~MiddleMenuWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MiddleMenuWidget *ui;
};

#endif // MIDDLEMENUWIDGET_H
