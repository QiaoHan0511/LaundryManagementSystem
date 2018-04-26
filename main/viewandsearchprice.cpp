#include "viewandsearchprice.h"
#include "ui_viewandsearchprice.h"
#include <QMessageBox>
#include <Qtsql>
#include <QStringList>
#include <QString>

ViewAndSearchPrice::ViewAndSearchPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAndSearchPrice)
{
    ui->setupUi(this);
}

ViewAndSearchPrice::~ViewAndSearchPrice()
{
    delete ui;
}

void ViewAndSearchPrice::on_searchButton_clicked()
{
    QString itemName = ui->itemName->text();
    QString namecheck;

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    QSqlQuery queryLaundry;

    if (itemName == NULL)
    {
        QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert item name."));
    }
    else
    {
        queryLaundry.prepare("SELECT ItemName FROM PRICELIST WHERE ItemName = '"+itemName+"'");
        queryLaundry.exec();
        while (queryLaundry.next())
        {
            namecheck = queryLaundry.value(0).toString();
        }

        if (namecheck == itemName)
        {
            queryLaundry.prepare("SELECT ItemName as 'Item Name', ItemPrice as 'Item Price' FROM PRICELIST WHERE ItemName = '"+itemName+"'");
            queryLaundry.exec();

            modelLaundry->setQuery(queryLaundry);
            ui->priceTableView->setModel(modelLaundry);

            ui->itemName->clear();

        }
        else
        {
            QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert a valid item name."));
            ui->itemName->clear();
        }
    }

}

void ViewAndSearchPrice::on_loadAllButton_clicked()
{
    ui->itemName->clear();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    QSqlQuery queryLaundry;
    queryLaundry.prepare("SELECT ItemName as 'Item Name', ItemPrice as 'Item Price' from PRICELIST");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->priceTableView->setModel(modelLaundry);
}


void ViewAndSearchPrice::on_backButton_clicked()
{
    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery("");
    ui->priceTableView->setModel(modelLaundry);

    this->close();
}
