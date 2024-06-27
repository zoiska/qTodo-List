#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ItemDialog; }
QT_END_NAMESPACE

class ItemDialog : public QMainWindow {
Q_OBJECT

public:
    explicit ItemDialog(QWidget *parent = nullptr);

    ~ItemDialog() override;

    void clear();

signals:
    void add_item(QString title,QString description);

public slots:
    void button_add_clicked();
    void button_cancel_clicked();

private:
    Ui::ItemDialog *ui;
};


#endif //ITEMDIALOG_H
