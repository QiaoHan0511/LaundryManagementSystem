#include "salesreport.h"
#include "ui_salesreport.h"

salesReport::salesReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesReport)
{
    ui->setupUi(this);
}

salesReport::~salesReport()
{
    delete ui;
}
