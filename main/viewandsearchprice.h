#ifndef VIEWANDSEARCHPRICE_H
#define VIEWANDSEARCHPRICE_H

#include <QDialog>

namespace Ui {
class ViewAndSearchPrice;
}

class ViewAndSearchPrice : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAndSearchPrice(QWidget *parent = 0);
    ~ViewAndSearchPrice();

private slots:
    void on_searchButton_clicked();

    void on_loadAllButton_clicked();

    void on_backButton_clicked();

private:
    Ui::ViewAndSearchPrice *ui;
};

#endif // VIEWANDSEARCHPRICE_H
