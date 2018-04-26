#ifndef MANAGEITEM_H
#define MANAGEITEM_H

#include <QDialog>

namespace Ui {
class ManageItem;
}

class ManageItem : public QDialog
{
    Q_OBJECT

public:
    explicit ManageItem(QWidget *parent = 0);
    ~ManageItem();

private slots:
    void on_searchButton_clicked();

    void on_loadComboBox_currentIndexChanged(const QString &arg1);

    void on_itemTableView_activated(const QModelIndex &index);

    void on_backButton_clicked();

    void on_updateButton_clicked();

    void on_statusComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::ManageItem *ui;
};

#endif // MANAGEITEM_H
