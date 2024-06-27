#include "item_dialog.h"
#include "ui_item_dialog.h"

#include "../mainwindow/mainwindow.h"

item_dialog::item_dialog(mainwindow *parent) : QMainWindow(parent), ui(new Ui::item_dialog), mainwindowptr(parent) {
    ui->setupUi(this);
    QObject::connect(ui->button_add, &QPushButton::clicked, this, &item_dialog::button_add_clicked);
    QObject::connect(ui->button_cancel, &QPushButton::clicked, this, &item_dialog::button_cancel_clicked);
}

item_dialog::~item_dialog() {
    delete ui;
}

void item_dialog::clear()
{
    ui->textEdit->clear();
    ui->lineEdit->clear();
}

void item_dialog::button_add_clicked() {
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    emit add_item(title, description);
    close();
}

void item_dialog::button_cancel_clicked() {
    close();
}
