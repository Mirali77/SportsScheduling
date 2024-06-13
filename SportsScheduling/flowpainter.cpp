#include "flowpainter.h"

FlowPainter::FlowPainter(QGLWidget *parent) : QGLWidget(parent)
{
    n = 0, m = 0;
}

FlowPainter::~GraphPainter()
{

}

void FlowPainter::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 5000, 0, 0, 1);
}

void FlowPainter::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void FlowPainter::paintGL()
{
    glLineWidth(1.8);
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGraph();
}

void FlowPainter::setGraph(int mn, int mm, vector<pair<pair<int, int>, int>> medges)
{
    n = mn, m = mm;
    edges = medges;
    update();
}

void FlowPainter::drawGraph()
{
    if (n == 0 && m == 0) return;
    auto draw_circle = [&](double x, double y, double rad, int N, bool filled = true) {
        glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
            for(int i = 0; i < N; i++ ) glVertex2d(rad * cos(2 * pi / N * i) + x, rad * sin(2 * pi / N * i) + y);
        glEnd();
    };
    qglColor(Qt::black);
    for(int i = 0; i < n; i++) draw_circle(1250, 4000 / n * i + 500, 50, 100);
    for(int i = 0; i < m; i++) draw_circle(3750, 4000 / m * i + 500, 50, 100);
    for(auto p: edges) {
        qglColor(p.second == 0 ? Qt::black : Qt::red);
        glBegin(GL_LINES);
            glVertex2d(1250, 4000 / n * p.first.first + 500);
            glVertex2d(3750, 4000 / m * p.first.second + 500);
        glEnd();
    }
}
