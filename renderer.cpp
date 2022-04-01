#include "renderer.h"
#include "textmanager.h"
#include <QDebug>

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Program = glCreateProgram();

    // Vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0
    };

    // Vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    // Index buffer object
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    CompileShaders();
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0.0f, 0.0f, w, h);
}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    update();
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

    int success;
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(Program, 512, NULL, infoLog);
        qInfo() << infoLog;
    }

    Src = FragSrc.c_str();
    glShaderSource(FragmentShader, 1, &Src, nullptr);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(Program, 512, NULL, infoLog);
        qInfo() << infoLog;
    }

    LinkProgram(VertexShader, FragmentShader);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    glUseProgram(Program);
}

void Renderer::LinkProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
    initializeOpenGLFunctions();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    int success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(Program, 512, NULL, infoLog);
        qInfo() << infoLog;
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}
