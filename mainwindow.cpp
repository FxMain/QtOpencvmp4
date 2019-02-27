#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QDialog>
#include "qrcode/qrencode.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QRectF>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <qxtglobalshortcut/qxtglobalshortcut.h>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QProgressDialog>
QProcess*  poc;
QString NewFileName();
bool isFileExist(QString fullFileName);
void FineName(QString s[],int &n,int mode);//最多寻找倒数的n个文件名，返回文件名和符合个数 mode=0网络连接 mode=1本地连接
using namespace cv;
using namespace std;
int openCamaraB=2;
int RCcount=0;
QSerialPort *serial;
int RCtime=-1;
QString QrCodeuL="";
QString CapuL="";
void delay_ms(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
#include <QCloseEvent>
void MainWindow::closeEvent( QCloseEvent * event )
{
switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
   {
     case 0:
          event->accept();
          openCamaraB=2;
          QApplication::quit();
          break;
     case 1:
     default:
          event->ignore();


         break;
   }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(ui->pic, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(ui->closeCam, SIGNAL(clicked()), this, SLOT(closeCamara()));

    setWindowFlags( Qt::WindowStaysOnTopHint);
    //ui->pushButton_3->setFlat(true);//就是这句实现按钮透明的效果
    ui->pushButton_2->setFlat(true);
    ui->pushButton->setFlat(true);
    ui->open->setFlat(true);
    ui->closeCam->setFlat(true);
    ui->pic->setFlat(true);

    ui->pushButton_2->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton->setStyleSheet("color: rgb(255, 255, 255)");
    ui->open->setStyleSheet("color: rgb(255, 255, 255)");
    ui->closeCam->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pic->setStyleSheet("color: rgb(255, 255, 255)");
    //ui->lineEdit->setFlat(true);
    ui->lineEdit->setStyleSheet("QLineEdit{color: rgb(255, 255, 255);background:transparent;border:0px;border-bottom:1px solid #000;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{color: rgb(255, 255, 255);background:transparent;border:0px;border-bottom:1px solid #000;}");
    //ui->lineEdit->setStyleSheet("color: rgb(255, 255, 255)");
    //查找可用的串口
      foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
      {
         QSerialPort serial;
         serial.setPort(info);
         if(serial.open(QIODevice::ReadWrite))
          {
             ui->PortBox->addItem(serial.portName());
            serial.close();
         }
    }

    bj();
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(1000);

    ui->PortBox->setStyleSheet("QComboBox{ background-color: rgb(35, 35, 37);\
                                        color: rgb(255, 255, 255);font-size:16px;}"
                                        "QComboBox QAbstractItemView{background-color: rgb(255, 255, 255);color:rgb(0,0,0);font-size:16px;}");

    ui->PortBox_2->setStyleSheet("QComboBox{ background-color: rgb(35, 35, 37);\
                                    color: rgb(255, 255, 255);font-size:16px;}"
                                    "QComboBox QAbstractItemView{background-color: rgb(255, 255, 255);color:rgb(0,0,0);font-size:16px;}");

    ui->PortBox_2->addItem("正转");
    ui->PortBox_2->addItem("反转");
    ui->progressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条
    ui->progressBar_2->setVisible(false);  //false:隐藏进度条  true:显示进度条


    ui->pushButton_sd->setFlat(true);
    ui->pushButton_sdz->setFlat(true);
    ui->pushButton_jd->setFlat(true);
    ui->pushButton_jdz->setFlat(true);

    ui->pushButton_sdz->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_jd->setStyleSheet( "color: rgb(255, 255, 255)");
    ui->pushButton_sd->setStyleSheet( "color: rgb(255, 255, 255)");
    ui->pushButton_jdz->setStyleSheet("color: rgb(255, 255, 255)");

//    ui->horizontalSlider->setStyleSheet("QSlider::groove:horizontal{ background-color: rgb(35, 35, 37);\
//                                        color: rgb(0, 0, 0);}"
//                                        );
    //设置滑块
    ui->horizontalSlider->setStyleSheet("QSlider::handle:horizontal {\
                                        background-color: rgb(100, 100, 100);\
                                         }" );
    ui->horizontalSlider_2->setStyleSheet("QSlider::handle:horizontal {\
                                        background-color: rgb(100, 100, 100);\
                                         }" );
    ui->horizontalSlider->setMinimum(0x23);      // 设置滑动条的最小值
    ui->horizontalSlider->setMaximum(0x61);   // 设置滑动条的最大值
    ui->horizontalSlider->setValue(0x51); // 设置滑动条初始值

    ui->horizontalSlider_2->setMinimum(1);      // 设置滑动条的最小值
    ui->horizontalSlider_2->setMaximum(360);   // 设置滑动条的最大值
    ui->horizontalSlider_2->setValue(360); // 设置滑动条初始值

   // QSettings settings("Setting.ini", QSettings::IniFormat); // 当前目录的INI文件
     //GPS setting
     /*settings.beginGroup("FrameRate");
     settings.setValue("Rate", 30);
     settings.endGroup();*/
    /*settings.beginGroup("FrameRate");
    settings.setValue("DelayMs", 1000);
    settings.endGroup();*/
    /*settings.beginGroup("FrameRate");
    settings.setValue("QrCodeuL", "www.jielizinxi.com/mp4/");
    settings.endGroup();*/

//    QSettings Rtings("Setting.ini", QSettings::IniFormat);

//    if(Rtings.contains("FrameRate/CapuL"))
//    {
//        CapuL = Rtings.value("FrameRate/CapuL").toString();
//        //DELAY=DELAYStr.toInt();
//        qDebug()<<CapuL;
//    }
    this->resize( QSize( 1100, 700 ));
    ui->open->setEnabled (false);


    ui->pushButton_3->setFlat(true);//按钮透明
    ui->pushButton_4->setFlat(true);//按钮透明
    ui->pushButton_5->setFlat(true);//按钮透明
    ui->pushButton_6->setFlat(true);//按钮透明
    ui->pushButton_7->setFlat(true);//按钮透明
    ui->pushButton_8->setFlat(true);//按钮透明
    ui->pushButton_9->setFlat(true);//按钮透明
    ui->pushButton_10->setFlat(true);//按钮透明
    ui->pushButton_11->setFlat(true);//按钮透明

    ui->pushButton_3->setStyleSheet("color: rgb(255, 255, 255)");//字体白色
    ui->pushButton_4->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_5->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_6->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_7->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_8->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_9->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_10->setStyleSheet("color: rgb(255, 255, 255)");
    ui->pushButton_11->setStyleSheet("color: rgb(255, 255, 255)");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255)");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255)");

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoWidget->hide();
    player->setVideoOutput(videoWidget);

    //ui->verticalLayout->h
    //setAttribute(Qt::WA_TransparentForMouseEvents,true);
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(QKeySequence("F11"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(myslot()));
    QxtGlobalShortcut* shortcut2 = new QxtGlobalShortcut(QKeySequence("F10"), this);
    connect(shortcut2, SIGNAL(activated()), this, SLOT(myslot2()));

    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->pushButton_dz1_2->hide();
    ui->pushButton_dz1->hide();
    ui->pushButton_12->hide();
    ui->label_2->hide();
     ui->label_3->hide();



}
void MainWindow::NEWFile(QString s){
    QString runPath1 = QCoreApplication::applicationDirPath();
    int first = runPath1.lastIndexOf ("/");
     runPath1=runPath1.left(first)+"/Gopro/"+s;
     QFile file(runPath1);
     file.open( QIODevice::WriteOnly );
     file.close();
}
void MainWindow::DEFile(QString s){
    QString runPath1 = QCoreApplication::applicationDirPath();
    int first = runPath1.lastIndexOf ("/");
     runPath1=runPath1.left(first)+"/Gopro/"+s;
    QFile::remove(runPath1);

}
int myslotsta=1;
int myslotsta2=0;
int mtime=0;
void MainWindow::myslot()//录制
{
    if(myslotsta2==0)return;
    myslotsta2=0;
    myslotsta=0;
    //return;
    qDebug()<<"f11";
    //qDebug()<<findClassAV("MP4",0);
    openCamara();
    while(myslotsta==0){
        delay_ms(50);
    }
    myslotsta=0;
    on_pic_clicked();
    myslotsta=1;
    on_pushButton_12_clicked();
    QString runPath1 = QCoreApplication::applicationDirPath();
    int first = runPath1.lastIndexOf ("/");
    runPath1=runPath1.left(first)+"/";
    QScreen *screen = QGuiApplication::primaryScreen();

   {


        QString s[3]={""};
        int n=3;
        FineName(s,n,0);
        //qDebug()<<s[0]<<":"<<s[1]<<":"<<s[2]<<":"<<n;
        if(n<=0)
        {
            ui->QR3->hide();
            ui->QR1->hide();
            ui->QR2->hide();
            return;
        }
        else{
            ui->QR3->hide();
            ui->QR1->hide();
            ui->QR2->hide();
            for(int i=0;i<n;i++)
            {
               if(i==0)
               {
                if(!s[0].isEmpty())
                {
                    ui->QR1->show();
                   GenerateQRcode(s[0],ui->QR1);
                }else{
                   ui->QR1->hide();
                }
               }
               if(i==1)
               {
                   if(!s[1].isEmpty())
                   {
                       ui->QR2->show();
                       GenerateQRcode(s[1],ui->QR2);
                   }else{
                      // GenerateQRcode("",ui->QR2);
                       ui->QR2->hide();
                   }


               }
               if(i==2)
               {
                   if(!s[2].isEmpty())
                   {
                        GenerateQRcode(s[2],ui->QR3);
                        ui->QR3->show();
                   }else{


                   }

               }

            }
        }
      }

    QString ss[3]={""};
    int n=3;
    FineName(ss,n,1);
    if(!ss[0].isEmpty()){

        ss[0].replace(".mp4",".png");
        QFile file(ss[0]);
        if (file.exists())
        {
            file.remove();
        }
    }else{
        return;
    }

    screen->grabWindow(ui->QR1->winId()).save(ss[0]);

myslotsta2=1;
}
void MainWindow::myslot2()//转换
{
    //qDebug()<<"f10"<<findClassAV("MP4",1);
    on_pushButton_12_clicked();

    //on_pic_clicked();
}
void MainWindow::handleTimeout()//定时器
{
    if(openCamaraB!=2)return;
    static int ccc=-1;

    //qDebug()<<"Enter timeout processing function\n";
    if(ccc==-1)
    {

        bj();
    }

    if(ccc>2){

        ccc=0;
        QString s[3]={""};
        int n=3;
        FineName(s,n,0);
        //qDebug()<<s[0]<<":"<<s[1]<<":"<<s[2]<<":"<<n;
        if(n<=0)
        {
            ui->QR3->hide();
            ui->QR1->hide();
            ui->QR2->hide();
            goto END;
        }
        else{
            ui->QR3->hide();
            ui->QR1->hide();
            ui->QR2->hide();
            for(int i=0;i<n;i++)
            {
               if(i==0)
               {
                if(!s[0].isEmpty())
                {
                    ui->QR1->show();
                   GenerateQRcode(s[0],ui->QR1);
                }else{
                   ui->QR1->hide();
                }
               }
               if(i==1)
               {
                   if(!s[1].isEmpty())
                   {
                       ui->QR2->show();
                       GenerateQRcode(s[1],ui->QR2);
                   }else{
                      // GenerateQRcode("",ui->QR2);
                       ui->QR2->hide();
                   }


               }
               if(i==2)
               {
                   if(!s[2].isEmpty())
                   {
                        GenerateQRcode(s[2],ui->QR3);
                        ui->QR3->show();
                   }else{


                   }

               }

            }
        }
      }
    ccc++;
     //qDebug()<<ccc;
END:
     ;
    /*if(m_pTimer->isActive()){
        m_pTimer->stop();
    }*/
}
void MainWindow::bj()
{
    //你的代码
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QString runPath = QCoreApplication::applicationDirPath()+"/res/backgroud.jpg";
    //qDebug()<<runPath;
      QPalette palette = this->palette();
      palette.setBrush(QPalette::Background,
              QBrush(QPixmap(runPath).scaled(// 缩放背景图.
                  this->size(),
                  Qt::IgnoreAspectRatio,
                  Qt::SmoothTransformation)));             // 使用平滑的缩放方式
      this->setPalette(palette);                           // 给widget加上背景图
     // qDebug()<<width()<<"|"<<height();
    float w=(float)width()/1024.0;
    float h=(float)height()/768.0;
    ui->pushButton->setGeometry(w*886,h*14,70*w,42*h);
    ui->PortBox->setGeometry(w*777,h*14,96*w,42*h);

    ui->PortBox_2->setGeometry(w*777-ui->PortBox->width(),h*14,96*w,42*h);
    ui->pushButton_2->setGeometry(w*82,h*72,145*w,42*h);
    ui->open->setGeometry(w*233,h*72,145*w,42*h);
    ui->closeCam->setGeometry(w*385,h*72,145*w,42*h);
    ui->pic->setGeometry(w*535,h*72,145*w,42*h);
   // ui->label->setGeometry(w*45,h*140,933*w,586*h);
    ui->label->setGeometry(w*300,h*140,707*w,606*h);

    //ui->label->setGeometry(w*233+145*w*0.4,h*140,933*w-(w*233+145*w*0.4-w*45),586*h);
    ui->lineEdit->setGeometry(w*711,h*81,216*w,26*h);

    ui->pushButton_sd->setGeometry(w*33,h*13,68*w,36*h);
    ui->pushButton_sdz->setGeometry(w*109,h*13,29*w,36*h);
    ui->pushButton_jd->setGeometry(w*371,h*13,67*w,36*h);
    ui->pushButton_jdz->setGeometry(w*446,h*13,29*w,36*h);

    ui->horizontalSlider->setGeometry(w*166,h*20,174*w,26*h);
    //ui->horizontalSlider_2->setGeometry(w*503,h*20,174*w,26*h);
    ui->horizontalSlider_2->setGeometry(w*503,h*20,100*w,26*h);
    ui->lineEdit_2->setGeometry(w*625,h*20,40*w,26*h);
//    ui->QR1->setGeometry(w*24,h*134,(191-24)*w,(191-24)*w);
//    ui->pushButton_3->setGeometry(w*204,h*233,70*w,28*h);
//    ui->pushButton_4->setGeometry(w*204,h*271,70*w,28*h);

//    ui->QR2->setGeometry(w*24,h*337,(191-22)*w,(191-24)*w);
//    ui->pushButton_5->setGeometry(w*204,h*(233+(337-134)),70*w,28*h);
//    ui->pushButton_6->setGeometry(w*204,h*(271+(337-134)),70*w,28*h);

//    ui->QR3->setGeometry(w*24,h*539,(191-22)*w,(191-24)*w);
//    ui->pushButton_7->setGeometry(w*204,h*(233+(539-134)),70*w,28*h);
//    ui->pushButton_8->setGeometry(w*204,h*(271+(539-134)),70*w,28*h);

    int QRH=(732-133)*h;
    int d=10;
    int QRh=(QRH-d*2)/3;
    int x0=w*24;
    int y0=h*134;

    ui->QR1->setGeometry(x0,y0,QRh,QRh);
    ui->pushButton_3->setGeometry(w*204,h*233,70*w,28*h);
    ui->pushButton_4->setGeometry(w*204,h*271,70*w,28*h);

    ui->QR2->setGeometry(x0,y0+QRh+d,QRh,QRh);
    ui->pushButton_5->setGeometry(w*204,h*(233+(337-134)),70*w,28*h);
    ui->pushButton_6->setGeometry(w*204,h*(271+(337-134)),70*w,28*h);

    ui->QR3->setGeometry(x0,y0+2*(QRh+d),QRh,QRh);
    ui->pushButton_7->setGeometry(w*204,h*(233+(539-134)),70*w,28*h);
    ui->pushButton_8->setGeometry(w*204,h*(271+(539-134)),70*w,28*h);

    ui->pushButton_9->setGeometry(w*204,h*(233-36),70*w,28*h);
    ui->pushButton_10->setGeometry(w*204,h*((233+(337-134)-36)),70*w,28*h);
    ui->pushButton_11->setGeometry(w*204,h*((233+(539-134)-36)),70*w,28*h);
    ui->progressBar->move( ui->label->x()+ui->label->width()/2-ui->progressBar->width()/2,ui->label->y()+ui->label->height()/2);
    ui->progressBar_2->move( ui->label->x()+ui->label->width()/2-ui->progressBar->width()/2,ui->label->y()+ui->label->height()/2);



}
void MainWindow::resizeEvent(QResizeEvent *event){

    bj();
    QWidget::resizeEvent(event);
}

MainWindow::~MainWindow()
{

    //capture.release();
    //cv::destroyWindow("Preview");
    openCamaraB=2;
    qDebug()<<"MainWindow::~MainWindow()";
    delete ui;
    //QApplication* app;
    //app->quit();


}
bool diejia(cv::Mat &dst, cv::Mat &src,
    double scale = 1.0, //整体透明度
    double size = 1.0,//图片缩放比例
    double angle = 0,//图片旋转角度
    cv::Point location = cv::Point(0, 0)//图片位置

)
{
    if (dst.channels() != 3 || src.channels() != 4 || location.x>dst.cols || location.y>dst.cols)
    {
        return false;
    }


    cv::Mat small_size = src.clone();

    if (size != 1 || angle != 0) {
        int width = src.cols>(dst.cols - location.x) ? (dst.cols - location.x) : src.cols;
        int length = src.rows>(dst.rows - location.y) ? (dst.rows - location.y) : src.rows;
        cv::Mat rotation = cv::getRotationMatrix2D(cv::Point2f(length / 2, width / 2), angle, size);
        cv::warpAffine(small_size, small_size, rotation, cv::Size(width, length));
    }
    //imshow("test", small_size);
    //std::cout << small_size.cols << " " << small_size.rows << std::endl;
    cv::Mat dst_part(dst, cv::Rect(location.x, location.y, small_size.cols, small_size.rows));

    std::vector<cv::Mat>src_channels;
    std::vector<cv::Mat>dst_channels;
    split(small_size, src_channels);
    split(dst_part, dst_channels);
    //	CV_Assert(src_channels.size() == 4 && dst_channels.size() == 3);

    if (scale < 1)
    {
        src_channels[3] *= scale;
        scale = 1;
    }
    for (int i = 0; i < 3; i++)
    {
        dst_channels[i] = dst_channels[i].mul(255.0 / scale - src_channels[3], scale / 255.0);
        dst_channels[i] += src_channels[i].mul(src_channels[3], scale / 255.0);
    }
    merge(dst_channels, dst_part);
    return true;
}

/******************************
********* 打开摄像头 ***********
*******************************/
void MainWindow::on_pushButton_2_clicked()//预览
{

    if(ui->pushButton_2->text()=="打开音视频合成"){
        //ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        //ui->lineEdit_5->show();
        ui->pushButton_dz1_2->show();
        //ui->pushButton_dz1->show();
        //ui->pushButton_12->show();
        //ui->label_2->show();
        ui->label_3->show();
        ui->pushButton_2->setText("关闭音视频合成");
    }else{
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();
        ui->pushButton_dz1_2->hide();
        ui->pushButton_dz1->hide();
        ui->pushButton_12->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->pushButton_2->setText("打开音视频合成");
    }
    //打开脚本
    //file:///F:/gQtOpencvmp4/gopro/B/dist/gopro_hero3.exe

//    QProcess pro;
//    QString runPath = QCoreApplication::applicationDirPath();
//    int first = runPath.lastIndexOf ("/");
//    runPath=runPath.left(first)+"/Gopro/gopro_hero.exe";
//    qDebug()<<runPath;
//    QStringList list;
//    pro.start(runPath,list);
    return;//预览去掉
    videoWidget->hide();
        openCamaraB=0;
        Mat frame;
       VideoCapture capture;
       QSettings Rtings("Setting.ini", QSettings::IniFormat);
        CapuL.clear();
       if(Rtings.contains("FrameRate/CapuL"))
       {
           CapuL = Rtings.value("FrameRate/CapuL").toString();
           //DELAY=DELAYStr.toInt();
           qDebug()<<CapuL;
       }
       if(CapuL.size()>4)
       {
            capture.open(0);
       }else{
           capture.open(CapuL.toStdString());
       }

       if(!capture.isOpened())
       {
           qDebug()<<"can not open the camear......";
           return ;
       }
       //设置摄像头参数 不要随意修改
       capture.set(CV_CAP_PROP_FRAME_WIDTH, 1920);//宽度
       capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);//高度

       //capture.set(CV_CAP_PROP_FRAME_WIDTH, 1618-303);//宽度
       //capture.set(CV_CAP_PROP_FRAME_HEIGHT, 859-146);//高度
       capture.set(CV_CAP_PROP_FPS, 30);//帧数


       //打印摄像头参数
       qDebug("width = %.2f\n",capture.get(CV_CAP_PROP_FRAME_WIDTH));
       qDebug("height = %.2f\n",capture.get(CV_CAP_PROP_FRAME_HEIGHT));
       qDebug("fbs = %.2f\n",capture.get(CV_CAP_PROP_FPS));
       qDebug("brightness = %.2f\n",capture.get(CV_CAP_PROP_BRIGHTNESS));
       qDebug("contrast = %.2f\n",capture.get(CV_CAP_PROP_CONTRAST));
       qDebug("saturation = %.2f\n",capture.get(CV_CAP_PROP_SATURATION));
       qDebug("hue = %.2f\n",capture.get(CV_CAP_PROP_HUE));
       qDebug("exposure = %.2f\n",capture.get(CV_CAP_PROP_EXPOSURE));



       //保存视频的路径
           string outputVideoPath = "out1.avi";

           //获取当前摄像头的视频信息
           int PROP_FRAME_WIDTH=capture.get(CV_CAP_PROP_FRAME_WIDTH);
           cv::Size sWH ;
           if(PROP_FRAME_WIDTH>=1920)
           {
                sWH = cv::Size((1618-303)/4*4,(859-146)/4*4);
           }
            else
           {
               sWH = cv::Size(capture.get(CV_CAP_PROP_FRAME_WIDTH),capture.get(CV_CAP_PROP_FRAME_HEIGHT));
           }

           QSettings settings("Setting.ini", QSettings::IniFormat);
           int FrameRateInt=30;
           if(settings.contains("FrameRate/Rate"))
           {
               QString FrameRateStr = settings.value("FrameRate/Rate").toString();
               FrameRateInt=FrameRateStr.toInt();
               qDebug()<<FrameRateInt;

           }
           //return;
           VideoWriter outputVideo;

           outputVideo.open(outputVideoPath, CV_FOURCC('M', 'P', '4', '2'), FrameRateInt, sWH);

           double fps;

               cv::namedWindow("Preview", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL就是0
               double t = 0;
               //QString mation="录制结束!";
       while (capture.read(frame))
       {


           Mat image = frame;
           if(PROP_FRAME_WIDTH>=1920)
           {

                Rect rect(303/4*4, 146/4*4, (1618-303)/4*4,(859-146)/4*4);
                image = image(rect);
           }


           if(openCamaraB==1)
           {
                outputVideo << image;

           }

           // getTickcount函数：返回从操作系统启动到当前所经过的毫秒数
           // getTickFrequency函数：返回每秒的计时周期数
           // t为该处代码执行所耗的时间,单位为秒,fps为其倒数
           t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
           fps = 1.0 / t;
            t=(double)cv::getTickCount();
            //qDebug()<<fps;

           if(openCamaraB==2)
           {

              cv::destroyWindow("Preview");
              outputVideo.release();
              //capture.
              ui->progressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条
              capture.release();
               QMessageBox::information(this,"提示","已结束!");
               ui->open->setEnabled (true);
              return;
           }

          imshow("Preview",image);
          cv::resizeWindow("Preview", 0,0);
          QRect WINXY=frameGeometry();
          cv::moveWindow("Preview",WINXY.x(),WINXY.y());
          waitKey(1);
          cvtColor(image,image,CV_BGR2RGB);
          int w=(ui->label->width()/4)*4;
          int h=(ui->label->height()/4)*4;
          cv::resize(image,image,Size(w,h),0,0,INTER_LINEAR);
          QImage img = QImage((const uchar*)image.data, image.cols, image.rows,QImage::Format_RGB888);
          ui->label->setPixmap( QPixmap::fromImage(img));

       }




}

/*********************************
********* 读取摄像头信息 ***********
**********************************/
void MainWindow::readFarme()
{

}

/*************************
********* 拍照 ***********
**************************/
void MainWindow::takingPictures()
{

}

/*******************************
***关闭摄像头，释放资源，必须释放***
********************************/
void MainWindow::closeCamara()
{
    openCamaraB=2;

    ui->open->setText("录制");
    ui->open->setStyleSheet("color: rgb(255, 255, 255)");
    ui->progressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条
    ui->open->setEnabled (true);
}



void MainWindow::on_pushButton_clicked()
{
    serial = new QSerialPort;
    //设置串口名
    //serial->setPortName("COM"+ui->lineEdit->text());
     serial->setPortName(ui->PortBox->currentText());
    //打开串口
    if(!serial->open(QIODevice::ReadWrite)){
        //QMessageBox::information(this,"提示","打开失败!");
        return;
    }
    //设置波特率
    if(!serial->setBaudRate(QSerialPort::Baud115200)){
        //QMessageBox::information(this,"提示","打开失败!");
        return;
    }
    //设置数据位数
    if(!serial->setDataBits(QSerialPort::Data8)){
        //QMessageBox::information(this,"提示","打开失败!");
        return;
    }
     //设置奇偶校验
     if(!serial->setParity(QSerialPort::NoParity)){
         //QMessageBox::information(this,"提示","打开失败!");
         return;
     }
    //设置停止位
    if(!serial->setStopBits(QSerialPort::OneStop)){
        //QMessageBox::information(this,"提示","打开失败!");
        return;
    }
    //设置流控制
    if(!serial->setFlowControl(QSerialPort::NoFlowControl)){
        //QMessageBox::information(this,"提示","打开失败!");
        return;
    }
    QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::serialRead_Data);
    QMessageBox::information(this,"提示","设备打开成功!");
    ui->open->setEnabled (true);
    myslotsta2=1;

}
QString MainWindow::Sgopro(QString s){
    QString runPath1 = QCoreApplication::applicationDirPath();
    int first = runPath1.lastIndexOf ("/");
    runPath1=runPath1.left(first)+"/Gopro/"+s;
    return runPath1;
}
void MainWindow::serialRead_Data()
{
    QString runPath1 = QCoreApplication::applicationDirPath();
    int first = runPath1.lastIndexOf ("/");
    runPath1=runPath1.left(first)+"/Gopro/";
    delay_ms(30);
    QByteArray buf;
    buf = serial->readAll();
    QByteArray c;
    int i=0;
    c[i++]=0xaa;
    if(ui->PortBox_2->currentText()=="正转"){
        c[i++]=0x01;
    }else{
        c[i++]=0x02;
    }
    c[i++]=ui->horizontalSlider->value();
    c[i++]=(ui->horizontalSlider_2->value()/360.0)*140;
//    c[i++]=0x51;
//    c[i++]=0x8c;
    //c[i++]=0x00;
   // c[i++]=0x00;
    //c[i++]=0x88;
    //c[i++]=0xbb;



    if( buf.count(c)>0)
    {
         NEWFile("Stop");//停止录像
         findClassAV("MP4",1);//删除.MP4
         ui->progressBar_2->setRange(0,10000);
         ui->progressBar_2->setVisible(true);  //false:隐藏进度条  true:显示进度条
         delay_ms(4000);
         NEWFile("Download");//下载视频
         //QFile::copy(runPath1+"/cmd/"+"Download",runPath1+"Download");


         for(int tt=0;tt<90000;tt++){
            ui->progressBar_2->setValue(tt);
            if(isFileExist(Sgopro("Download_OK")))
            {

                QString sath=findClassAV("MP4",0);
                qDebug()<<"::"<<sath;
                if(sath!=""){

                    QFile::rename(sath,runPath1+"tmp.MP4");
                }
                myslotsta=1;
                break;
            }
            delay_ms(10);
         }
        ui->progressBar_2->setVisible(false);
        ui->open->setText("录制");
        ui->open->setStyleSheet("color: rgb(255, 255, 255)");
        ui->open->setEnabled (true);

    }

    qDebug()<<"buf:"<<buf;
}

