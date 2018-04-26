#ifndef SALESREPORT_H
#define SALESREPORT_H

#include <QDialog>

namespace Ui {
class salesReport;
}

class salesReport : public QDialog
{
    Q_OBJECT

public:
    explicit salesReport(QWidget *parent = 0);
    ~salesReport();

private:
    Ui::salesReport *ui;
};

#endif // SALESREPORT_H
