/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/12/21
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef AUTOCADREADER_OPENGLWIDGET_H
#define AUTOCADREADER_OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_5_Core>


#include "libdxfrw/dx_data.h"
#include "libdxfrw/dx_iface.h"
#include "DwgObject.h"

#include <vector>
#include <iostream>
#include <QColor>

using namespace std;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    vector<DwgObject> entityList;

    explicit OpenGLWidget(QWidget *parent = 0);

    void init();

    void setDataList(vector<DwgObject> list);

    double pointMapper(double cur, double all = 500);

public:

    void render_DRW_Line(DwgObject obj);

    void render_DRW_LWPolyline(DwgObject obj);

    void render_DRW_Circle(DwgObject obj);

    void render_DRW_Arc(DwgObject obj);

protected:
    void initializeGL();

    void paintGL();

    void resizeGL(int w, int h);
};


#endif //AUTOCADREADER_OPENGLWIDGET_H
