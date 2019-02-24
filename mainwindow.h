#include <QtWidgets/QMainWindow>

#include <QImage>
#include <QTimer>     // 设置采集数据的间隔时间
#include <opencv.hpp>
#include "ui_mainwindow.h"
#include <highgui.h>  //包含opencv库头文件
#include <cv.h>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

#include <QFileDialog>
using namespace cv;
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bj();
    void GenerateQRcode(QString tempstr);//
    void GenerateQRcode(QString tempstr,QLabel *QR);

public slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照
    void serialRead_Data();


private slots:
    void on_pushButton_clicked();

    void on_pic_clicked();

    void on_pushButton_2_clicked();

    void handleTimeout();  //超时处理函数



    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();



    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    QString fileadd();
    void NEWFile(QString s);
    void DEFile(QString s);
    QString Sgopro(QString s);
    QString findClassAV(QString s,int i);
    QString findFiles(const QStringList &files, const QString &text);
private slots:
    void myslot();
    void myslot2();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();



private:


    VideoCapture capture;//创建一个摄像头对象并且指定摄像头编号，只有一个写0就可以

    Ui::MainWindow *ui;

    void resizeEvent(QResizeEvent * event);
    void closeEvent( QCloseEvent * event );
     QTimer *m_pTimer;

     QMediaPlayer *player;
     QVideoWidget *videoWidget;


};
