#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomListWidget; }
QT_END_NAMESPACE

class CustomListWidget : public QWidget {
Q_OBJECT

public:
    explicit CustomListWidget(QWidget *parent = nullptr);

    ~CustomListWidget() override;

signals:
    void  completed_signal(CustomListWidget *widget);

public slots:
    void check_button_clicked();

private:
    Ui::CustomListWidget *ui;
};


#endif //CUSTOMLISTWIDGET_H