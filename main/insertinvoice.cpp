#include "insertinvoice.h"
#include "ui_insertinvoice.h"
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QStringList>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>


InsertInvoice::InsertInvoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertInvoice)
{
    ui->setupUi(this);

    ui->sales_groupBox->hide();
    ui->custInfo_groupBox->hide();
    ui->invoicetableView->hide();
    ui->total_groupBox->hide();
    ui->finishButton->hide();


    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTime_text = dateTime.toString("d/M/yyyy h:mm A");
    ui->todayDateTime->setText(dateTime_text);
}

InsertInvoice::~InsertInvoice()
{
    delete ui;
}

void InsertInvoice::on_newInvoiceButton_clicked()
{
    ui->custInfo_groupBox->show();
}

void InsertInvoice::on_checkButton_clicked()
{
    QSqlQuery queryLaundry;

    queryLaundry.prepare("CREATE TABLE IF NOT EXISTS CUSTOMER"
                         "(ContactNo VARCHAR(12) UNIQUE PRIMARY KEY,"
                         " CustName VARCHAR(30),"
                         " CustAddress VARCHAR(80))");

    if (!queryLaundry.exec())
            qDebug() << queryLaundry.lastError();
        else
            qDebug() << "Table created!";


    QString contactNo, contactCheck;

    contactNo = ui->contactNolineEdit->text();

    if (contactNo == NULL)
    {
        QMessageBox::warning(this,tr("Invalid Input."),tr("Please insert a contact no.."));
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
            if (queryLaundry.prepare("INSERT INTO CUSTOMER (ContactNo) VALUES('"+contactNo+"')"))
                queryLaundry.exec();
            else
                QMessageBox::information(this, "Error", "Failed to save data" + queryLaundry.lastError().text());
        }
        else
        {
            if (queryLaundry.exec("SELECT CustName, CustAddress FROM CUSTOMER WHERE ContactNo = '"+contactNo+"'"))
            {
                while(queryLaundry.next())
                {
                    ui->custNamelineEdit->setText(queryLaundry.value(0).toString());
                    ui->custAddresstextEdit->setText(queryLaundry.value(1).toString());
                }
            }
            else
                QMessageBox::information(this, "Error", "Failed to save data" + queryLaundry.lastError().text());
        }
    }
}

void InsertInvoice::on_confirmButton_clicked()
{
    QString contactNo, custName, custAddress;

    contactNo = ui->contactNolineEdit->text();
    custName = ui->custNamelineEdit->text();
    custAddress = ui->custAddresstextEdit->toPlainText();

    QSqlQuery queryLaundry;
        if (queryLaundry.exec("UPDATE CUSTOMER SET CustName='"+custName+"', CustAddress='"+custAddress+"' WHERE ContactNo='"+contactNo+"'"))
            QMessageBox::information(this,"Customer Info","Saved");
        else
            QMessageBox::critical(this,"Error", queryLaundry.lastError().text());


    ui->sales_groupBox->show();


    ui->readydateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(5));
    ui->readydateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());


    ui->itemNamecomboBox->show();


    queryLaundry.prepare("CREATE TABLE IF NOT EXISTS INVOICE"
                         "(InvoiceNo VARCHAR(10) UNIQUE PRIMARY KEY,"
                         " DroppedOffDate DATE,"
                         " ReadyDate DATE,"
                         " ContactNo VARCHAR(12) REFERENCES CUSTOMER(ContactNo))");

    if (!queryLaundry.exec())
            qDebug() << queryLaundry.lastError();
        else
            qDebug() << "Table created!";


    queryLaundry.prepare("select MAX(CAST(SUBSTR(InvoiceNo,4,9) as int)) + 1 from INVOICE");
    queryLaundry.exec();

    int num;

    if(queryLaundry.next())
    {
        num = queryLaundry.value(0).toInt();
    }
    if (num == 0)
    {
        num = num + 1;
    }

    ui->invoiceNo->setText("BBL" + QString::number(num));


    QSqlQueryModel *modelLaundry = new QSqlQueryModel();

    queryLaundry.prepare("SELECT ItemName from PRICELIST");
    queryLaundry.exec();
    modelLaundry->setQuery(queryLaundry);

    ui->itemNamecomboBox->setModel(modelLaundry);

}

