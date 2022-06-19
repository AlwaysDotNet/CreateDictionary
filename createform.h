#ifndef CREATEFORM_H
#define CREATEFORM_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QDialog>
namespace Ui {
class CreateForm;
}

class CreateForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateForm(QWidget *parent = nullptr);
    ~CreateForm();
signals:
    void logEmit(const QString&log);
private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateForm *ui;
};

#endif // CREATEFORM_H
