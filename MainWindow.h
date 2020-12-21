/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/12/20
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef AUTOCADREADER_MAINWINDOW_H
#define AUTOCADREADER_MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDockWidget>
#include <QPushButton>
#include <QLabel>

#include <iostream>
#include <string>


#include "DwgObject.h"
#include "OpenGLWidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void updateGLWidget();

public slots:

    void onBtnClick();

private:


    OpenGLWidget *openGLWidget;

    std::string filePath;

    Ui::MainWindow *ui;

    QPushButton *fileBtn;

    QLabel *pathLabel;

};


#endif //AUTOCADREADER_MAINWINDOW_H
