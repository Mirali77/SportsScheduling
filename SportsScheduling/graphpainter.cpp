#include "graphpainter.h"

GraphPainter::GraphPainter(QGLWidget *parent) : QGLWidget(parent)
{
    init(0);
}

GraphPainter::~GraphPainter()
{

}

void GraphPainter::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 5000, 0, 0, 1);
}

void GraphPainter::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GraphPainter::setPalitra(int n)
{
    palitra = vector<QColor>(n + 1);
    random_device rd;
    mt19937 gen(rd());
    palitra[0] = Qt::black;
    for(int i = 1; i <= n; i++) {
        palitra[i] = QColor::fromRgb(gen() % 256, gen() % 256, gen() % 256);
    }
}

void GraphPainter::drawGraph(vector<vector<int>> graph)
{
    if (graph.empty()) return;
    auto draw_circle = [&](double x, double y, double rad, int N, bool filled = true) {
        glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
            for(int i = 0; i < N; i++ ) glVertex2d(rad * cos(2 * pi / N * i) + x, rad * sin(2 * pi / N * i) + y);
        glEnd();
    };
    int n = graph.size();
    qglColor(Qt::black);
    for(int i = 0; i < n; i++) draw_circle(2500 + 2000 * sin(2 * pi / n * i), 2500 + 2000 * cos(2 * pi / n * i), 50, 100);
    for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
        qglColor(palitra[graph[i][j]]);
        glBegin(GL_LINES);
            glVertex2d(2500 + 2000 * sin(2 * pi / n * i), 2500 + 2000 * cos(2 * pi / n * i));
            glVertex2d(2500 + 2000 * sin(2 * pi / n * j), 2500 + 2000 * cos(2 * pi / n * j));
        glEnd();
    }
}

void GraphPainter::setGraph(vector<vector<int>> mgraph)
{
    if (graph.size() != mgraph.size()) setPalitra(mgraph.size());
    graph = mgraph;
    update();
}

void GraphPainter::init(int n)
{
    graph = vector<vector<int>>(n, vector<int>(n));
    setPalitra(n);
    update();
}

void GraphPainter::paintGL()
{
    glLineWidth(1.8);
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGraph(graph);
}
