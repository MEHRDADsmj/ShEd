#include "renderer.h"

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0.0f, 0.0f, w, h);
}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
