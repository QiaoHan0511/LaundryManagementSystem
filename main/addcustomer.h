#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>

namespace Ui {
class addCustomer;
}

class addCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit addCustomer(QWidget *parent = 0);
    ~addCustomer();

private:
    Ui::addCustomer *ui;
};

#endif // ADDCUSTOMER_H
