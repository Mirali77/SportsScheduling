#ifndef LIGHTMENUWIDGET_H
#define LIGHTMENUWIDGET_H

#include <QWidget>

namespace Ui {
class LightMenuWidget;
}

class LightMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightMenuWidget(QWidget *parent = nullptr);
    ~LightMenuWidget();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::LightMenuWidget *ui;

signals:
    void nChangedSignal(int n);
    void generateGraphSignal(int n);
};

#endif // LIGHTMENUWIDGET_H
