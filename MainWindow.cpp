/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/12/20
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "MainWindow.h"

#include "ui_mainwindow.h"
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openGLWidget = new OpenGLWidget();
    fileBtn = new QPushButton("Select DWG File",this);
    pathLabel = new QLabel("please select file");
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(fileBtn);
    centralLayout->addWidget(pathLabel);
    centralLayout->addWidget(openGLWidget);
    this->ui->centralwidget->setLayout(centralLayout);
    connect(fileBtn, &QAbstractButton::clicked, this, &MainWindow::onBtnClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGLWidget()
{
    if (filePath.empty() || filePath.size() == 0)
        return;

    bool badState = false;
    dx_data fData;
    dx_iface *input = new dx_iface();
    badState = input->printText(filePath, &fData);
    if (!badState)
    {
        cout << "dwg file load error" << endl;
        pathLabel->setText("dwg file load error");
        return;
    }
    else
        pathLabel->setText(filePath.c_str());

    vector<DwgObject> objectList;
    auto mDwgData = input->cData;
    int size = mDwgData->mBlock->ent.size();
    cout << "dwg file object num: " << size << endl;
    for (std::list<DRW_Entity *>::const_iterator it =
            mDwgData->mBlock->ent.begin(); it != mDwgData->mBlock->ent.end(); ++it)
    {
        DRW_Entity *e = *it;
        DwgObject obj;
        obj.type = e->eType;
        obj.parse(e);
        objectList.push_back(obj);
    }
    openGLWidget->setDataList(objectList);
}

void MainWindow::onBtnClick()
{

    QString filter = "DWG File (*.dwg)";
    QString path = QFileDialog::getOpenFileName(this, tr("Open DWG File"), ".", filter);
    std::cout << path.toStdString() << std::endl;
    filePath = path.toStdString();
    updateGLWidget();
}
