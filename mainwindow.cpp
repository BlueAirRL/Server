#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QSettings>

static const QString iniFileName = "serverConfig.ini";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readIni();
    initUI();

    m_timeidRunningStatus = startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;

    killTimer(m_timeidRunningStatus);
}

void MainWindow::initUI()
{
    m_pListenerModel = new QStandardItemModel(0,3,this);
    m_pListenerModel->setHeaderData(0,Qt::Horizontal,tr("Name"));
    m_pListenerModel->setHeaderData(1,Qt::Horizontal,tr("Addr"));
    m_pListenerModel->setHeaderData(2,Qt::Horizontal,tr("Port"));
    ui->listenTableView->setModel(m_pListenerModel);
}

void MainWindow::on_listenAdd_clicked()
{
    QString name = ui->lineEdit->text();
    QString ipAdd = ui->lineEdit_2->text();
    QString port = ui->lineEdit_3->text();
    QHostAddress address(ipAdd);
    if (address.isNull())
        address = QHostAddress(QHostAddress::Any);

    if (m_listenNames.contains(name))
    {
        QMessageBox::information(this, tr("信息"), tr("监听的名称已经被使用"));
        return;
    }

    if (address.isNull())
    {
        QMessageBox::information(this, tr("信息"), tr("地址无效"));
        return;
    }

    if (port.toInt() < 1024 || port.toInt() > 32767)
    {
        QMessageBox::information(this, tr("信息"), tr("监听端口无效，必须在1024~32767之间"));
        return;
    }

    int count = m_pListenerModel->rowCount();
    m_pListenerModel->insertRow(count);
    m_pListenerModel->setData(m_pListenerModel->index(count, 0), name);
    m_pListenerModel->setData(m_pListenerModel->index(count, 1), address.toString());
    m_pListenerModel->setData(m_pListenerModel->index(count, 2), port);
    m_listenNames.append(name);
    m_listPorts.append(port.toInt());
}

//修改
void MainWindow::on_modify_clicked()
{

}

void MainWindow::on_listenDel_clicked()
{
    //当前选中的模型
    QItemSelectionModel* pModel = ui->listenTableView->selectionModel();
    //选中的所用项
    QModelIndexList list = pModel->selectedIndexes();

    //记录要删除的所有项
    QSet<int> rows; //唯一性
    foreach (QModelIndex index, list)
    {
        rows.insert(index.row());
    }


    //删除项
    int ct = 0;
    QString str;
    int port;
    QList<int> listValue = rows.values();
    //必须排序删除，不然删除错乱
    qSort(listValue.begin(), listValue.end());
    foreach (int row, listValue)
    {
        str = m_pListenerModel->index(row-ct, 0).data().toString();
        port = m_pListenerModel->index(row-ct, 2).data().toInt();
        m_listPorts.removeOne(port);
        m_listenNames.removeOne(str);
        m_pListenerModel->removeRow(row-ct);
        ct++;
    }
}

void MainWindow::on_listenSave_clicked()
{
    QSettings setting(iniFileName, QSettings::IniFormat);
    setting.setValue("Listen/name", ui->lineEdit->text());
    setting.setValue("Listen/addr", ui->lineEdit_2->text());
    setting.setValue("Listen/port", ui->lineEdit_3->text());
}

void MainWindow::on_taskSave_clicked()
{
    QSettings setting(iniFileName, QSettings::IniFormat);
    setting.setValue("Thread/transfer", ui->spinBox->value());
    setting.setValue("Thread/dataProcee", ui->spinBox_2->value());
}


void MainWindow::readIni()
{
    QSettings setting(iniFileName, QSettings::IniFormat);
    ui->lineEdit->setText(setting.value("Listen/name", "listen1").toString());
    ui->lineEdit_2->setText(setting.value("Listen/addr", "127.0.0.1").toString());
    ui->lineEdit_3->setText(setting.value("Listen/port", "5826").toString());

    ui->spinBox->setValue(setting.value("Thread/transfer", 8).toInt());
    ui->spinBox_2->setValue(setting.value("Thread/dataProcee", 8).toInt());
}

//运行状况
void MainWindow::runningStatus()
{
    QByteArray arry;
    arry.append(tr("监听端口数: %1").arg(m_listenNames.size()));
    arry.append("\r\n");

    for (int i = 0; i < m_listenNames.size() && i < m_listPorts.size(); i++)
    {
        arry.append(tr("  监听名称: %1\t监听端口: %2").arg(m_listenNames.at(i)).arg(m_listPorts.at(i)));
        arry.append("\r\n");
    }

    arry.append("\r\n");
    arry.append("\r\n");

    ui->plainTextEdit->setPlainText(arry);
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timeidRunningStatus)
    {
        killTimer(m_timeidRunningStatus);
        runningStatus();
        m_timeidRunningStatus = startTimer(m_timeidRunningStatus);
    }
}


