#include "customer.h"
#include "ui_customer.h"
#include <QMessageBox>
#include <Qtsql>
#include <QStringList>
#include <QString>

Customer::Customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
}

Customer::~Customer()
{
    delete ui;
}

void Customer::on_searchButton_clicked()
{
    QString contactNo = ui->contactNo->text();
    QString contactCheck;

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    QSqlQuery queryLaundry;

    if (contactNo == NULL)
    {
        QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert contact no.."));
    }
    else
    {
        queryLaundry.prepare("SELECT ContactNo FROM CUSTOMER WHERE ContactNo = '"+contactNo+"'");
        queryLaundry.exec();
        while (queryLaundry.next())
        {
            contactCheck = queryLaundry.value(0).toString();
        }

        if (contactCheck != contactNo)
        {
            QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert a valid contact no.."));
            ui->contactNo->clear();

        }
        else
        {

            queryLaundry.prepare("SELECT ContactNo as 'Contact No', CustName as 'Customer Name', CustAddress as 'Customer Address' FROM CUSTOMER WHERE ContactNo = '"+contactNo+"'");
            queryLaundry.exec();

            modelLaundry->setQuery(queryLaundry);
            ui->customerTableView->setModel(modelLaundry);

            ui->contactNo->clear();
        }
    }

}

void Customer::on_loadAllButton_clicked()
{
    ui->contactNo->clear();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    QSqlQuery queryLaundry;
    queryLaundry.prepare("SELECT ContactNo as 'Contact No', CustName as 'Customer Name', CustAddress as 'Customer Address' from CUSTOMER");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->customerTableView->setModel(modelLaundry);
}

void Customer::on_backButton_clicked()
{
    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery("");
    ui->customerTableView->setModel(modelLaundry);
    this->close();
}
