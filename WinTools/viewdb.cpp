#include "viewdb.h"
#include "ui_viewdb.h"
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "ui_defind.h"

#define VDB_EOF -1

typedef struct {
    int index;
    const char* name;
    const char* condition_sql;
} SLIST_CHECK;

typedef struct {
    int index;
    const char* name;
    SLIST_CHECK* condition;
    const char* sql;
} SLIST_TB;

// 查询人脸表的条件
static SLIST_CHECK face_con[] = {
    {0, "无条件", NULL},
    {1, "可识别人脸", NULL},
    {2, "不能识别人脸", NULL},
    {3, "无权限", NULL},
    {VDB_EOF, 0, 0}
};
static int map_ck[] = {0,1,2,3};

static SLIST_TB stbs[] = {
    {0, "选择操作", 0, 0},  // 这个没有操作意义
    {1, "人脸查询", NULL, NULL},    // 查询人脸表
    {2, "权限查询", NULL, NULL},    // 查询权限表
    {3, "临时权限查询", NULL, NULL},  // 查询临时权限表
    {4, "查询基本参数", NULL, NULL},  // 查询基本参数
    {VDB_EOF, 0, 0, 0}
};
// 选择下拉框的时候根据index，选择到对应的tb
static int map_tb[] = {0,1,2,3,4};

// 定义标准的查询数据库接口
typedef struct {

} TB_CHECK_LIST;

ViewDb::ViewDb(QWidget *parent, const QString &dbname, int devtyp) :
    QDialog(parent),
    ui(new Ui::ViewDb)
{
    ui->setupUi(this);
    setWindowTitle(tr("设备数据查询"));

    // 初始化一些字符串，主要是对于不同的设备，访问的数据库字段有区别
    InitSql(0xff&devtyp, devtyp);

    ui->s_tb->addItem(stbs[0].name);
    map_tb[0] = 0;
    for (int i=1,j=1;;i++)
    {
        if (VDB_EOF==stbs[i].index)
            break;
        if (NULL==stbs[i].sql)
            continue ;
        ui->s_tb->addItem(stbs[i].name);
        map_tb[j++] = i;
    }
    ui->s_tb->setItemData(0, 0, Qt::UserRole - 1);

#if 1
    // 如果有选项，选择第一个有效选项
    stbs_select = 0;
    stbs_index = map_tb[stbs_select];
    if (ui->s_tb->count()<=1)
        return ;

    stbs_select = 1;
    stbs_index = map_tb[stbs_select];
    ui->s_tb->setCurrentIndex(1);
#endif

    // 以下是有有效查询命令，那么打开数据库，并执行第1个有效指令，展示表格内容
    // 打开数据库
    qDebug() << "open db";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(QCoreApplication::applicationDirPath()+"\\file\\"+dbname);
    if (!m_db.open())
    {
        qDebug() << "open db error";
        return ;
    }

    // 初始化表格模型
    m_model = new QSqlQueryModel(this);
}

ViewDb::~ViewDb()
{
    qDebug() << "release ViewDb";

    delete m_model;

    if (m_db.isOpen())
        m_db.close();
    delete ui;
}

void ViewDb::closeEvent(QCloseEvent *event)
{
    qDebug() << "close ViewDb";
    deleteLater();
}

void ViewDb::InitSql(int devtype, int dev)
{
    qDebug() << devtype << " " << dev;
    printf("<< 0x%x 0x%x\n", devtype, dev);
    // 主要是添加查询数据库的sql，和查询条件，
    // 先检查设备类型，如果还需要平台补充，就需要处理2次
    switch (devtype) {
    case SUP_DEV_DCTR_YT328:
    case SUP_DEV_DCTR_YT327L:
        // 修改stbs每个元素的 condition 和 sql
        stbs[1].condition = face_con;
        stbs[2].condition = NULL;
        stbs[3].condition = NULL;
        stbs[4].condition = NULL;

        stbs[1].sql = "select accname,cardno,accnum,state,authstate,tmpauthstate,facestate from face_img_info";
        stbs[2].sql = NULL;
        stbs[3].sql = NULL;
        stbs[4].sql = "select * from LocalInfo";

        // 如果有条件，修改条件啊
        face_con[1].condition_sql = "where state='0'";
        face_con[2].condition_sql = "where state!='0'";
        face_con[3].condition_sql = "where authstate='0'";
        break;
    default:
        stbs[1].condition = NULL;
        stbs[2].condition = NULL;
        stbs[3].condition = NULL;

        stbs[1].sql = NULL;
        stbs[2].sql = NULL;
        stbs[3].sql = NULL;
        break;
    }
}

void ViewDb::on_s_tb_currentIndexChanged(int index)
{
    qDebug() << "on_s_tb_currentIndexChanged " << index;

    stbs_select = index;
    stbs_index = map_tb[stbs_select];

    if (nullptr==stbs[stbs_index].condition || nullptr==stbs[stbs_index].sql)
    {
        ui->s_condition->hide();
        ui->s_condition->clear();
        // 没有选择条件，使用无条件
        condition_index = 0;
        return ;
    }

    // 显示条件，并清掉之前的选项
    ui->s_condition->show();
    ui->s_condition->clear();

    SLIST_CHECK* ck = stbs[stbs_index].condition;
    // 无条件必须要加
    ui->s_condition->addItem(ck[0].name);
    map_ck[0] = 0;
    for (int i=1,j=1;;i++)
    {
        if (VDB_EOF==ck[i].index)
            break;
        if (nullptr==ck[i].condition_sql)
            continue;
        ui->s_condition->addItem(ck[i].name);
        map_ck[j++] = i;
    }

    // 默认选择第一项条件
    condition_select = 0;
    condition_index = map_ck[condition_select];
}

void ViewDb::on_bt_check_clicked()
{
    // 点击按键，根据选择的查询语句和条件情况，查询数据库
    // 获取数据
    QString sql;
    sql.append(stbs[stbs_index].sql).append(" ");
    qDebug() << "condition_index " << condition_index;
    if (stbs[stbs_index].condition&&condition_index)
        sql.append(stbs[stbs_index].condition[condition_index].condition_sql);

    qDebug() << "exec sql: " << sql;
    m_model->setQuery(sql);
    // 设置数据到表格
    ui->tableView->setModel(m_model);
}

void ViewDb::on_bt_export_clicked()
{

}

void ViewDb::on_s_condition_currentIndexChanged(int index)
{
    qDebug() << "on_s_condition_currentIndexChanged " << index;
    condition_select = index;
    condition_index = map_ck[condition_select];
}
