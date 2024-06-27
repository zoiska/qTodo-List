#include "changedialog.h"
#include "ui_change_dialog.h"

#include "../mainwindow/mainwindow.h"

ChangeDialog::ChangeDialog(QWidget *parent) : QMainWindow(parent), ui(new Ui::ChangeDialog) {
    ui->setupUi(this);

    QObject::connect(ui->button_change,&QPushButton::clicked,this,&ChangeDialog::button_change_clicked);
    QObject::connect(ui->button_cancel, &QPushButton::clicked, this, &ChangeDialog::button_cancel_clicked);
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}

void ChangeDialog::fillInputs(const QString &title, const QString &description)
{
    ui->lineEdit->setText(title);
    ui->textEdit->setPlainText(description);
}

void ChangeDialog::button_change_clicked()
{
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    emit add_item(title, description);
    this->close();
}

void ChangeDialog::button_cancel_clicked()
{
    this->close();
}
