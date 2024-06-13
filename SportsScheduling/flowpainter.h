#ifndef FLOWPAINTER_H
#define FLOWPAINTER_H

#include <QWidget>
#include <QGLWidget>
#include <cmath>

using namespace std;

const double pi = acos(-1);

class FlowPainter : public QGLWidget
{
    Q_OBJECT
private:
    int n, m;
    vector<pair<pair<int, int>, int>> edges;
public:
    explicit FlowPainter(QGLWidget *parent = nullptr);
    virtual ~GraphPainter();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void setGraph(int mn, int mm, vector<pair<pair<int, int>, int>> medges);
    void drawGraph();
signals:
};

#endif // FLOWPAINTER_H
