#include "customlistwidget.h"
#include "ui_customlistwidget.h"


CustomListWidget::CustomListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CustomListWidget) {
    hide();
    ui->setupUi(this);
    ui->item_button->setIcon(QIcon(COMPLETED_ICON));
    connect(ui->item_button, &QPushButton::clicked, this, &CustomListWidget::check_button_clicked);
}

CustomListWidget::~CustomListWidget() {
    delete ui;
}

void CustomListWidget::check_button_clicked() {
    emit completed_signal(this);
}
