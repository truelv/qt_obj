/**
 * 管理界面使用的统一的背景窗口
 */
#include "managerbkview.h"
#include "ui_managerbkview.h"
#include "global.h"

#undef LOG_TAG
#define LOG_TAG "ui_manager_bk"
ManagerBkView* ManagerBkView::_intent = NULL;
/**
 * 构造函数
 * @brief ManagerBkView::ManagerBkView
 * @param parent
 */
ManagerBkView::ManagerBkView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerBkView)
{
    ui->setupUi(this);
    // 隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置背景窗口背景图片
    ui->wframe->setStyleSheet(QString("#wframe {border-image: url(%1/background_pic.png);}")
                              .arg(UI_IMG_DIR));
    // 创建垂直分布layout，放显示窗口
    _layout = new QVBoxLayout(ui->wframe);
    _w = NULL;
    this->showMaximized();
}
/**
 * 析构函数
 * @brief ManagerBkView::~ManagerBkView
 */
ManagerBkView::~ManagerBkView()
{
    if (NULL!=_w) {
        delete _w;
    }
    delete _layout;
    delete ui;
    _intent = NULL;
}

ManagerBkView *ManagerBkView::getInstance()
{
    if (NULL==_intent)
        _intent = new ManagerBkView;

    return _intent;
}
/**
 * 添加具体的显示子窗口
 * @brief ManagerBkView::addWidgetShow
 * @param w
 */
void ManagerBkView::addWidgetShow(QWidget *w)
{
    if (NULL==w) {
        LOG_E("参数为空，添加显示窗口失败");
        return;
    }
    w->setParent(this);
    // 如果layout已经添加窗口，先移除
    if (NULL!=_w) {
        _layout->removeWidget(_w);
    }
    _layout->addWidget(w);
    _w = w;
}
