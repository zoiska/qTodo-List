#include "item_dialog.h"
#include "ui_item_dialog.h"


item_dialog::item_dialog(mainwindow *parent) : QMainWindow(parent), ui(new Ui::item_dialog), mainwindowptr(parent) {
    ui->setupUi(this);
    QObject::connect(ui->button_add, &QPushButton::clicked, this, &item_dialog::button_add_clicked);
    QObject::connect(ui->button_cancel, &QPushButton::clicked, this, &item_dialog::button_cancel_clicked);
}

item_dialog::~item_dialog() {
    delete ui;
}

void item_dialog::button_add_clicked() {
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    emit add_item(title, description);
    this->close();
}

void item_dialog::button_cancel_clicked() {
    this->close();
}