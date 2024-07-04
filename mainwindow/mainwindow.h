#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMenuBar>
#include <QFile>
#include "../item_dialog/itemdialog.h"
#include "../change_dialog/changedialog.h"
#include "customlistwidget.h"

class FileHandling;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void add_clicked();
    void change_clicked();
    void delete_clicked() const;
    void add_list_item(const QString &title, const QString &description) const;
    void change_list_item(const QString &title, const QString &description) const;
    void create_menus();
    void load_clicked() const;
    void save_clicked() const;

public slots:
    void completed() const;

private:
    void setupConnects();
    QAction *load_act;
    QAction *save_act;
    ItemDialog *itemDialog = new ItemDialog(this);
    ChangeDialog *changeDialog = new ChangeDialog(this);
    CustomListWidget *customlistwidget = new CustomListWidget(this);
};


#endif //MAINWINDOW_H
