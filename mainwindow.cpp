#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->quit,&QAction::triggered,this,QApplication::quit);
    connect(ui->actionTelegramm,&QAction::triggered,this,&MainWindow::goTelegram);
    connect(ui->actionWhatsUp,&QAction::triggered,this,&MainWindow::goWhatsUp);
    connect(ui->actionrat_1,&QAction::triggered,this,&MainWindow::IconChange);
    connect(ui->actionrat_2,&QAction::triggered,this,&MainWindow::IconChange2);
    connect(ui->actionrat_3,&QAction::triggered,this,&MainWindow::IconChange2);
    connect(ui->open_tr,&QAction::triggered,this,&MainWindow::open_translator);
    connect(ui->actionremoveWord,&QAction::triggered,this,&MainWindow::on_removeWord);
    connect(ui->actionaddWord,&QAction::triggered,this,&MainWindow::showAddWidget);
    connect(ui->create,&QAction::triggered,this,&MainWindow::showCreateForm);
    this->dictions=new QTranslator(QApplication::applicationDirPath()+"\\base\\Eng_Russian.csv");
    QStringList lst=dictions->getKeys();
    comp=new QCompleter(lst,this);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(comp);
    QFont font("Time New Romans",14,2,true);
    ui->textEdit->setFont(font);
    ui->label->setText(dictions->getLangFrom()+"->"+dictions->getLangTo());
    this->m_w_Add=new AddWords(this);
    this->m_cr_form=new CreateForm(this);
    flog.setFileName(QApplication::applicationDirPath()+"log.txt");
    flog.open(QIODevice::Append|QFile::Text);
    connect(m_w_Add,SIGNAL(AddWordEmit(QString&,QString&)),this,SLOT(addNewWords(QString&,QString&)));
    connect(m_w_Add,SIGNAL(logEmit(const QString&)),this,SLOT(getLogEmit(const QString&)));
    connect(m_cr_form,SIGNAL(logEmit(const QString&)),this,SLOT(getLogEmit(const QString&)));
    connect(dictions,SIGNAL(logEmit(const QString&)),this,SLOT(getLogEmit(const QString&)));

}

MainWindow::~MainWindow()
{
    delete ui;
    if(dictions!=nullptr)
        delete dictions;
    delete m_cr_form;
    delete m_w_Add;
}

void MainWindow::goTelegram()
{
    QString link="https://telegram.org";
    QDesktopServices::openUrl(link);
}

void MainWindow::goWhatsUp()
{
    QString link="https://whatsapp.com";
    QDesktopServices::openUrl(link);
}

void MainWindow::changeRat()
{
    if(ui->actionrat_1->isCheckable()==true)
    {
        ui->actionrat_1->setCheckable(false);
    }
    else
        ui->actionrat_1->setCheckable(true);
}
//Изменение рейтинг ну к сожаление работает не очень
void MainWindow::IconChange()
{
    this->ui->actionrat_1->setIcon(QIcon(":/img/img/start_sl.ico"));
}

void MainWindow::IconChange2()
{
    this->ui->actionrat_2->setIcon(QIcon(":/img/img/start_sl.ico"));
}

void MainWindow::IconChange3()
{
     this->ui->actionrat_2->setIcon(QIcon(":/img/img/start_sl.ico"));
}

void MainWindow::on_pushButton_clicked()
{
    QString key=ui->lineEdit->text();
    if(!isCorrectWordInput(key))//Если введено не слова
    {
        QMessageBox::information(this,"Информация ","Некорректное ввод");
        ui->lineEdit->clear();
    }
    else
    {
        QStringList lst=dictions->findWord(key);
        //Подготовим шаблон
        QString txt="<ul style=\"list-style-type:circle;color=\'white\';\">";
        for(QString &str:lst)
        {
            txt=txt+"<li>"+str+"<\\li>";
        }
        txt+="<\\ul>";
        ui->textEdit->setText(txt);
    }
}

void MainWindow::open_translator()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QApplication::applicationDirPath(),
                                                    tr("Словарь (*.csv *.txt)"));
    //Откроем файл с записям
    if(comp!=nullptr)
        delete comp;
    if(dictions!=nullptr)
        delete dictions;
    this->dictions=new QTranslator(fileName);
    QStringList lst=dictions->getKeys();
    lst.removeDuplicates();
    comp=new QCompleter(lst,this);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(comp);
}

void MainWindow::on_removeWord()
{
    QString key=ui->lineEdit->text();
    dictions->RemoveWord(key);

    if(comp!=nullptr)
        delete comp;
    QString pth=dictions->getFileName();
    if(dictions!=nullptr)
        delete dictions;
    this->dictions=new QTranslator(pth);
    QStringList lst=dictions->getKeys();
    comp=new QCompleter(lst,this);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(comp);
     ui->label->setText(dictions->getLangFrom()+"->"+dictions->getLangTo());
}

void MainWindow::showAddWidget()
{
    this->m_w_Add->show();
}

void MainWindow::addNewWords(QString &key,QString &value)
{
    dictions->AddWord(key,value);
    if(comp!=nullptr)
        delete comp;
    QString pth=dictions->getFileName();
    if(dictions!=nullptr)
        delete dictions;
    this->dictions=new QTranslator(pth);
    QStringList lst=dictions->getKeys();
    comp=new QCompleter(lst,this);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(comp);
     ui->label->setText(dictions->getLangFrom()+"->"+dictions->getLangTo());
}

void MainWindow::showCreateForm()
{
    m_cr_form->show();
}

void MainWindow::getLogEmit(const QString &qst)
{
    QTextStream st(&flog);
    st<<qst;

}

bool MainWindow::isCorrectWordInput(QString &str)
{
    for(qsizetype i=0;i<str.length();i++)
    {
        if(!str.at(i).isLetter())
            return false;
    }
    return true;
}

