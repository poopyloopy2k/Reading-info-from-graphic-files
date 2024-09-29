#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
 }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString folder = QFileDialog::getExistingDirectory(this, "Выберите папку");
    if(!folder.isEmpty())
    {
        selectedFolder = folder;
        ui->label->setText("Вы выбрали папку " + folder);
        ui->label->setEnabled(true);
        ui->progressBar->setEnabled(true);
        ui->progressBar->setValue(0);
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
        qDebug() << "Папка уже выбрана. Чтобы выбрать другую, сначала сбросьте выбор.";
    }
    qDebug() << folder;
}


void MainWindow::on_pushButton_2_clicked()
{
    QDir directory(selectedFolder);
    QFileInfoList infoList = directory.entryInfoList(QDir::Files);
    for(const QFileInfo &infoFile: infoList)
    {
        QString fileName = infoFile.fileName();
        QString filePath = infoFile.filePath();
        QString extension = infoFile.suffix().toLower();
        if (extension == "jpg" || extension == "jpeg" ||
            extension == "png" || extension == "gif" ||
            extension == "bmp" || extension == "tif" )
        {
        QImage image(filePath);
            if(image.isNull())
        {
            qDebug() << "Не удалось загрузить изображение:" << filePath;
                continue;
        }
        QSize imageSize = image.size();
        int depth = image.depth();
        int dpiX = image.dotsPerMeterX();
        int dpiY = image.dotsPerMeterY();
        qDebug() << "имя файла" << fileName;
        qDebug() << "размер в пикселях" << imageSize;
        qDebug() << "глубина" << depth;
        qDebug() << "разрешение" << dpiX << " " << dpiY;
        }
    }
}