void InsertInvoice::on_itemNamecomboBox_activated(const QString &choice)
{
    QSqlQuery queryLaundry;

    int firstNo, lastNo;
    QString itemCode, checkCode;

    firstNo=0;
    lastNo=10000;

    do{
        int randomValue = qrand() % ((lastNo + 1) - firstNo) + firstNo;

        queryLaundry.exec("SELECT ItemName FROM PRICELIST WHERE ItemName='"+choice+"'");
        while(queryLaundry.next())
        {
            itemCode=(queryLaundry.value(0).toString() + QString::number(randomValue));
        }

        queryLaundry.prepare("SELECT ItemCode FROM ITEM WHERE ItemCode='"+itemCode+"'");
        queryLaundry.exec();
        while(queryLaundry.next())
        {
            checkCode=queryLaundry.value(0).toString();
        }

        if(itemCode==checkCode)
        {
             ui->itemCode->setText("");
        }
        else
        {
            ui->itemCode->setText(itemCode);
        }

    }while(itemCode==checkCode);





    queryLaundry.prepare("CREATE TABLE IF NOT EXISTS ITEM"
                         "(ItemCode VARCHAR(15) UNIQUE PRIMARY KEY,"
                         " InvoiceNo VARCHAR(10) REFERENCES INVOICE(InvoiceNo),"
                         " ItemName VARCHAR(30) REFERENCES PRICELIST(ItemName),"
                         " Status VARCHAR(15),"
                         " CollectedDate DATE)");

    if (!queryLaundry.exec())
            qDebug() << queryLaundry.lastError();
        else
            qDebug() << "Table created!";


}

void InsertInvoice::on_nextItemButton_clicked()
{
    ui->invoicetableView->show();
    ui->total_groupBox->show();
    ui->changeLabel->hide();
    ui->change->hide();

    QString invoiceNo = ui->invoiceNo->text();
    QString itemSelect = ui->itemNamecomboBox->currentText();
    QString itemCode = ui->itemCode->text();
    QString readyDateTime = ui->readydateTimeEdit->text();
    QString todayDateTime = ui->todayDateTime->text();
    QString contactNo = ui->contactNolineEdit->text();


    QSqlQuery queryLaundry;

    queryLaundry.prepare("INSERT INTO INVOICE (InvoiceNo, DroppedOffDate, ReadyDate, ContactNo)"
                         "VALUES ('"+invoiceNo+"', '"+todayDateTime+"', '"+readyDateTime+"', '"+contactNo+"')");

    queryLaundry.exec();


    queryLaundry.prepare("INSERT INTO ITEM (ItemCode, InvoiceNo, ItemName, Status)"
                         "VALUES ('"+itemCode+"', '"+invoiceNo+"', '"+itemSelect+"', 'Waiting') ");

    queryLaundry.exec();


    ui->itemNamecomboBox->setCurrentIndex(0);
    ui->itemCode->clear();


    queryLaundry.prepare("SELECT ITEM.ItemCode as 'Item Code', PRICELIST.ItemName as 'Item Name', PRICELIST.ItemPrice as 'Item Price' FROM ITEM, PRICELIST WHERE PRICELIST.ItemName = ITEM.ItemName AND ITEM.InvoiceNo = '"+invoiceNo+"'");

    queryLaundry.exec();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery(queryLaundry);

    ui->invoicetableView->setModel(modelLaundry);


    double total = 0.00;

    queryLaundry.exec("SELECT SUM(ItemPrice)FROM PRICELIST, ITEM WHERE PRICELIST.ItemName=ITEM.ItemName AND ITEM.InvoiceNo = '"+invoiceNo+"'");

    if (queryLaundry.next())
        total += queryLaundry.value(0).toDouble();

    ui->total->setText(QString::number(total));

    double finalTotal = 0.00;

    if (total >= 50)
    {
        finalTotal = (total * 0.90) ;
    }
    else
    {
        finalTotal = total;
    }

    ui->finalTotal->setText(QString::number(finalTotal));

}

void InsertInvoice::on_enterButton_clicked()
{
    QString finalTotal, cash;

    double change = 0.00;

    finalTotal = ui->finalTotal->text();
    cash = ui->cash_lineEdit->text();

    if(cash < finalTotal)
    {
        QMessageBox::critical(this,"Error", "Please insert a valid amount!");
        ui->cash_lineEdit->clear();
    }
    else
    {
        change = (cash.toDouble() - finalTotal.toDouble());
        ui->changeLabel->show();
        ui->change->show();
        ui->change->setText(QString::number(change));
        ui->finishButton->show();
    }

}

