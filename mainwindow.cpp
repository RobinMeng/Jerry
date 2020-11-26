#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectdb.h"
#include <QAction>
#include <QDebug>
#include <QList>
#include <QTreeWidgetItem>
#include <qxmlutils.h>
#include <qjerrysqllite.h>
#include <QTextEdit>
#include <QToolButton>
#include <QSizePolicy>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->UiDefault();
    this->DbInit();

    void (QAction:: * triggered) (bool)= &QAction::triggered;

    connect(ui->actionnew,triggered,this,[&](){
      ConnectDB *dbUi= new ConnectDB();
      connect(dbUi,SIGNAL(updateUi()),this,SLOT(reshDbUI()));
      dbUi->show();
    });

    connect(this->ui->tabWidget,SIGNAL(tabCloseRequested (int)),this,SLOT(closeTab(int)));
}


void MainWindow::UiDefault(){

    ui->splitter->setHandleWidth(1);
    ui->splitter->setStretchFactor(1,3);

    ui->tabWidget->clear();

    this->ui->tabWidget->setTabsClosable(true);

    //table 构建
//    QWidget *page =new QWidget();
//    const QIcon *objIcon  = new QIcon(":/icon/img/obj.svg");
//    ui->tabWidget->addTab(page,*objIcon,QString("对象"));

}

void MainWindow ::DbInit(){
    QJerrySqlLite sqlLiet;
    sqlLiet.initTable();
    sqlLiet.connectDB();
    //sqlLiet.execSQl(new QString("delete from account"));

    const QIcon &icon  = QIcon(":/icon/img/db.svg");

    QTreeWidgetItem  *treeWidgetHead=new QTreeWidgetItem();

    treeWidgetHead->setIcon(0, icon);
    treeWidgetHead->setText(0,"数据库");
    this->ui->treeWidget ->setHeaderItem(treeWidgetHead);
    QList<QMap<QString,QString>>list= sqlLiet.queryData(new QString("select * from account"));

    for(int i=0;i<list.size();i++){
        QMap<QString,QString>map=list.at(i);
        map.insert("type","1");
        QTreeWidgetItem *item=new QTreeWidgetItem(this->ui->treeWidget,QStringList() << map.value("dbname"));
        item->setIcon(0,icon);
        item->setData(0,Qt::UserRole,QVariant::fromValue(map));
    }

    connect(this->ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showTables(QTreeWidgetItem*,int)));

}


void MainWindow::reshDbUI(){
    this->ui->treeWidget->clear();
    this->DbInit();
}

/**
 * type 1  机器
 * type 2  数据库
 *
 * @brief MainWindow::showTables
 * @param item
 * @param index
 */
void MainWindow::showTables(QTreeWidgetItem  * item,int index){
    qDebug()<<"树双击" << index << item->text(index);
    QMap<QString,QString> map=item->data(0,Qt::UserRole).value<QMap<QString,QString>>();
    QString type=map.value("type");
    QString url=map.value("url");
    QString name=map.value("name");
    QString pwd= map.value("password");
    QString port=map.value("port");
    QString dbName=map.value("dbname");

    ConnectDB conn;
    QString *sql;
    if(type.compare(QString::fromLocal8Bit("1"))==0){
        mySqlDataBase =*conn.connect2DB(new QSqlDatabase(),&url,&name,&pwd,port.toInt(),&dbName);
        sql=new QString("show databases");

        QList<QMap<QString,QString>>*listData= conn.queryData(&mySqlDataBase,sql);
        const QIcon &icon  = QIcon(":/icon/img/db.svg");
        for(int i=0;i<listData->length();i++){
            QMap<QString,QString>map=listData->at(i);
            map.insert("type","2");
            QTreeWidgetItem *childItem=new QTreeWidgetItem(item,QStringList() << map.value("Database"));
            childItem->setIcon(0,icon);
            childItem->setData(0,Qt::UserRole,QVariant::fromValue(map));
        }
    }else if (type.compare(QString::fromLocal8Bit("2"))==0) {
        QString useSQl("use ");
        useSQl.append(item->text(0));
        qDebug()<<useSQl;
        conn.exec(&mySqlDataBase,&useSQl);

        sql=new QString("show tables");
        QList<QMap<QString,QString>>*listData= conn.queryData(&mySqlDataBase,sql);
        qDebug()<<"listData"<< listData;

        // tab 选项卡布局开始

        QWidget *tablePage =new QWidget();
        QVBoxLayout *layout = new QVBoxLayout;
        QListWidget *listWidget=new QListWidget();
        layout->addWidget(listWidget);
        tablePage->setLayout(layout);
        const QIcon *objIcon  = new QIcon(":/icon/img/obj.svg");
        ui->tabWidget->addTab(tablePage,*objIcon,QString("对象").append("-").append(item->text(0)));


        // tab 选项卡布局结束


        const QIcon *tableIcon  = new QIcon(":/icon/img/table.svg");
        for(int i=0;i<listData->length();i++){
            QMap<QString,QString>map=listData->at(i);
            for (auto iter = map.begin(); iter != map.end(); ++iter)
            {
                QString key = iter.key();
                QString value = iter.value();
                qDebug() << key << value;
                QTreeWidgetItem *tableItem=new QTreeWidgetItem(item,QStringList() << value);
                tableItem->setIcon(0,*tableIcon);

                // 表结构
                QListWidgetItem *listWidgetItem=new QListWidgetItem(*tableIcon,QString(value));
                listWidget->addItem(listWidgetItem);
            }
        }
    }
}

