#include "lightmenuwidget.h"
#include "ui_lightmenuwidget.h"

LightMenuWidget::LightMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightMenuWidget)
{
    ui->setupUi(this);
}

LightMenuWidget::~LightMenuWidget()
{
    delete ui;
}

void LightMenuWidget::on_lineEdit_returnPressed()
{
    QString txt = ui->lineEdit->text();
    int n = txt.toInt();
    emit nChangedSignal(n);
}

void LightMenuWidget::on_pushButton_clicked()
{
    QString txt = ui->lineEdit->text();
    int n = txt.toInt();
    emit generateGraphSignal(n);
}
