#ifndef LMS_H
#define LMS_H

#include <QWidget>
#include "pricelist.h"
#include "invoice.h"
#include "customer.h"
#include "manageitem.h"
#include "salesreport.h"

namespace Ui {
class LMS;
}

class LMS : public QWidget
{
    Q_OBJECT

public:
    explicit LMS(QWidget *parent = 0);
    ~LMS();

private:
    Ui::LMS *ui;

protected:
    PriceList windowPriceList;
    Invoice windowInvoice;
    Customer windowCustomer;
    ManageItem windowManageItem;
    salesReport windowSalesReport;

private slots:
    void on_PriceListButton_clicked();
    void on_ExitButton_clicked();
    void on_InvoiceButton_clicked();
    void on_CustomerButton_clicked();
    void on_ManageItemButton_clicked();
    void on_SalesReportButton_clicked();
};

#endif // LMS_H
