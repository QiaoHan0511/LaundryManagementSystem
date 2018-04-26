#include "invoice.h"
#include "ui_invoice.h"

Invoice::Invoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Invoice)
{
    ui->setupUi(this);
}

Invoice::~Invoice()
{
    delete ui;
}

void Invoice::on_InsertInvoiceButton_clicked()
{
    windowInsertInvoice.show();
}

void Invoice::on_ViewInvoiceButton_clicked()
{
    windowViewAndSearchInvoice.show();
}
