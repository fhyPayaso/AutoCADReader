/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/12/21
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "OpenGLWidget.h"


OpenGLWidget::OpenGLWidget(QWidget *parent)
{
    setMinimumHeight(800);
    setMinimumWidth(800);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    init();
}

void OpenGLWidget::render_DRW_Line(DwgObject obj)
{
    DRW_Line line = obj.entity_Line;
//    cout << "thickness : " << line.thickness << endl;

    glBegin(GL_LINES);
    glVertex3f(pointMapper(line.basePoint.x), pointMapper(line.basePoint.y), 0.0f);
    glVertex3f(pointMapper(line.secPoint.x), pointMapper(line.secPoint.y), 0.0f);
    glEnd();
    glFlush();
}

void OpenGLWidget::render_DRW_LWPolyline(DwgObject obj)
{
    DRW_LWPolyline polyline = obj.entity_LWPolyline;

//    cout << "color : " << polyline.color << endl;
//    cout << "color name: " << polyline.colorName << endl;
//    cout << "color24 : " << polyline.color24 << endl;
//    QColor color = QColor::fromRgba(polyline.color);
//    cout << "red: " << color.red() << endl;
//    cout << "green: " << color.green() << endl;
//    cout << "blue: " << color.blue() << endl;

    auto list = polyline.vertlist;
    glBegin(GL_LINES);
    for (int i = 0; i < polyline.vertlist.size(); i++)
    {
        int nex = i == polyline.vertlist.size() - 1 ? 0 : i + 1;
        glVertex3f(pointMapper(list[i]->x), pointMapper(list[i]->y), 0.0f);
        glVertex3f(pointMapper(list[nex]->x), pointMapper(list[nex]->y), 0.0f);
    }
    glEnd();
    glFlush();
}

void OpenGLWidget::render_DRW_Circle(DwgObject obj)
{
    DRW_Circle circle = obj.entity_Circle;

    int n = 360;     //这里的n表示用多边形绘制圆的精度，可以考虑增大精度

    float R = pointMapper(circle.radious);
    double centerX = pointMapper(circle.basePoint.x);
    double centerY = pointMapper(circle.basePoint.y);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < n; i++)
        glVertex2f(centerX + R * cos(2 * M_PI * i / n), centerY + R * sin(2 * M_PI * i / n));
    glVertex2f(centerX + R * cos(0), centerY + R * sin(0));
    glEnd();
    glFlush();
}

void OpenGLWidget::render_DRW_Arc(DwgObject obj)
{
    DRW_Arc arc = obj.entity_Arc;
//    cout << "start angle :" << arc.staangle << endl;
//    cout << "end angle :" << arc.endangle << endl;
//    cout << "center :   x: " << arc.basePoint.x << "\ty:" << arc.basePoint.y << endl;
//    cout << "radius" << arc.radious << endl;
    double R = pointMapper(arc.radious);
    double centerX = pointMapper(arc.basePoint.x);
    double centerY = pointMapper(arc.basePoint.y);

    int startRealAngle = 360 * arc.staangle / (2 * M_PI);
    int endRealAngle = 360 * arc.endangle / (2 * M_PI);
    int diffRealAngle = endRealAngle - startRealAngle;
    double diffAngle = arc.endangle - arc.staangle;
    double angleStep = diffAngle / diffRealAngle;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= diffRealAngle; i++)
    {
        double angle = arc.staangle + i * angleStep;
        glVertex2f(centerX + R * cos(angle), centerY + R * sin(angle));
    }
    glEnd();
    glFlush();
}

void OpenGLWidget::setDataList(vector<DwgObject> list)
{
    entityList = list;
}

void OpenGLWidget::init()
{
    if (entityList.empty())
        return;
    // =====================================================
    for (auto e : entityList)
    {
        switch (e.type)
        {
            case DRW::LINE:
                render_DRW_Line(e); // 直线
                break;
            case DRW::LWPOLYLINE:
                render_DRW_LWPolyline(e); // 多段线
                break;
            case DRW::CIRCLE:
                render_DRW_Circle(e); // 圆
                break;
            case DRW::ARC: //圆弧
                render_DRW_Arc(e);
                break;
            case DRW::TEXT: // 文字
            {
                cout << "Text ===> ";
                cout << e.entity_Text.text << endl;
                break;
            }
            case DRW::MTEXT: // 多行文字
            {
                cout << "MTEXT ===> ";
                cout << e.entity_MText.text << endl;
                break;
            }
            default:
                break;
        }
    }
}

double OpenGLWidget::pointMapper(double cur, double all)
{
    double p = cur / all;
    if (p > 1.0f) p = 1.0f;
    if (p < -1.0f) p = -1.0f;
    return p;
}


