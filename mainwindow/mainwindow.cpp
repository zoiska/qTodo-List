#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    create_menus();
    setupConnects();
    load_clicked();
    load_completed();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::add_clicked() {
    itemDialog->clear();
    itemDialog->show();
}

void MainWindow::change_clicked() {
    if(ui->listWidget->currentItem() != nullptr) {
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();
        QString text = selectedItem->text();

        QStringList parts = text.split('\n');
        QString title = parts[0];
        QString description = "";
        for (int j = 1; j < parts.size() - 1; ++j) {
            description += parts[j] + "\n";
        }
        description += parts[parts.size() - 1];

        changeDialog->fillInputs(title, description);
        changeDialog->show();
    }
}

void MainWindow::delete_clicked() const {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));
}

void MainWindow::completed(CustomListWidget *widget) const {
    ui->label_out->setText(ui->label_out->text() + "Task Completed\n");

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (ui->listWidget->itemWidget(item) == widget) {
            QFile completedFile(COMPLETED_FILE);
            if (!completedFile.open(QIODevice::Append | QIODevice::Text)) {
                ui->label_out->setText("F");
                return;
            }

            QTextStream out(&completedFile);
            QString text = item->text();
            QStringList parts = text.split("\n");
            QString title = parts[0].replace(",", "[COMMA]");
            QString description = "";
            for (int j = 1; j < parts.size() - 1; ++j) {
                description += parts[j].replace(",", "[COMMA]") + "\\n";
            }
            description += parts[parts.size() - 1].replace(",", "[COMMA]");
            out << title << "," << description << "\n";
            completedFile.close();

            add_completed_item(title, description);
            break;
        }
    }
}

void MainWindow::load_completed() const {
    ui->listWidget_2->clear();
    QFile file(COMPLETED_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->label_out->setText("Failed to open file");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 2)
        {
            QString title = fields[0];
            QString description = fields[1];

            auto item = new QListWidgetItem(title.replace("[COMMA]", ",") + "\n" + description.replace("[COMMA]", ",").replace("\\n", "\n"));
            ui->listWidget_2->addItem(item);
        }
    }
    file.close();
}

void MainWindow::add_completed_item(const QString& title, const QString &description) const {
    auto item = new QListWidgetItem(title + "\n" + description);

    ui->listWidget_2->addItem(item);
}

void MainWindow::add_list_item(const QString& title, const QString& description) const {
    auto customitem = new CustomListWidget((QWidget *) this);
    connect(customitem, &CustomListWidget::completed_signal, this, &MainWindow::completed);
    auto item = new QListWidgetItem(title + "\n" + description);

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, customitem);
}

void MainWindow::change_list_item(const QString &title, const QString &description) const {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));

    auto customitem = new CustomListWidget((QWidget *) this);
    connect(customitem, &CustomListWidget::completed_signal, this, &MainWindow::completed);
    auto item = new QListWidgetItem(title + "\n" + description);

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, customitem);
}

void MainWindow::create_menus() {
    load_act = new QAction("Load tasks", this);
    load_act->setToolTip(tr("Load tasks from file"));
    load_act->setShortcut(QKeySequence("CTRL+L"));
    load_act->setIcon(QIcon(LOAD_ICON));

    save_act = new QAction("Save tasks", this);
    save_act->setToolTip(tr("Save current tasks"));
    save_act->setShortcut(QKeySequence("CTRL+S"));
    save_act->setIcon(QIcon(SAVE_ICON));

    QMenuBar *bar = menuBar();
    QMenu *file_menu = bar->addMenu(tr("Menu"));
    file_menu->addAction(load_act);
    file_menu->addAction(save_act);
}

void MainWindow::load_clicked() const {
    ui->listWidget->clear();
    QFile file(SAVE_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->label_out->setText("Failed to open file");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 2)
        {
            QString title = fields[0];
            QString description = fields[1];

            auto customitem = new CustomListWidget((QWidget *) this);
            connect(customitem, &CustomListWidget::completed_signal, this, &MainWindow::completed);
            auto item = new QListWidgetItem(title.replace("[COMMA]", ",") + "\n" + description.replace("[COMMA]", ",").replace("\\n", "\n"));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item, customitem);
        }
    }
    file.close();
}

void MainWindow::save_clicked() const {
    QFile file(SAVE_FILE);
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
        QString title = parts[0].replace(",", "[COMMA]");
        QString description = "";
        for (int j = 1; j < parts.size() - 1; ++j) {
            description += parts[j].replace(",", "[COMMA]") + "\\n";
        }
        description += parts[parts.size() - 1].replace(",", "[COMMA]");
        out << title << "," << description << "\n";
    }
    file.close();
}

void MainWindow::setupConnects() {
    connect(ui->button_add, &QPushButton::clicked, this, &MainWindow::add_clicked);
    connect(ui->button_change, &QPushButton::clicked, this, &MainWindow::change_clicked);
    connect(ui->button_delete, &QPushButton::clicked, this, &MainWindow::delete_clicked);

    connect(load_act, &QAction::triggered, this, &MainWindow::load_clicked);
    connect(save_act, &QAction::triggered, this, &MainWindow::save_clicked);

    connect(itemDialog, &ItemDialog::add_item, this, &MainWindow::add_list_item);
    connect(changeDialog, &ChangeDialog::add_item, this, &MainWindow::change_list_item);
}
