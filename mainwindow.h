#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QSqlDatabase mySqlDataBase;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UiDefault();
    void DbInit();

public slots:
    /**
     * 刷新DBUI
     * @brief reshDbUI
     */
    void reshDbUI();

    void closeTab(int index);


    /**
     * 展示表数据
     * @brief showTables
     */
    void showTables(QTreeWidgetItem  * item,int index);

private slots:
    void on_actionnewView_triggered();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
