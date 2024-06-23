#include "change_dialog.h"
#include "ui_change_dialog.h"


change_dialog::change_dialog(const QString &title, const QString &description, mainwindow *parent) : QMainWindow(parent), ui(new Ui::change_dialog), mainwindowptr(parent) {
    ui->setupUi(this);
    ui->lineEdit->setText(title);
    ui->textEdit->setPlainText(description);
    QObject::connect(ui->button_change, &QPushButton::clicked, this, &change_dialog::button_change_clicked);
    QObject::connect(ui->button_cancel, &QPushButton::clicked, this, &change_dialog::button_cancel_clicked);
}

change_dialog::~change_dialog() {
    delete ui;
}

void change_dialog::button_change_clicked() {
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    emit add_item(title, description);
    this->close();
}

void change_dialog::button_cancel_clicked() {
    this->close();
}