void MainWindow::on_pic_clicked()//转换
{
    QString fileName2 = "*";
    //QString text = s;
    QString fullFileName2;
    QString runPath = QCoreApplication::applicationDirPath();
    int first2 = runPath.lastIndexOf ("/");
    runPath=runPath.left(first2);
    QFile file2(runPath+"/Gopro/tmp.avi");
    if (file2.exists())
    {
        file2.remove();
    }
    {

        //ffmpeg -i tmp.MP4 -an -vcodec libx264 -crf 23 outfile.avi
        poc = new QProcess(this);
        //ffmpeg -i MV8.mp4 -c:v copy -an mmp.mp4
        //QString command = QString("D:/ffmpeg-bbezxcy-compressMode-0.0.1/bin/ffmpeg -i F:rawvideo/1.mp4 -pass 1 -y F:/rawvideo/1xxx1.mp4");

        QString command= runPath+"/ffmpeg/ffmpeg -i "+runPath+"/Gopro/tmp.MP4 -an -vcodec libx264 -crf 23 "+runPath+"/Gopro/tmp.avi";
        connect(poc, SIGNAL(readyReadStandardOutput()), this, SLOT(sltOnReadOutput()));
        connect(poc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));

        //poc->start("D://ffmpeg.bat");
        poc->setProcessChannelMode(QProcess::MergedChannels);
        poc->start(command);
        poc->waitForFinished();
    }



    QString path = runPath+"/tc";

    QDir currentDir = QDir(path);
    QStringList files = currentDir.entryList(QStringList(fileName2),
                                 QDir::Files | QDir::NoSymLinks);
    int tccount=files.size();
    qDebug()<<"::"<<tccount;
   // return;
       int Eventcuunt=0;
       VideoCapture cap;
       QString runPath3 = QCoreApplication::applicationDirPath();
       int first3 = runPath3.lastIndexOf ("/");
       runPath3=runPath3.left(first3)+"/Gopro/tmp.avi";
       cap.open(runPath3.toStdString()); //打开视频,以上两句等价于VideoCapture cap("E://2.avi");
       qDebug()<<"视频帧数："<<cap.get(7);//获取视频帧数
       int spzs=cap.get(7);//
       int FilmClip=0;
       QSettings Rtings("Setting.ini", QSettings::IniFormat);

       if(Rtings.contains("FrameRate/FilmClip"))
       {
           FilmClip = Rtings.value("FrameRate/FilmClip").toInt();
       }
       spzs=spzs-FilmClip;
       if(spzs<0)spzs=0;
       ui->progressBar->setRange(0,cap.get(7));//
       ui->progressBar->setValue(0);
       ui->progressBar->setVisible(true);  //false:隐藏进度条  true:显示进度条

       cv::Size sWH = cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT));
       VideoWriter outputVideo;
       //string outputVideoPath = "..\\out2.mp4";
       string outputVideoPath =  NewFileName().toStdString();
       qDebug()<<"fs:"<<cap.get(CV_CAP_PROP_FPS);
       outputVideo.open(outputVideoPath, CV_FOURCC('M', 'P', '4', 'v'), cap.get(CV_CAP_PROP_FPS), sWH);

        if(!cap.isOpened())//如果视频不能正常打开则返回
        {
            qDebug()<<"视频err";//
            return;

        }
        Mat frame;

        waitKey(30);
        double t = (double)cv::getTickCount();
        cv::namedWindow("Preview", CV_WINDOW_NORMAL);//CV_WINDOW_NORMAL就是 0
        int jd=0;
        int tcjs=0;
        QString fullFileName;
        QString runPath1 = QCoreApplication::applicationDirPath();
        int first = runPath1.lastIndexOf ("/");
        runPath1=runPath1.left(first);
        Mat pngtc[tccount];
        for(int i=0;i<tccount;i++){
            string runPath =runPath1.toStdString()+"/tc/tc"+QString::number(i).toStdString()+".png";
            qDebug()<<runPath.c_str();
            pngtc[i] = imread(runPath,-1);
        }
        //QMessageBox::information(this,"提示","1!");
        //while(cap.read(frame))
        int fcount=cap.get(7);
        mtime=((float)cap.get(7))/cap.get(CV_CAP_PROP_FPS);
        while(fcount--)
        {
            cap>>frame;
            Mat png=pngtc[tcjs];
            tcjs++;
            if(tcjs>=tccount){tcjs=0;}//切换照片

            if(jd>=spzs)break;
             //QMessageBox::information(this,"提示","2!");
            double T=(double)cv::getTickCount()-t;

            //qDebug()<< "time:"<<(T)*1000/(cv::getTickFrequency());
            t=(double)cv::getTickCount();

            if(frame.empty())//如果某帧为空则退出循环
            {
                //cv::destroyWindow("Preview");
                outputVideo.release();
                cap.release();
                 ui->progressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条
                // delay_ms(10);
                 qDebug()<< "time2:"<<fcount<<"2"<<(T)*1000/(cv::getTickFrequency());
                 continue;
                //QMessageBox::information(this,"提示","转换成功!22");
                 qDebug()<<"--->>>>>>";
                //return;
            }




            cv::resize(png,png,Size(frame.cols,frame.rows),0,0,INTER_LINEAR);

            double t1 = (double)cv::getTickCount();

            diejia(frame, png,1,0.9999999999,0,Point(0,0));

            T=(double)cv::getTickCount()-t1;
            qDebug()<< "time2:"<<fcount<<"2"<<(T)*1000/(cv::getTickFrequency());
            ui->progressBar->setValue(++jd);

            outputVideo << frame;


           imshow("Preview",frame);

           QRect WINXY=frameGeometry();
           cv::moveWindow("Preview",WINXY.x(),WINXY.y());
           cv::resizeWindow("Preview", 0,0);
           waitKey(1);




        }

        outputVideo.release();
        cap.release();
        if(myslotsta==1)
        QMessageBox::information(this,"提示","转换成功!");
        ui->progressBar->setVisible(false);  //false:隐藏进度条  true:显示进度条

}
void MainWindow::openCamara()//录制
{

    DEFile("Start");//Stop//Download//GoProOK//Downloading
    DEFile("Stop");
    DEFile("Download");
    DEFile("GoProOK");
    DEFile("Download_OK");
    DEFile("Downloading");
    NEWFile("Start");
    ui->open->setEnabled (false);
    //openCamaraB=1;
    //RCcount=0;
    ui->open->setText("录制中");
    ui->open->setStyleSheet("color: rgb(255, 0, 0)");
    char buf[20];
    int i=0;
    buf[i++]=0xaa;

    if(ui->PortBox_2->currentText()=="正转"){
        buf[i++]=0x01;
    }else{
        buf[i++]=0x02;
    }
    buf[i++]=ui->horizontalSlider->value();
    buf[i++]=(ui->horizontalSlider_2->value()/360.0)*140;
    buf[i++]=ui->lineEdit_2->text().toInt();
    buf[i++]=0x00;
    //buf[i++]=0x88;
    buf[i++]=buf[0]+buf[1]+buf[2]+buf[3]+buf[4]+buf[5];
    buf[i++]=0xbb;
    serial->write(buf,8);
    QSettings Rtings("Setting.ini", QSettings::IniFormat);
    int DELAY=1;
    if(Rtings.contains("FrameRate/DelayMs"))
    {
        QString DELAYStr = Rtings.value("FrameRate/DelayMs").toString();
        DELAY=DELAYStr.toInt();
        qDebug()<<DELAY;

    }
    delay_ms(DELAY);
}





