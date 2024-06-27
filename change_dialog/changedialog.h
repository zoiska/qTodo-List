#ifndef CHANGE_DIALOG_H
#define CHANGE_DIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ChangeDialog; }
QT_END_NAMESPACE

class ChangeDialog : public QMainWindow {
Q_OBJECT

public:
    explicit ChangeDialog(QWidget *parent = nullptr);

    ~ChangeDialog() override;

    void fillInputs(const QString &title, const QString &description);

signals:
    void add_item(QString title,QString description);

public slots:
    void button_change_clicked();
    void button_cancel_clicked();

private:
    Ui::ChangeDialog *ui;
};


#endif //CHANGE_DIALOG_H
