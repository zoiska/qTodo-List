#include "customlistwidget.h"
#include "ui_customlistwidget.h"


CustomListWidget::CustomListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CustomListWidget) {
    ui->setupUi(this);
    ui->item_button->setIcon(QIcon(COMPLETED_ICON));
    connect(ui->item_button, &QPushButton::clicked, this, &CustomListWidget::completed_clicked);
}

CustomListWidget::~CustomListWidget() {
    delete ui;
}

void CustomListWidget::completed_clicked() {
    //animation green fading falling moving sideways?

}
