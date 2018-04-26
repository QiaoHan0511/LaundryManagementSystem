#ifndef VIEWANDSEARCHINVOICE_H
#define VIEWANDSEARCHINVOICE_H

#include <QDialog>

namespace Ui {
class ViewAndSearchInvoice;
}

class ViewAndSearchInvoice : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAndSearchInvoice(QWidget *parent = 0);
    ~ViewAndSearchInvoice();

private slots:

    void on_searchButton_clicked();

    void on_loadAllButton_clicked();

    void on_invoiceTableView_activated(const QModelIndex &index);

    void on_backButton_clicked();

private:
    Ui::ViewAndSearchInvoice *ui;
};

#endif // VIEWANDSEARCHINVOICE_H
