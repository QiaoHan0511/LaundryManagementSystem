#ifndef INVOICE_H
#define INVOICE_H

#include <QDialog>
#include "insertinvoice.h"
#include "viewandsearchinvoice.h"

namespace Ui {
class Invoice;
}

class Invoice : public QDialog
{
    Q_OBJECT

public:
    explicit Invoice(QWidget *parent = 0);
    ~Invoice();

private:
    Ui::Invoice *ui;

protected:
    InsertInvoice windowInsertInvoice;
    ViewAndSearchInvoice windowViewAndSearchInvoice;

private slots:
    void on_InsertInvoiceButton_clicked();
    void on_ViewInvoiceButton_clicked();
};

#endif // INVOICE_H