void MainWindow::closeTab(int index){

    qDebug()<<"current Index:" << index;
    this->ui->tabWidget->removeTab(index);
}

/**
 * 新建查询槽函数
 */
void MainWindow::on_actionnewView_triggered()
{

    QWidget *queryWidget =new QWidget();
    QToolBar *tabToolBar =new QToolBar();
    QToolButton *buttonExec=new QToolButton();
    QSizePolicy *sizePolicy=new QSizePolicy();
    sizePolicy->setHorizontalPolicy(QSizePolicy::Minimum);

    buttonExec->setIcon(QIcon(":/icon/img/exec.svg"));
    buttonExec->setFixedSize(20,20);

    tabToolBar->setSizePolicy(*sizePolicy);
    tabToolBar->addWidget(buttonExec);

    QVBoxLayout *layout = new QVBoxLayout;
    QTextEdit *sqlTextEdit =new QTextEdit();
    QTableWidget *tableWidget=new QTableWidget();
    QSplitter *querySplitter=new QSplitter(Qt::Vertical);
    querySplitter->addWidget(sqlTextEdit);
    querySplitter->addWidget(tableWidget);
    querySplitter->setHandleWidth(1);
    querySplitter->setStretchFactor(3,1);



    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->hide();

    layout->addWidget(tabToolBar);
    layout->addWidget(querySplitter);

    queryWidget->setLayout(layout);

    const QIcon *objIcon  = new QIcon(":/icon/img/query.svg");
    this->ui->tabWidget->addTab(queryWidget,*objIcon,QString("对象").append("-").append("新建查询"));
    this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count()-1);

    void (QToolButton:: * clicked) (bool)= &QToolButton::clicked;

    connect(buttonExec,clicked,this,[=](){
        QString sql=sqlTextEdit->toPlainText();
        qDebug()<< sql;
        qDebug() << mySqlDataBase;
        ConnectDB conn;
        QList<QMap<QString,QString>>*queryData=conn.queryData(&mySqlDataBase,&sql);

        tableWidget->setRowCount(queryData->size());
        tableWidget->setColumnCount((*queryData).at(0).size());
        tableWidget->show();

        QStringList header;

        for (auto iter = (*queryData).at(0).begin(); iter != (*queryData).at(0).end(); ++iter)
        {
            QString key = iter.key();
            header<< key;
        }

        tableWidget->setHorizontalHeaderLabels(header);

        if(queryData->size()==0){
            qDebug()<<"无数据";
        }

        for(int i=0;i<(*queryData).size();i++){
            QMap<QString,QString>map=(*queryData).at(i);
             int j=0;
            for (auto iter = map.begin(); iter != map.end(); ++iter)
            {
                QString key = iter.key();
                QString value = iter.value();
                qDebug() << key << value;
                QTableWidgetItem *item=new QTableWidgetItem();
                item->setText(value);
                tableWidget->setItem(i,j,item);
                j++;
            }

        }
    });

}




MainWindow::~MainWindow()
{
    delete ui;
}

AccountXml::AccountXml(){
    this->url=NULL;
    this->pwd=NULL;
    this->name=NULL;
    this->port=0;
}


