#ifndef AUTEUR_H
#define AUTEUR_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class auteur;
}

class auteur : public QDialog
{
    Q_OBJECT

public:
    explicit auteur(QWidget *parent = 0);
    ~auteur();
    int renvoieNumAuteur();
    QString renvoieAuteur();
    QString renvoiePreAuteur();

private slots:
    void on_pushButton_clicked();

private:
    Ui::auteur *ui;
    void afficherTable();
    int i=0;
    int noMax;
};

#endif // AUTEUR_H
