#include "updateprice.h"
#include "ui_updateprice.h"
#include <QtSql>
#include <QMessageBox>

UpdatePrice::UpdatePrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdatePrice)
{
    ui->setupUi(this);

}

UpdatePrice::~UpdatePrice()
{
    delete ui;
}




void UpdatePrice::on_updateButton_clicked()
{
    QString itemName, itemPrice;

    itemName = ui->itemNamelineEdit->text();
    itemPrice = ui->itemPricelineEdit->text();

    QSqlQuery queryLaundry;
    if (queryLaundry.exec("UPDATE PRICELIST SET ItemPrice='"+itemPrice+"' WHERE ItemName='"+itemName+"'"))
        QMessageBox::information(this,"Edit","Saved");
    else
        QMessageBox::critical(this,"Error", queryLaundry.lastError().text());

    ui->itemNamecomboBox->setCurrentIndex(0);
    ui->itemNamelineEdit->clear();
    ui->itemPricelineEdit->clear();

}

void UpdatePrice::on_finishButton_clicked()
{
    this->close();
}

void UpdatePrice::on_deleteButton_clicked()
{
    QString itemName, itemPrice;

    itemName = ui->itemNamelineEdit->text();
    itemPrice = ui->itemPricelineEdit->text();

    QSqlQuery queryLaundry;

    if (queryLaundry.exec("DELETE FROM PRICELIST WHERE ItemName='"+itemName+"'"))
    {
        QMessageBox::information(this,"Delete","Deleted");
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),queryLaundry.lastError().text());
    }


    ui->itemNamelineEdit->clear();
    ui->itemPricelineEdit->clear();
    ui->itemNamecomboBox->setCurrentIndex(0);


    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    queryLaundry.prepare("SELECT ItemName from PRICELIST");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->itemNamecomboBox->setModel(modelLaundry);

}


void UpdatePrice::on_itemNamecomboBox_activated(const QString &choice)
{
    QSqlQuery queryLaundry;

    if (queryLaundry.exec("SELECT * FROM PRICELIST WHERE ItemName='"+choice+"'"))
    {
        while(queryLaundry.next())
        {
            ui->itemNamelineEdit->setText(queryLaundry.value(0).toString());
            ui->itemPricelineEdit->setText(queryLaundry.value(1).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),queryLaundry.lastError().text());
    }
}



void UpdatePrice::on_itemNameButton_clicked()
{
    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    QSqlQuery queryLaundry;
    queryLaundry.prepare("SELECT ItemName from PRICELIST");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->itemNamecomboBox->setModel(modelLaundry);
}
