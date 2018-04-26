#ifndef VIEWCUSTINFO_H
#define VIEWCUSTINFO_H

#include <QDialog>

namespace Ui {
class ViewCustInfo;
}

class ViewCustInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCustInfo(QWidget *parent = 0);
    ~ViewCustInfo();

private:
    Ui::ViewCustInfo *ui;
};

#endif // VIEWCUSTINFO_H
