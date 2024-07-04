#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomListWidget; }
QT_END_NAMESPACE

class CustomListWidget : public QWidget {
Q_OBJECT

public:
    explicit CustomListWidget(QWidget *parent = nullptr);

    ~CustomListWidget() override;

private slots:
    void completed_clicked();

private:
    Ui::CustomListWidget *ui;
};


#endif //CUSTOMLISTWIDGET_H