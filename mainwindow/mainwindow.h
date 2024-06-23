#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMenuBar>
#include <QFile>
#include "../item_dialog/item_dialog.h"
#include "../change_dialog/change_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    Ui::mainwindow *ui;

    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

public slots:
    void add_clicked();
    void change_clicked();
    void delete_clicked() const;
    void add_list_item(const QString &title, const QString &description) const;
    void change_list_item(const QString &title, const QString &description) const;
    void create_menus();
    void load_clicked() const;
    void save_clicked() const;

private:
    QAction *load_act;
    QAction *save_act;
};


#endif //MAINWINDOW_H