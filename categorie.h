#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class categorie;
}

class categorie : public QDialog
{
    Q_OBJECT

public:
    explicit categorie(QWidget *parent = 0);
    ~categorie();
    int renvoieNumCategorie();
    QString renvoieCategorie();

private slots:
    void on_pushButton_clicked();

private:
    Ui::categorie *ui;
    void afficherTable();
    int i=0;
    int noMax;
};

#endif // CATEGORIE_H
