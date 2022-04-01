#include "renderer.h"
#include "textmanager.h"

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    Program = glCreateProgram();
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0.0f, 0.0f, w, h);
}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::CompileShaders()
{
    initializeOpenGLFunctions();
    TextManager* tm = TextManager::GetTextManager();
    if(!tm)
    {
        return;
    }

    std::string VertexSrc, FragSrc;
    tm->GetTextFromEditors(VertexSrc, FragSrc);
    unsigned int VertexShader, FragmentShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* Src = VertexSrc.c_str();
    glShaderSource(VertexShader, 1, &Src, nullptr);
    glCompileShader(VertexShader);

    Src = FragSrc.c_str();
    glShaderSource(FragmentShader, 1, &Src, nullptr);
    glCompileShader(FragmentShader);

    LinkProgram(VertexShader, FragmentShader);
    glUseProgram(Program);
}

void Renderer::LinkProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
    initializeOpenGLFunctions();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}
