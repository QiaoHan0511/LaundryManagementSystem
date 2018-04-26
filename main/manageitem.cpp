#include "manageitem.h"
#include "ui_manageitem.h"
#include <QMessageBox>
#include <Qtsql>
#include <QStringList>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QDateTime>

ManageItem::ManageItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageItem)
{
    ui->setupUi(this);

    ui->ItemGroupBox->hide();
}

ManageItem::~ManageItem()
{
    delete ui;
}

void ManageItem::on_searchButton_clicked()
{
    QString invoiceItem = ui->invoiceNoItemCode->text();
    QString check, check2;

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    QSqlQuery queryLaundry;

    if (invoiceItem == NULL)
    {
        QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert either invoice no. or item code."));
    }
    else
    {
        queryLaundry.prepare("SELECT InvoiceNo, ItemCode FROM ITEM WHERE InvoiceNo='"+invoiceItem+"' or ItemCode='"+invoiceItem+"'");
        queryLaundry.exec();
        while (queryLaundry.next())
        {
            check = queryLaundry.value(0).toString();
            check2 = queryLaundry.value(1).toString();
        }

        if (check == invoiceItem || check2 == invoiceItem)
        {
            queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ItemCode as 'Item Code', Status FROM ITEM WHERE InvoiceNo='"+invoiceItem+"' or ItemCode='"+invoiceItem+"'");
            queryLaundry.exec();

            modelLaundry->setQuery(queryLaundry);
            ui->itemTableView->setModel(modelLaundry);

            ui->invoiceNoItemCode->clear();

        }
        else
        {
            QMessageBox::warning(this,tr("Invalid Search."),tr("Please insert a valid invoice no. or item code."));
            ui->invoiceNoItemCode->clear();
        }
    }

}

void ManageItem::on_loadComboBox_currentIndexChanged(const QString &choice)
{
    ui->invoiceNoItemCode->clear();


    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    QSqlQuery queryLaundry;

    if (choice == "Ready" || choice == "Waiting" || choice == "Collected")
    {
        queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ItemCode as 'Item Code', Status FROM ITEM WHERE Status == '"+choice+"'");
        queryLaundry.exec();
        modelLaundry->setQuery(queryLaundry);

        ui->itemTableView->setModel(modelLaundry);
    }
    else if (choice == "All")
    {
        queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ItemCode as 'Item Code', Status FROM ITEM");
        queryLaundry.exec();
        modelLaundry->setQuery(queryLaundry);

        ui->itemTableView->setModel(modelLaundry);
    }
    else
    {
        ui->itemTableView->setModel(NULL);
    }
}

void ManageItem::on_itemTableView_activated(const QModelIndex &index)
{


    QString row = ui->itemTableView->model()->data(index).toString();

    QSqlQuery queryLaundry;

    queryLaundry.prepare("SELECT InvoiceNo, ItemCode, Status FROM ITEM WHERE ItemCode='"+row+"'");
    if (queryLaundry.exec())
    {
        ui->ItemGroupBox->show();
        ui->collctedDateLabel->hide();
        ui->collecteddateTimeEdit->hide();

        while(queryLaundry.next())
        {
            ui->itemCode->setText(queryLaundry.value(1).toString());
            ui->invoiceNo->setText(queryLaundry.value(0).toString());
            ui->statusComboBox->setCurrentText(queryLaundry.value(2).toString());
        }
    }
}

void ManageItem::on_backButton_clicked()
{
    ui->statusComboBox->setCurrentIndex(0);
    ui->itemCode->clear();
    ui->invoiceNo->clear();
    ui->collecteddateTimeEdit->clear();
    ui->collctedDateLabel->hide();
    ui->collecteddateTimeEdit->hide();
    ui->ItemGroupBox->hide();


    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery("");
    ui->itemTableView->setModel(modelLaundry);
    this->close();
}

void ManageItem::on_updateButton_clicked()
{


    QString itemCode, invoiceNo, status, collectedDate;

    itemCode = ui->itemCode->text();
    invoiceNo = ui->invoiceNo->text();
    status = ui->statusComboBox->currentText();
    collectedDate = ui->collecteddateTimeEdit->text();


    QSqlQuery queryLaundry;
    if (status == "Collected")
    {
        if (queryLaundry.exec("UPDATE ITEM SET Status='"+status+"' WHERE ItemCode='"+itemCode+"'"))
            QMessageBox::information(this,"Edit","Saved");
        else
            QMessageBox::critical(this,"Error", queryLaundry.lastError().text());

    }
    else
    {
        if (queryLaundry.exec("UPDATE ITEM SET Status='"+status+"', CollectedDate='"+collectedDate+"' WHERE ItemCode='"+itemCode+"'"))
            QMessageBox::information(this,"Edit","Saved");
        else
            QMessageBox::critical(this,"Error", queryLaundry.lastError().text());
    }



    ui->statusComboBox->setCurrentIndex(0);
    ui->itemCode->clear();
    ui->invoiceNo->clear();
    ui->collecteddateTimeEdit->clear();
    ui->collctedDateLabel->hide();
    ui->collecteddateTimeEdit->hide();
    ui->ItemGroupBox->hide();

    QString choice = ui->loadComboBox->currentText();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();


    if (choice == "Ready" || choice == "Waiting" || choice == "Collected")
    {
        queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ItemCode as 'Item Code', Status FROM ITEM WHERE Status == '"+choice+"'");
        queryLaundry.exec();
        modelLaundry->setQuery(queryLaundry);

        ui->itemTableView->setModel(modelLaundry);
    }
    else if (choice == "All")
    {
        queryLaundry.prepare("SELECT InvoiceNo as 'Invoice No', ItemCode as 'Item Code', Status FROM ITEM");
        queryLaundry.exec();
        modelLaundry->setQuery(queryLaundry);

        ui->itemTableView->setModel(modelLaundry);
    }
    else
    {
        ui->itemTableView->setModel(NULL);
    }

}

void ManageItem::on_statusComboBox_currentIndexChanged(const QString &status)
{
    QString invoiceNo, readyDate;

    invoiceNo = ui->invoiceNo->text();

    QSqlQuery queryLaundry;

    queryLaundry.prepare("SELECT ReadyDate FROM INVOICE WHERE InvoiceNo='"+invoiceNo+"'");
    queryLaundry.exec();
    while(queryLaundry.next())
    {
        readyDate = queryLaundry.value(0).toString();
    }


    if (status == "Collected")
    {
        ui->collctedDateLabel->show();
        ui->collecteddateTimeEdit->show();
        ui->collecteddateTimeEdit->setDateTime(QDateTime::currentDateTime());
        //ui->collecteddateTimeEdit->setMinimumDateTime(QDateTime::fromString(readyDate));
    }

}
