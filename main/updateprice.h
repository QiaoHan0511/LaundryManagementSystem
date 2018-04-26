#ifndef UPDATEPRICE_H
#define UPDATEPRICE_H

#include <QDialog>

namespace Ui {
class UpdatePrice;
}

class UpdatePrice : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePrice(QWidget *parent = 0);
    ~UpdatePrice();


private slots:

    void on_updateButton_clicked();

    void on_finishButton_clicked();

    void on_deleteButton_clicked();

    void on_itemNamecomboBox_activated(const QString &arg1);


    void on_itemNameButton_clicked();

private:
    Ui::UpdatePrice *ui;

};

#endif // UPDATEPRICE_H