void InsertInvoice::on_finishButton_clicked()
{
    QString total = ui->total->text();
    QString finalTotal = ui->finalTotal->text();
    QString cash = ui->cash_lineEdit->text();
    QString change = ui->change->text();
    QString invoiceNo = ui->invoiceNo->text();
    QString CustName, contactNo, droppedOffDate, readyDate;

    const int i = 15;
    QString itemName[i], itemCode[i], itemPrice[i];

    QSqlQuery queryLaundry;


    queryLaundry.prepare("SELECT c.CustName, i.ContactNo, i.DroppedOffDate, i.ReadyDate FROM CUSTOMER c, INVOICE i WHERE c.ContactNo = i.ContactNo AND i.InvoiceNo = '"+invoiceNo+"'");
    queryLaundry.exec();
    while (queryLaundry.next())
    {
        CustName = queryLaundry.value(0).toString();
        contactNo = queryLaundry.value(1).toString();
        droppedOffDate = queryLaundry.value(2).toString();
        readyDate = queryLaundry.value(3).toString();
    }

    queryLaundry.prepare("SELECT i.ItemName, i.ItemCode, p.ItemPrice FROM PRICELIST p, ITEM i WHERE p.ItemName=i.ItemName AND i.InvoiceNo = '"+invoiceNo+"'");
    queryLaundry.exec();
    for (int i = 0; i<15 ; i++)
    {
        if (queryLaundry.next())
        {
            itemName[i] = queryLaundry.value(0).toString();
            itemCode[i] = queryLaundry.value(1).toString();
            itemPrice[i] = queryLaundry.value(2).toString();
        }
    }



    QString fileName = tr("../Laundry_Management_System/invoice.pdf");
    QPdfWriter pdf(fileName);
    QPainter painter(&pdf);
    pdf.setPageSize(QPagedPaintDevice::A4);

    painter.drawImage(QRect(150,0,4800,2160), QImage("../Laundry_Management_System/logo BBL"));

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(5200,800,"BIG BOSS LAUNDRY SDN BHD");

    painter.setFont(QFont("Arial", 10, QFont::Normal));
    painter.drawText(5200,1200,"Freeport A Famosa, Unit 88 and 89");
    painter.drawText(5200,1400,"Melaka, Malaysia.");
    painter.drawText(5200,1600,"Tel: 062820333");
    painter.drawText(5200,1800,"Email: bigbosslaundry@gmail.com");
    painter.drawText(5200,2000,"Visit us at www.bigbosslaundry.com");

    QPen paintpen(Qt::black);
    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,2500,9600,2500);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(6650,3000,"Tax Invoice:");
    painter.drawText(8350,3000,invoiceNo);

    painter.setFont(QFont("Arial", 12, QFont::Normal));
    painter.drawText(1000,3500,CustName);
    painter.drawText(1000,3800,contactNo);
    painter.drawText(1000,4100,"Dropped off: ");
    painter.drawText(2200,4100,droppedOffDate);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(1000,4400,"Ready on: ");
    painter.drawText(2100,4400,readyDate);

    painter.setFont(QFont("Arial", 16, QFont::Bold));
//    painter.drawText(1200, 5100, "No.");
    painter.drawText(2500,5100,"Item");
    painter.drawText(6500,5100,"Amount");
    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,5200,9600,5200);

    for (int a=5800, i=0; i<10;i++, a+=600)
    {
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(2500,a,itemName[i]);
        painter.drawText(6500,a,itemPrice[i]);
        painter.setFont(QFont("Arial", 10, QFont::Normal));
        painter.drawText(3500,a,itemCode[i]);
    }

    paintpen.setWidth(30);
    painter.setPen(paintpen);
    painter.drawLine(0,10700,9600,10700);
    painter.setFont(QFont("Arial", 16, QFont::Normal));
    painter.drawText(5000,11300,"Sub Total:");
    painter.drawText(5000,11700,"Total:");
    painter.drawText(5000,12100,"Cash:");
    painter.drawText(5000,12500,"Change:");
    painter.drawText(7200,11300,"RM "+total);
    painter.drawText(7200,11700,"RM "+finalTotal);
    painter.drawText(7200,12100,"RM "+cash);
    painter.drawText(7200,12500,"RM "+change);


    painter.end();
    QDesktopServices::openUrl(QUrl("file:///C:/Users/user-pc/Documents/Laundry_Management_System/invoice.pdf", QUrl::TolerantMode));



    ui->contactNolineEdit->clear();
    ui->custNamelineEdit->clear();
    ui->custAddresstextEdit->clear();
    ui->custInfo_groupBox->close();

    ui->invoiceNo->clear();
    ui->readydateTimeEdit->clear();
    ui->sales_groupBox->close();

    QSqlQueryModel *modelLaundry = new QSqlQueryModel();
    modelLaundry->setQuery("");
    ui->invoicetableView->setModel(modelLaundry);
    ui->invoicetableView->close();

    ui->total->clear();
    ui->cash_lineEdit->clear();
    ui->change->clear();
    ui->total_groupBox->close();

    this->close();

}



