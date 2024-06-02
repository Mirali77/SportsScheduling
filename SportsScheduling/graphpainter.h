#ifndef GRAPHPAINTER_H
#define GRAPHPAINTER_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <vector>
#include <random>

using namespace std;

const double pi = acos(-1);

class GraphPainter : public QGLWidget
{
    Q_OBJECT
private:
    vector<QColor> palitra;
    vector<vector<int>> graph;
public:
    explicit GraphPainter(QGLWidget *parent = nullptr);
    virtual ~GraphPainter();
    void initializeGL();
    void resizeGL(int w, int h);
    void setPalitra(int n);
    void drawGraph(vector<vector<int>> graph);
    void setGraph(vector<vector<int>> mgraph);
    void init(int n);
    void paintGL();

signals:

};

#endif // GRAPHPAINTER_H