void MainWindow::on_horizontalSlider_valueChanged(int value)
{

        QString str = QString("%1").arg(value);
        ui->pushButton_sdz->setText(str);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{

        QString str = QString("%1").arg(value);
        ui->pushButton_jdz->setText(str);
}


void MainWindow::GenerateQRcode(QString tempstr,QLabel *QR)
{
 QRcode *qrcode;
 if(tempstr.size()>4)
 tempstr.resize(tempstr.size()-4);
 qrcode=QRcode_encodeString(tempstr.toStdString().c_str(),2,QR_ECLEVEL_Q,QR_MODE_8,1);
 qint32 temp_width=QR->width();
 qint32 temp_height=QR->height();
 /*if(QR->width()>QR->height())
 {
        temp_height=temp_width;
 }else
 {
     temp_width=temp_height;
 }*/
 //qDebug()<<"temp_width="<<temp_width<<";temp_height="<<temp_height;
 qint32 qrcode_width=qrcode->width>0?qrcode->width:1;
 double scale_x=(double)temp_width/(double)qrcode_width;
 double scale_y=(double)temp_height/(double)qrcode_width;
 QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
 QPainter painter(&mainimg);
 QColor background(Qt::white);
 painter.setBrush(background);
 painter.setPen(Qt::NoPen);
 painter.drawRect(0,0,temp_width,temp_height);
 QColor foreground(Qt::black);
 painter.setBrush(foreground);
 for(qint32 y=0;y<qrcode_width;y++)
 {
     for(qint32 x=0;x<qrcode_width;x++)
     {
         unsigned char b=qrcode->data[y*qrcode_width+x];
         if(b &0x01)
         {
             QRectF r(x*scale_x,y*scale_y,scale_x,scale_y);
             painter.drawRects(&r,1);
         }
     }
 }

QPixmap mainmap=QPixmap::fromImage(mainimg);
QR->setPixmap(mainmap);
QR->setVisible(true);
}
QDir currentDir;
QString MainWindow::findFiles(const QStringList &files, const QString &text)
{



    QString foundFiles="";

    for (int i = 0; i < files.size(); i++) {
        //qDebug()<<":"<<files[i];
        if(files[i].indexOf(text)!=-1){
            foundFiles=files[i];
        }
    }
    return foundFiles;
}
QString MainWindow::findClassf(QString s,int sta)
{

    QString fileName = "*";
    QString text = s;
    QString fullFileName;
    QString runPath = QCoreApplication::applicationDirPath();
    int first = runPath.lastIndexOf ("/");
     //qDebug()<<runPath;
    runPath=runPath.left(first);
    QString path = runPath;

     currentDir = QDir(path);
    QStringList files;
    if (fileName.isEmpty()){

            fileName = "*";
        }
    files = currentDir.entryList(QStringList(fileName),
                                 QDir::Files | QDir::NoSymLinks);
    if(sta==1){//删除.MP4

        for (int i = 0; i < files.size(); i++) {
            //qDebug()<<":"<<runPath+"/"+files[i];
            if(files[i].indexOf(text)!=-1){
                    //qDebug()<<"2:"<<runPath+"/"+files[i];
                QFile file(runPath+"/"+files[i]);
                if (file.exists())
                {
                    file.remove();
                }

            }
        }
        return "";
    }

    QString path2;
    if (!text.isEmpty())
        path2 = findFiles(files, text);
    //showFiles(files);
    if(path2.isEmpty())
    {
        return "";
    }
    return runPath+"/"+path2;
}
QString MainWindow::findClassAV(QString s,int sta)
{

    QString fileName = "*";
    QString text = s;
    QString fullFileName;
    QString runPath = QCoreApplication::applicationDirPath();
    int first = runPath.lastIndexOf ("/");
     //qDebug()<<runPath;
    runPath=runPath.left(first)+"/Gopro";
    QString path = runPath;

     currentDir = QDir(path);
    QStringList files;
    if (fileName.isEmpty()){

            fileName = "*";
        }
    files = currentDir.entryList(QStringList(fileName),
                                 QDir::Files | QDir::NoSymLinks);
    if(sta==1){//删除.MP4

        for (int i = 0; i < files.size(); i++) {
            //qDebug()<<":"<<runPath+"/"+files[i];
            if(files[i].indexOf(text)!=-1){
                    //qDebug()<<"2:"<<runPath+"/"+files[i];
                QFile file(runPath+"/"+files[i]);
                if (file.exists())
                {
                    file.remove();
                }

            }
        }
        return "";
    }

    QString path2;
    if (!text.isEmpty())
        path2 = findFiles(files, text);
    //showFiles(files);
    if(path2.isEmpty())
    {
        return "";
    }
    return runPath+"/"+path2;
}
//2. 判断文件是不是存在
//参数说明：
//QString fullFileName;//文件全路径(包含文件名)
//方法1
bool isFileExist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}
QString NewFileName()
{
    int count=0;
    QString fullFileName;
    QString runPath = QCoreApplication::applicationDirPath();
    int first = runPath.lastIndexOf ("/");
     //qDebug()<<runPath;
    runPath=runPath.left(first);
    //qDebug()<<runPath;
    for(count=0;count<10000;count++)
    {
        fullFileName=runPath+"/MV"+QString::number(count)+".mp4";
         //qDebug()<<fullFileName;
        if(!isFileExist(fullFileName))
        {
            goto END;
        }
        fullFileName="";

    }
END:
    return fullFileName;
}
QString NewFileName2()
{
    int count=0;
    QString fullFileName;
    QString runPath = QCoreApplication::applicationDirPath();
    int first = runPath.lastIndexOf ("/");
     //qDebug()<<runPath;
    runPath=runPath.left(first);
    //qDebug()<<runPath;
    for(count=0;count<10000;count++)
    {
        //int uuu=(count-1);
        fullFileName=runPath+"/MV"+QString::number(count-1)+".mp4";
         //qDebug()<<fullFileName;
        if(!isFileExist(runPath+"/MV"+QString::number(count)+".mp4"))
        {
            goto END;
        }
        fullFileName="";

    }
END:
    return fullFileName;
}
void FineName(QString *s,int &n,int mode)//最多寻找倒数的n个文件名，返回文件名和符合个数
{
    int count=0;
    int nc=0,N=n;
    n=nc;
    QString fullFileName;
    QString runPath = QCoreApplication::applicationDirPath();
    int first = runPath.lastIndexOf ("/");
     //qDebug()<<runPath;
    runPath=runPath.left(first);
    QSettings Rtings("Setting.ini", QSettings::IniFormat);
    QString QrCodeuLStr="";
    if(Rtings.contains("FrameRate/QrCodeuL"))
    {
        QrCodeuLStr = Rtings.value("FrameRate/QrCodeuL").toString();

        //qDebug()<<QrCodeuLStr;

    }
    //qDebug()<<runPath;
    for(count=10000-1;count>=0;count--)
    {
        fullFileName=runPath+"/MV"+QString::number(count)+".mp4";
         //qDebug()<<fullFileName;
        if(isFileExist(fullFileName))
        {
            if(nc<N)
            {
                if(mode ==0)
                {
                    s[nc++]=QrCodeuLStr+"MV"+QString::number(count)+".mp4";
                }else if(mode == 1){
                    s[nc++]=fullFileName;
                }
                n=nc;

            }
            else
            {
                return;
            }
        }

    }
}
void MainWindow::on_pushButton_3_clicked()//QR1预览
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[0].isEmpty()){

        player->setMedia(QUrl(s[0]));
        qDebug()<<QUrl(s[0]);
        videoWidget->setGeometry(ui->label->x(),ui->label->y(),ui->label->width(),ui->label->height());
        videoWidget->setWindowFlags(Qt::FramelessWindowHint);
        videoWidget->show();
        player->play();
    }


}
void MainWindow::on_pushButton_4_clicked()//QR1删除
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[0].isEmpty()){

            QFile file(s[0]);
            if (file.exists())
            {
                file.remove();
            }
    }
}


