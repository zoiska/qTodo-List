#include "mainwindow.h"
#include "ui_mainwindow.h"


mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    create_menus();

    QObject::connect(ui->button_add, &QPushButton::clicked, this, &mainwindow::add_clicked);
    QObject::connect(ui->button_change, &QPushButton::clicked, this, &mainwindow::change_clicked);
    QObject::connect(ui->button_delete, &QPushButton::clicked, this, &mainwindow::delete_clicked);

    QObject::connect(load_act, &QAction::triggered, this, &mainwindow::load_clicked);
    QObject::connect(save_act, &QAction::triggered, this, &mainwindow::save_clicked);

}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::add_clicked() {
    auto *w = new item_dialog(this);
    QObject::connect(w, &item_dialog::add_item, this, &mainwindow::add_list_item);
    w->show();
}

void mainwindow::change_clicked() {
    if(ui->listWidget->currentItem() != nullptr) {
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();
        QString text = selectedItem->text();

        QStringList parts = text.split('\n');
        QString title = parts[0];
        QString description = parts[1];

        auto *w = new change_dialog(title, description, this);
        QObject::connect(w, &change_dialog::add_item, this, &mainwindow::change_list_item);
        w->show();
    }
}

void mainwindow::delete_clicked() const {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));
}

void mainwindow::add_list_item(const QString& title, const QString& description) const {
    ui->listWidget->addItem(title + "\n" + description);
}

void mainwindow::change_list_item(const QString &title, const QString &description) const {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));
    ui->listWidget->addItem(title + "\n" + description);
}

void mainwindow::create_menus() {
    load_act = new QAction("Load tasks", this);
    load_act->setToolTip(tr("Load tasks from file"));
    save_act = new QAction("Save tasks", this);
    save_act->setToolTip(tr("Save current tasks"));
    QMenuBar *bar = menuBar();
    QMenu *file_menu = bar->addMenu(tr("Menu"));
    file_menu->addAction(load_act);
    file_menu->addAction(save_act);
}

void mainwindow::load_clicked() const {
    ui->listWidget->clear();
    QFile file("../tasks.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->label_out->setText("Failed to open file");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.size() == 2)
        {
            QString title = fields[0];
            QString description = fields[1];
            ui->listWidget->addItem(title + "\n" + description);
        }
    }
    file.close();
}

void mainwindow::save_clicked() const {
    QFile file("../tasks.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        ui->label_out->setText("Failed to open file");
        return;
    }
    QTextStream out(&file);
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString text = item->text();
        QStringList parts = text.split("\n");
        QString title = parts[0];
        QString description = parts[1];
        out << title << ";" << description << "\n";
    }
    file.close();
}
