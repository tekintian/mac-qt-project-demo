# c++ demo project with mac qt

最简单的 qt c++项目!!!



## 开发环境: 
Mac 10.15.7
Qt 5.9.9
c++ 
c



## 目录说明

- bin 为项目编译后的 Mac应用程序

- src 为项目源文件



## 头文件说明

```
#include <QFileDialog>   QT弹窗对象
#include <QString>      QT字符串对象
#include <QTextCodec>   QT文本编码对象
#include <QDebug>       QT调试对象
#include <string.h>    C字符串处理库
```



- 通过对话框获取文件路径指针

  ~~~cpp
  //通过对话框打开文件,获取打开的文件路径 QString类型
  QString fileName=QFileDialog::getOpenFileName();
  // 转码  这里需要注意根据你的系统编码类型设置, Mac linux系统一般为 UTF8, 中文windows系统默认 GBK
  QTextCodec * codec = QTextCodec::codecForName("UTF8");
  char *pfile = codec->fromUnicode(fileName).data(); // 获取文件路径指针
  ~~~



- 将QString类型与 char * 指针类型互转
  ~~~cpp
  // 创建QTexeCodec转换器,  这里注意编码,如果编码选择不对将无法打开, 中文windows默认是 GBK , 本机默认编码UTF8
  QTextCodec *codec = QTextCodec::codecForName("UTF8");
  //将QString转换为 char * 类型
  char *file = codec->fromUnicode(fileName).data();

  // 定义一个1024字节的缓存 buf
  //char buf[1024];

  // 将buf转换为QString对象
  QString txt = codec->toUnicode(buf);
  ~~~



- 从qt文本框中获取字节数组指针buf

  ~~~cpp
    // 读取输入框textEdit的内容
      QString txt = ui->textEdit->toPlainText();
      const char *buf = txt.toStdString().data();
  ~~~

  





C++构造函数:  类名::类名

~~~cpp
// MainWindow 类构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
~~~



c++析构函数: 类名::~类名   

~~~cpp
// MainWindow析构函数 ~
MainWindow::~MainWindow()
{
    delete ui;
}
~~~



C++方法:  类名::方法名



在类中自定义方法, 需要现在 类的头文件 类名.h 的 slots中定义函数, 然后在类文件中实现, 如:

mainwindow.h

~~~h
private slots:
		// 定义函数
    void saveFile(QString fileName, const char *buf);
    // ......
~~~



mainwindow.cpp

~~~cpp
/**
 * @brief 自定义的保存文件的函数
 * @param fileName 文件名
 * @param buf 要保存的字符指针
 */
void MainWindow::saveFile(QString fileName, const char *buf)
{
    // 转码
    QTextCodec * codec = QTextCodec::codecForName("UTF8");
    char *pfile = codec->fromUnicode(fileName).data();
    // 打开文件
    FILE * fp = fopen(pfile,"w");

    if(!fp)
        return;

    fputs(buf,fp);

    fclose(fp);

}
~~~



