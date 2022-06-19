#ifndef QTRANSLATOR_H
#define QTRANSLATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include <cstdint>
#include <map>//Используем asosation map
#include <QFile>
#include <QTextStream>
#include <QDateTime>
class QString;
//Реализуем класс Словарья
/*
 *используем контйенер multimap каждое слова можеть имеет более одно значение
Реализуем так что бы мы могли работать двухстаронно то есть например Англо-Русскый или Русско английскый
*/
class QTranslator:public QObject
{
    Q_OBJECT
private:
   std::multimap<QString,QString>dicts;//База слов  слов и перевод
   size_t size;//Количество слов
   QString fromLang;//С какого языка
   QString toLang;//Переводимое  язык
   QString fileName;//Файл базы данных
public:
    QTranslator(const QString &filename);//Конструктор  принимает название Файла
    QTranslator(const QTranslator&tr);//Копирование объекта
    QStringList findWord(QString& key);//Нахождение слова и его значение
    QString getLangFrom()const;
    QString getLangTo()const;
    size_t getSize()const;
    std::multimap<QString,QString>getDicts()const;
    QString getFileName()const;
    QStringList getKeys()const;//Возврашает только ключи
    ~QTranslator();
signals:
    void sgErorFile();//Если файл не сушествует то выбрасиваем сигнал
    void logEmit(const QString& st);//Логирование
public slots:
    void AddWord(const QString&wrd,const QString& value);//Добавление новая слова  и его значение
    void RemoveWord(QString& key);//Удаление слова
    void  updateBase();//Обновление базы после удаление
};

#endif // QTRANSLATOR_H
