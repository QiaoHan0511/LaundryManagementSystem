#include "insertprice.h"
#include "ui_insertprice.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql>

InsertPrice::InsertPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertPrice)
{
    ui->setupUi(this);

}

InsertPrice::~InsertPrice()
{
    delete ui;
}


void InsertPrice::on_savepriceButton_clicked()
{

    QString ItemName, ItemPrice;

    ItemName = ui->itemName->text();
    ItemPrice = ui->itemPrice->text();

    ui->itemName->clear();
    ui->itemPrice->clear();

    QSqlQuery queryLaundry;

    queryLaundry.prepare("CREATE TABLE IF NOT EXISTS PRICELIST "
                         "( ItemName VARCHAR(30) UNIQUE PRIMARY KEY,"
                         " ItemPrice DOUBLE )");


    if (!queryLaundry.exec())
        qDebug() << queryLaundry.lastError();
    else
        qDebug() << "Table created!";

    queryLaundry.prepare("INSERT INTO PRICELIST ( ItemName, ItemPrice)"
                         " VALUES ( '"+ItemName+"', '"+ItemPrice+"')");

    if (!queryLaundry.exec())
    {
        QMessageBox::information(this, "Error", "Failed to save data" + queryLaundry.lastError().text());
    }
}

void InsertPrice::on_backButton_clicked()
{
    ui->itemName->clear();
    ui->itemPrice->clear();

    this->close();
}
