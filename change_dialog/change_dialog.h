#ifndef CHANGE_DIALOG_H
#define CHANGE_DIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class change_dialog; }
QT_END_NAMESPACE

class mainwindow;

class change_dialog : public QMainWindow {
Q_OBJECT

public:
    explicit change_dialog(mainwindow *parent = nullptr);

    ~change_dialog() override;

    void fillInputs(const QString &title, const QString &description);

signals:
    void add_item(QString title,QString description);

public slots:
    void button_change_clicked();
    void button_cancel_clicked();

private:
    Ui::change_dialog *ui;
    mainwindow *mainwindowptr;
};


#endif //CHANGE_DIALOG_H
