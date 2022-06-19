#include "qtranslator.h"
#include <QMessageBox>
#include <exception>
QTranslator::QTranslator(const QString &filename)
{
    try {

        QFile baseFile;

        this->fileName=QString(filename);

        qDebug()<<this->fileName<<"\n";
        baseFile.setFileName(filename);//Установка значение файла
        if(!baseFile.open(QIODevice::ReadOnly|QFile::Text))
        {
                //Если файл не откоется то нужно передтсигнал
            emit this->sgErorFile();
        }
        else
        {
            //Название файл должен описат язык например Eng_Русскый.csv
            qDebug()<<"Open File\n";
            QString cur=filename;
            auto part=cur.split("_");//разделим
            this->fromLang=part.front();
            QString rem="";
            size_t pos=0;
            for(qsizetype i=0;i<fromLang.length();i++)
            {
                if(fromLang.at(i)=='/')
                    pos=i;
            }
            if(pos!=0)
            fromLang=fromLang.remove(0,pos+1);
            part.pop_front();
            this->toLang=part.front();
            toLang=toLang.remove(".csv");
            part.clear();
            qDebug()<<fromLang<<" "<<toLang<<"\n";
            //Теперь прочитаем всех слов
            //Файл csv разделено ; символам в виде key;value
            //Одно ключ и одно значение если значение несколько то нужно указать через пробел Например hello;Привет Здравствуйте ....
            QTextStream s(&baseFile);
            while(!s.atEnd())
            {
                QString line=s.readLine();
                if(line.isEmpty())
                    break;
                qDebug()<<line;
                QStringList lst=line.split(";");
                QString key=lst.front();
                lst.pop_front();
                QStringList values=lst.front().split(" ");
                values.removeDuplicates();
                lst.clear();
                for(QString value:values)
                {
                    dicts.emplace(key,value);
                }
            }
            //Загрузили базу
            this->size=dicts.size();
            baseFile.close();
        }
    }
     catch(std::exception e)
    {
        QMessageBox::about(nullptr,"Ошибка ",QString::fromLatin1(e.what()));
    }
}

QTranslator::QTranslator(const QTranslator &tr)
{
    this->size=tr.getSize();
    this->fromLang=tr.getLangFrom();
    this->toLang=tr.getLangTo();
    this->fileName=tr.getFileName();
    this->dicts=tr.getDicts();
    QString log="";
    log+=QDateTime::currentDateTime().toString();
    log+="; Не важно;Копирование объекта\n";
    emit logEmit(log);
}

QStringList QTranslator::findWord(QString &key)
{
    auto it=dicts.equal_range(key);
    QStringList lst;
    for(auto& cur=it.first;cur!=it.second;cur++)
    {
        lst.push_back((*cur).second);
    }
    QString log="";
    log+=QDateTime::currentDateTime().toString();
    log+="; Не важно;";
    log+="Нахождение значение перевода\n";
    emit logEmit(log);
    return lst;
}

QString QTranslator::getLangFrom() const
{
    return fromLang;
}

QString QTranslator::getLangTo() const
{
    return this->toLang;
}

size_t QTranslator::getSize()const
{
    return size;
}

std::multimap<QString, QString> QTranslator::getDicts() const
{
    return this->dicts;
}

QString QTranslator::getFileName() const
{
    return this->fileName;
}

QStringList QTranslator::getKeys() const
{
    QStringList lst;
    for(auto it=dicts.begin();it!=dicts.end();it++)
    {
        lst<<(*it).first;
    }
    return lst;
}

QTranslator::~QTranslator()
{
  dicts.clear();
}

void QTranslator::AddWord(const QString &wrd, const QString &value)
{
    qDebug()<<"Adding\n";
     this->dicts.emplace(wrd,value);
     QFile base;
     base.setFileName(this->fileName);
     qDebug()<<fileName<<"\n";
     base.open(QIODevice::Append|QFile::Text);
     QTextStream s(&base);
     s<<wrd<<";"<<value<<"\n";
     base.close();
     QString log="";
     log+=QDateTime::currentDateTime().toString();
     log+=";важно;";
     log+="Добавление слова:значение\n";
     emit logEmit(log);
}

void QTranslator::RemoveWord(QString &key)
{
    this->dicts.erase(key);
    QString log="";
    log+=QDateTime::currentDateTime().toString();
    log+=";важно;";
    log+="Удаление\n";
    emit logEmit(log);
    updateBase();
}

void QTranslator::updateBase()
{
    //Обновление базы данных
    QFile base(this->fileName);
    base.open(QIODevice::Append|QFile::Text);
    QTextStream s(&base);
    for(auto cur=dicts.begin();cur!=dicts.end();cur++)
    {
        s<<(*cur).first<<";"<<(*cur).second<<"\n";
    }
    QString log="";
    log+=QDateTime::currentDateTime().toString();
    log+=";важно;";
    log+="Перезапись базы данных\n";
    emit logEmit(log);
    base.close();
}
