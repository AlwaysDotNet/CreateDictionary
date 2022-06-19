#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "qtranslator.h"
#include <QCompleter>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include "addwords.h"
#include "createform.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void goTelegram();
    void goWhatsUp();
    void changeRat();
    void IconChange();
    void IconChange2();
    void IconChange3();

    void on_pushButton_clicked();
    void open_translator();//Открыт новый словарь
    void on_removeWord();//Удаление слова
    void showAddWidget();
    void addNewWords(QString&key,QString&value);
    void showCreateForm();
    void getLogEmit(const QString&qst);
private:
    Ui::MainWindow *ui;
    QTranslator *dictions;
    QCompleter *comp;
    bool isCorrectWordInput(QString &str);//Проверка введенное слова
    AddWords* m_w_Add;//Виджет для добавление слова
    CreateForm *m_cr_form;
    QFile flog;
};
#endif // MAINWINDOW_H
