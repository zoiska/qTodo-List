#include "itemdialog.h"
#include "ui_item_dialog.h"

ItemDialog::ItemDialog(QWidget *parent) : QMainWindow(parent), ui(new Ui::ItemDialog){
    ui->setupUi(this);
    QObject::connect(ui->button_add, &QPushButton::clicked, this, &ItemDialog::button_add_clicked);
    QObject::connect(ui->button_cancel, &QPushButton::clicked, this, &ItemDialog::button_cancel_clicked);
}

ItemDialog::~ItemDialog() {
    delete ui;
}

void ItemDialog::clear()
{
    ui->textEdit->clear();
    ui->lineEdit->clear();
}

void ItemDialog::button_add_clicked() {
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    emit add_item(title, description);
    close();
}

void ItemDialog::button_cancel_clicked() {
    close();
}
