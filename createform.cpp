#include "createform.h"
#include "ui_createform.h"

CreateForm::CreateForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateForm)
{
    ui->setupUi(this);
}

CreateForm::~CreateForm()
{
    delete ui;
}

void CreateForm::on_pushButton_clicked()
{
    QFile sv;
    if(QDir::isAbsolutePath(QApplication::applicationDirPath()+"\\base"))
    {

        sv.setFileName(QApplication::applicationDirPath()+"\\base\\"+ui->lineEdit->text()+"_"+ui->lineEdit_2->text()+".csv");
        sv.open(QIODevice::NewOnly|QFile::Text);
        QString log=QDateTime::currentDateTime().toString()+"; не важно;Созадно новый словарь\n";
        emit logEmit(log);
        sv.close();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        close();
    }
   else
    {

        QString log=QDateTime::currentDateTime().toString()+"; важно;не удалось создать новый словарь\n";
        emit logEmit(log);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        close();
    }
}

