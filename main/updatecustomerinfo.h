#ifndef UPDATECUSTOMERINFO_H
#define UPDATECUSTOMERINFO_H

#include <QDialog>

namespace Ui {
class UpdateCustomerInfo;
}

class UpdateCustomerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCustomerInfo(QWidget *parent = 0);
    ~UpdateCustomerInfo();

private:
    Ui::UpdateCustomerInfo *ui;
};

#endif // UPDATECUSTOMERINFO_H
