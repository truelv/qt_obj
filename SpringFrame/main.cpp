#include "mainwindow.h"
#include "springframe.h"
#include <QApplication>
#include <QTextCodec>
#include <QObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SpringFrame* v = new SpringFrame(0,SF_LINETEXT, 10,100,500,300);
    v->setFrameStyle("border-image:url(/data/zytk_reader/img/title_dialog_background.png);");
    v->setButtonStyle("background-color:rgb(29,50,163,254);font-size:45px;color:white");
    SFLineText* iLine = (SFLineText*)v->getUiOpt();
    iLine->setLineTextStyle("font-size:45px;");
    v->show();
#if 0
    SpringFrame* v2 = new SpringFrame(0,SF_INPUTLINE, 10,900,500,300);
    v2->setFrameStyle("border-radius:20px;background-color:rgb(29,50,163,254);");
    v2->setButtonStyle("background-color:rgb(0,0,255);font-size:45px;color:white");
    SFInputLine* iInput = (SFInputLine*)v2->getUiOpt();
    iInput->setLabelStyle("font-size:45px;color:white");
    iInput->setLabelText(QObject::tr("输入密码"));
    QString pass;
    iInput->setInputText("12345");
    // 绑定返回值
    iInput->bindInputRetval(&pass);
    v2->exec();
    qDebug() << "xxxxxxxx" << pass;
#endif

#if 1
    SpringFrame* v1 = new SpringFrame(0,SF_485ERR, 0,0,720,1280);
    v1->hideButton(false);
    v1->setFrameStyle("background-color:rgb(255,255,255);");
    SF485Error* err485 = (SF485Error*)v1->getUiOpt();
    err485->setLabelStyle("border-image:url(/root/errlabel.png)");
    err485->setTitleStyle("font-size:50px;color:rgb(92,94,134,254)");
    err485->setContentStyle("font-size:35px;color:rgb(92,94,134,254)");
    err485->setContentText(QObject::tr("• 485连线是否正确\n• 模式配置及ID配置是否正确\n• 查看控制器版本是否高于21.1030"));
    v1->show();

#endif
    return a.exec();
}
