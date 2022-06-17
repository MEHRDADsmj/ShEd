#ifndef RENDERER_H
#define RENDERER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QTime>

class QLabel;

class Renderer : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Renderer(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void MarkShaderDirty();
    void SetFPSLabel(QLabel* NewLabel);

private:
    void CompileShaders();
    void LinkProgram(unsigned int VertexShader, unsigned int FragmentShader);

    void CheckCompileStatus(unsigned int Shader, GLenum Type);
    void CheckLinkStatus(unsigned int ShaderProgram);

    void SetUniforms();

    unsigned int Program;
    bool bIsShaderDirty;

    QTime StartTime;
    QTime CurrentTime;
    QLabel* FPSLabel;

signals:
    void AddError(std::string Error);
    void ClearErrorList();

};

#endif // RENDERER_H
