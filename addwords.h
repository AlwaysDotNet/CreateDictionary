#ifndef ADDWORDS_H
#define ADDWORDS_H

#include <QWidget>
#include <QDialog>
#include <QDateTime>
namespace Ui {
class AddWords;
}

class AddWords : public QDialog
{
    Q_OBJECT

public:
    explicit AddWords(QWidget *parent = nullptr);
    ~AddWords();
signals:
    void logEmit(const QString&str);
    void AddWordEmit(QString&key,QString&value);
private slots:
    void on_pushButton_clicked();

    void on_AddWords_customContextMenuRequested(const QPoint &pos);

private:
    Ui::AddWords *ui;
    bool isCorrectWord(QString&str);
};

#endif // ADDWORDS_H
