#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>

namespace Ui {
class Customer;
}

class Customer : public QDialog
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = 0);
    ~Customer();

private slots:
    void on_searchButton_clicked();

    void on_loadAllButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Customer *ui;

};

#endif // CUSTOMER_H
