#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void readIni();

    void initUI();

private slots:
    void on_listenAdd_clicked();

    void on_listenDel_clicked();

    void on_listenSave_clicked();

    void on_taskSave_clicked();

    void on_modify_clicked();

public slots:
    void runningStatus();

protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;

    //监听的所有名称
    QStringList  m_listenNames;
    QList<int>   m_listPorts;
    //监听器模型
    QStandardItemModel* m_pListenerModel;

    int m_timeidRunningStatus;
};

#endif // MAINWINDOW_H
