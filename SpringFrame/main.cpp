#include "mainwindow.h"
#include "springframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SpringFrame* v = new SpringFrame(0,LINE_TEXT, 10,100,500,300);
    v->setFrameStyle("border-image:url(/data/zytk_reader/img/title_dialog_background.png);");
    v->setButtonStyle("background-color:rgb(29,50,163,254);font-size:45px;color:white");
    v->getUiOpt()->setLineTextStyle("font-size:45px;");
    v->show();
#if 1
    SpringFrame* v1 = new SpringFrame(0,LINE_TEXT, 10,500,500,300);
    v1->hideButton(false);
    v1->setFrameStyle("border-radius:20px;background-color:rgb(29,50,163,254);");
    v1->getUiOpt()->setLineTextStyle("font-size:45px;color:white");
    //v1->showTimeOut(EV_DIALOG_HIDE, 5);
    v1->showTimeOut(EV_DIALOG_EXIT, 5);

#endif
#if 1
    SpringFrame* v2 = new SpringFrame(0,INPUT_LINE, 10,900,500,300);
    v2->setFrameStyle("border-radius:20px;background-color:rgb(29,50,163,254);");
    v2->setButtonStyle("background-color:rgb(0,0,255);font-size:45px;color:white");
    SpringFrame::InputLine* iline = (SpringFrame::InputLine*)v2->getUiOpt();
    v2->show();
#endif
    return a.exec();
}
