#ifndef NUMBER_INPUT_DIALOG_H
#define NUMBER_INPUT_DIALOG_H

#include <QDialog>
#include "../core/database_util.h"

namespace Ui {
class NumberInputDialog;
}

class NumberInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumberInputDialog(QWidget *parent = 0);
    ~NumberInputDialog();

    void bind(DatabaseUtil database);

signals:
    void sendNumber(int number);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NumberInputDialog *ui;

    DatabaseUtil database;
};

#endif // NUMBER_INPUT_DIALOG_H
