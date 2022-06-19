#include "addwords.h"
#include "ui_addwords.h"
#include <QMessageBox>
AddWords::AddWords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWords)
{
    ui->setupUi(this);
}

AddWords::~AddWords()
{
    delete ui;
}
void AddWords::on_pushButton_clicked()
{
    QString key=ui->lineEdit->text();
    QString value=ui->lineEdit_2->text();
    if(isCorrectWord(key)&&isCorrectWord(value))
    {
        emit this->AddWordEmit(key,value);
        QString log="";
        log+=QDateTime::currentDateTime().toString();
        log+=";важно;";
        log+="Ввод слова;значение\n";
        emit this->logEmit(log);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        this->close();
    }
    else
    {
        QMessageBox::information(this,"Информация","Данные введено неверно");
    }
}

bool AddWords::isCorrectWord(QString &str)
{
    for(qsizetype i=0;i<str.length();i++)
    {
        if(!str.at(i).isLetter())
            return false;
    }
    return true;
}


void AddWords::on_AddWords_customContextMenuRequested(const QPoint &pos)
{

}