void MainWindow::on_pushButton_5_clicked()//QR2预览
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[1].isEmpty()){

        player->setMedia(QUrl(s[1]));
        qDebug()<<QUrl(s[1]);
        videoWidget->setGeometry(ui->label->x(),ui->label->y(),ui->label->width(),ui->label->height());
        videoWidget->setWindowFlags(Qt::FramelessWindowHint);
        videoWidget->show();
        player->play();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[1].isEmpty()){

            QFile file(s[1]);
            if (file.exists())
            {
                file.remove();
            }
    }
}

void MainWindow::on_pushButton_7_clicked()//QR3预览
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[2].isEmpty()){

        player->setMedia(QUrl(s[2]));
        qDebug()<<QUrl(s[2]);
        videoWidget->setGeometry(ui->label->x(),ui->label->y(),ui->label->width(),ui->label->height());
        videoWidget->setWindowFlags(Qt::FramelessWindowHint);
        videoWidget->show();
        player->play();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QString s[3]={""};
    int n=3;
    FineName(s,n,1);
    if(!s[2].isEmpty()){

            QFile file(s[2]);
            if (file.exists())
            {
                file.remove();
            }
    }
}
QString MainWindow::fileadd(){
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("*.bin"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    QString t;
    for(auto tmp:fileNames)
    {
         qDebug()<<tmp<<endl;
         t=tmp;
         //ui->lineEdit->setText(tmp);
    }
    return  t;
}
void MainWindow::on_pushButton_9_clicked()
{
       QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
       QScreen *screen = QGuiApplication::primaryScreen();
       screen->grabWindow(ui->QR1->winId()).save(filename1);

}

void MainWindow::on_pushButton_10_clicked()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->QR2->winId()).save(filename1);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->QR3->winId()).save(filename1);
}



