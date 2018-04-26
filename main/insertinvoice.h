#ifndef INSERTINVOICE_H
#define INSERTINVOICE_H

#include <QDialog>

namespace Ui {
class InsertInvoice;
}

class InsertInvoice : public QDialog
{
    Q_OBJECT

public:
    explicit InsertInvoice(QWidget *parent = 0);
    ~InsertInvoice();

private slots:
    void on_newInvoiceButton_clicked();

    void on_confirmButton_clicked();

    void on_nextItemButton_clicked();

    void on_itemNamecomboBox_activated(const QString &arg1);

    void on_finishButton_clicked();

    void on_checkButton_clicked();

    void on_enterButton_clicked();


private:
    Ui::InsertInvoice *ui;
};

#endif // INSERTINVOICE_H
