#include "lms.h"
#include "ui_lms.h"

LMS::LMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMS)
{
    ui->setupUi(this);
}

LMS::~LMS()
{
    delete ui;
}

void LMS::on_PriceListButton_clicked()
{
    windowPriceList.show();
}

void LMS::on_ExitButton_clicked()
{
    this->close();
}

void LMS::on_InvoiceButton_clicked()
{
    windowInvoice.show();
}

void LMS::on_CustomerButton_clicked()
{
    windowCustomer.show();
}

void LMS::on_ManageItemButton_clicked()
{
    windowManageItem.show();
}

void LMS::on_SalesReportButton_clicked()
{
    windowSalesReport.show();
}