void MainWindow::on_pushButton_dz1_clicked()
{
        QString filename = QFileDialog::getOpenFileName(this,tr("选择视频文件"),"",tr("Images (*.mp4)")); //选择路径
        ui->lineEdit_3->setText(filename);

}

void MainWindow::on_pushButton_dz1_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("选择视频文件"),"",tr("Images (*.mp3)")); //选择路径
    ui->lineEdit_4->setText(filename);
}

void MainWindow::on_pushButton_12_clicked()
{

        QString fullFileName;
        QString runPath = QCoreApplication::applicationDirPath();
        int first = runPath.lastIndexOf ("/");
        runPath=runPath.left(first);

        QFile file(runPath+"/ffmpeg/ttx.mp4");
        if (file.exists())
        {
            file.remove();
        }

        poc = new QProcess(this);
        //ffmpeg -i MV8.mp4 -c:v copy -an mmp.mp4
        //QString command = QString("D:/ffmpeg-bbezxcy-compressMode-0.0.1/bin/ffmpeg -i F:rawvideo/1.mp4 -pass 1 -y F:/rawvideo/1xxx1.mp4");
        QString sjkaj=NewFileName2();
        if(sjkaj.isEmpty()){
            QMessageBox::information(this,"提示","生成新视频失败!");
            return;
        }
        QString command= runPath+"/ffmpeg/ffmpeg -i "+sjkaj+" -c:v copy -an "+runPath+"/ffmpeg/ttx.mp4";

        connect(poc, SIGNAL(readyReadStandardOutput()), this, SLOT(sltOnReadOutput()));
        connect(poc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));

        //poc->start("D://ffmpeg.bat");
        poc->setProcessChannelMode(QProcess::MergedChannels);
        poc->start(command);
        poc->waitForFinished();
        //ffmpeg -i mmp.mp4 -i 11197.mp3 -t 25 -y o.mp4
        fullFileName=NewFileName();
        if(fullFileName.isEmpty()){
            QMessageBox::information(this,"提示","生成新视频失败!");
            return;
        }
        //ffmpeg -i /Users/mac/Desktop/Video/797.mp4 -i /Users/mac/Desktop/Video/152.mp3 -filter_complex "[0:v]copy [vout];[0:a]volume=volume=0 [aout0];[1:a]volume=volume=1 [aout1];[aout1]aloop=loop=-1:size=2e+09,atrim=0:43[aconcat]; [aout0][aconcat]amix=inputs=2:duration=longest:dropout_transition=0 [aout]" -map [vout] -map [aout] -y /Users/mac/Desktop/Video/mixVideo.mp4
        //-filter_complex "[0:v]copy [vout];[0:a]volume=volume=0 [aout0];[1:a]volume=volume=1 [aout1];[aout1]aloop=loop=-1:size=2e+09,atrim=0:43[aconcat]; [aout0][aconcat]amix=inputs=2:duration=longest:dropout_transition=0 [aout]" -map [vout] -map [aout]
        if(ui->lineEdit_4->text().isEmpty()){
            command= runPath+"/ffmpeg/ffmpeg -i "+runPath+"/ffmpeg/ttx.mp4"+" -i "+runPath+"/AudioVideo/m.mp3 -t "+QString::number(mtime)+" -y " +fullFileName;

        }else{
            command= runPath+"/ffmpeg/ffmpeg -i "+runPath+"/ffmpeg/ttx.mp4"+" -i "+ui->lineEdit_4->text()+" -t "+QString::number(mtime)+" -y " +fullFileName;
        }

        //String t
        /*String tcommand= runPath.toStdString()+"/ffmpeg/ffmpeg -i "+runPath.toStdString()+"/ffmpeg/ttx.mp4"+" -i "+runPath.toStdString()+"/AudioVideo/m.mp3"+
                " -filter_complex \"[0:v]copy [vout];[0:a]volume=volume=0 [aout0];[1:a]volume=volume=1 [aout1];[aout1]aloop=loop=-1:size=2e+09,atrim=0:43[aconcat]; [aout0][aconcat]amix=inputs=2:duration=longest:dropout_transition=0 [aout]\" -map [vout] -map [aout] -y " +fullFileName.toStdString();
        command=QString::fromStdString(tcommand);*/
        qDebug("--------------\n%s",command.toLocal8Bit().data());
         //          QMessageBox::information(this,"提示","1!");

        connect(poc, SIGNAL(readyReadStandardOutput()), this, SLOT(sltOnReadOutput()));
        connect(poc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));

        //poc->start("D://ffmpeg.bat");
        poc->setProcessChannelMode(QProcess::MergedChannels);
        poc->start(command);
        poc->waitForFinished();
        QMessageBox::information(this,"提示","合并成功!");

}
void MainWindow::sltOnReadOutput(){
    QString s = poc->readAllStandardOutput();
    ui->label_3->setText(s);
    qDebug()<<"11---------"<<s;
}
