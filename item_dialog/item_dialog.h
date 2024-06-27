#ifndef ITEM_DIALOG_H
#define ITEM_DIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class item_dialog; }
QT_END_NAMESPACE

class mainwindow;

class item_dialog : public QMainWindow {
Q_OBJECT

public:
    explicit item_dialog(mainwindow *parent = nullptr);

    ~item_dialog() override;

    void clear();

signals:
    void add_item(QString title,QString description);

public slots:
    void button_add_clicked();
    void button_cancel_clicked();

private:
    Ui::item_dialog *ui;
    mainwindow *mainwindowptr;
};


#endif //ITEM_DIALOG_H
