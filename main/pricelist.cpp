#include "pricelist.h"
#include "ui_pricelist.h"
#include <QtSql>
#include <QTimer>


PriceList::PriceList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceList)
{
    ui->setupUi(this);
}

PriceList::~PriceList()
{
    delete ui;
}

void PriceList::on_InsertPriceButton_clicked()
{
    windowInsertPrice.show();
}

void PriceList::on_UpdatePriceButton_clicked()
{
    windowUpdatePrice.show();
}

void PriceList::on_ViewPriceButton_clicked()
{
    windowViewAndSearchPrice.show();
}

void PriceList::on_backButton_clicked()
{
    this->close();
}
