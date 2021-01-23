#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include <QDebug>


//定义一个宏文件用于打印日志
#define cout qDebug()

// 定义一个全局变量
QString fileName=NULL;

//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//析构函数 ~
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 打开文件
 */
void MainWindow::on_actionOpen_triggered()
{
    //打开文件
    /*
     * 1. fopen打开文件
     * 2. 判断可用性
     * 3. 读取内容
     * 4. 关闭
     */
    //通过对话框打开文件,获取文件路径 QString类型
    fileName=QFileDialog::getOpenFileName();
    //cout<<"======"<<fileName<<"====";
    // 创建QTexeCodec转换器,  这里注意编码,如果编码选择不对将无法打开, 中文windows默认是 GBK , 本机默认编码UTF8
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    //将QString转换为 char * 类型
    char *file = codec->fromUnicode(fileName).data();

    FILE *fp = fopen(file,"r");
    if(!fp)
        return;
   cout<<"文件打开成功"<<endl;

    // 定义一个1024字节的缓存 buf
    char buf[1024];

    // 什么QString对象 txt
    QString txt;

    // 循环读取文件
    while(!feof(fp))
    {
        // 申请1024个字节的内存并初始化为0
       memset(buf,0,1024);
       // 读取文件
       fgets(buf,1024,fp);

       cout<<buf;
       txt += codec->toUnicode(buf);

       ui->textEdit->setText(txt);
    }
    //关闭文件
    fclose(fp);

    cout<<"文件打开成功";

}
/**
 * @brief 保存
 */
void MainWindow::on_actionSave_triggered()
{

   // 如果文件名不为空,则弹出对话框
   if(NULL == fileName){
       // 对话框保存文件名
      fileName =QFileDialog::getSaveFileName();
    }
   // 转码
   QTextCodec * codec = QTextCodec::codecForName("UTF8");
   char *pfile = codec->fromUnicode(fileName).data();
   // 打开文件
   FILE * fp = fopen(pfile,"w");

   if(!fp)
       return;

    // 读取输入框textEdit的内容
    QString txt = ui->textEdit->toPlainText();

    const char *buf = txt.toStdString().data();
    fputs(buf,fp);
    fclose(fp);
}
/**
 * @brief 另存为对话框
 */
void MainWindow::on_actionSave_As_triggered()
{
    // 对话框保存文件名
   fileName =QFileDialog::getSaveFileName();
    // 转码
    QTextCodec * codec = QTextCodec::codecForName("UTF8");
    char *pfile = codec->fromUnicode(fileName).data();
    // 打开文件
    FILE * fp = fopen(pfile,"w");

    if(!fp)
        return;
    // 读取输入框textEdit的内容
    QString txt = ui->textEdit->toPlainText();

    const char *buf = txt.toStdString().data();
    fputs(buf,fp);
    fclose(fp);
}

/**
 * @brief 新建
 */
void MainWindow::on_actionnew_triggered()
{
    ui->textEdit->clear();
    // 新建文件时清除原来的文件名
    fileName.clear();
}
/**
 * @brief 取消
 */
void MainWindow::on_actioncancel_triggered()
{
    ui->textEdit->undo();
}
/**
 * @brief 拷贝
 */
void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}
/**
 * @brief 剪切
 */
void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}
/**
 * @brief 粘贴
 */
void MainWindow::on_actionpase_triggered()
{
    ui->textEdit->paste();
}

/**
 * @brief 退出
 */
void MainWindow::on_actionExit_triggered()
{
    exit(EXIT_SUCCESS);
}
