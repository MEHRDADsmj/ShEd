#include "renderer.h"
#include "textmanager.h"

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget{parent}, bIsShaderDirty{true}
{
    StartTime = QTime::currentTime();
}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0.0f, 0.0f, w, h);
}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CompileShaders();
    SetUniforms();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    update();
}

void Renderer::CompileShaders()
{
    if(bIsShaderDirty == false)
    {
        return;
    }
    emit ClearErrorList();

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

    CheckCompileStatus(VertexShader, GL_VERTEX_SHADER);

    Src = FragSrc.c_str();
    glShaderSource(FragmentShader, 1, &Src, nullptr);
    glCompileShader(FragmentShader);

    CheckCompileStatus(FragmentShader, GL_FRAGMENT_SHADER);

    LinkProgram(VertexShader, FragmentShader);

    bIsShaderDirty = false;
}

void Renderer::LinkProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
    initializeOpenGLFunctions();

    glDeleteProgram(Program);
    Program = glCreateProgram();

    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    CheckLinkStatus(Program);

    glUseProgram(Program);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void Renderer::CheckCompileStatus(unsigned int Shader, GLenum Type)
{
    int success;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(Shader, 512, nullptr, infoLog);
        std::string ErrorText;
        if(Type == GL_VERTEX_SHADER)
        {
            ErrorText = "Vertex: ";
        }
        else if(Type == GL_FRAGMENT_SHADER)
        {
            ErrorText = "Fragment: ";
        }
        ErrorText.append(infoLog);
        emit AddError(ErrorText);
    }
}

void Renderer::CheckLinkStatus(unsigned int ShaderProgram)
{
    int success;
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(ShaderProgram, 512, nullptr, infoLog);
        std::string ErrorText = "Program: ";
        ErrorText.append(infoLog);
        emit AddError(ErrorText);
    }
}

void Renderer::SetUniforms()
{
    initializeOpenGLFunctions();

    unsigned int ResolutionLocation = glGetUniformLocation(Program, "resolution");
    float Screen[2] = { (float)this->width(), (float)this->height() };
    glUniform2fv(ResolutionLocation, 1, Screen);

    unsigned int TimeLocation = glGetUniformLocation(Program, "time");
    CurrentTime = QTime::currentTime();
    glUniform1f(TimeLocation, CurrentTime.msecsTo(StartTime) / 1000.0f);
}

void Renderer::MarkShaderDirty()
{
    bIsShaderDirty = true;
}
