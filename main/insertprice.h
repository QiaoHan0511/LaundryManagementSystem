#ifndef INSERTPRICE_H
#define INSERTPRICE_H

#include <QDialog>

namespace Ui {
class InsertPrice;
}

class InsertPrice : public QDialog
{
    Q_OBJECT

public:
    explicit InsertPrice(QWidget *parent = 0);
    ~InsertPrice();

private slots:
    void on_savepriceButton_clicked();

    void on_backButton_clicked();

private:
    Ui::InsertPrice *ui;
};

#endif // INSERTPRICE_H
