#ifndef PRICELIST_H
#define PRICELIST_H

#include <QDialog>
#include "insertprice.h"
#include "updateprice.h"
#include "viewandsearchprice.h"

namespace Ui {
class PriceList;
}

class PriceList : public QDialog
{
    Q_OBJECT

public:
    explicit PriceList(QWidget *parent = 0);
    ~PriceList();

private:
    Ui::PriceList *ui;

protected:
    InsertPrice windowInsertPrice;
    UpdatePrice windowUpdatePrice;
    ViewAndSearchPrice windowViewAndSearchPrice;

private slots:
    void on_InsertPriceButton_clicked();
    void on_UpdatePriceButton_clicked();
    void on_ViewPriceButton_clicked();
    void on_backButton_clicked();
};

#endif // PRICELIST_H
