#include "auteur.h"
#include "ui_auteur.h"
#include <QDebug>

auteur::auteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auteur)
{
    ui->setupUi(this);
    //initialisation tableau
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    //mise en place du header du tableau
    QStringList headers;
    headers << "N°" << "Nom";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //tableau responsif
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    afficherTable();
}

auteur::~auteur()
{
    delete ui;
}

int auteur::renvoieNumAuteur()
{
    return (noMax);
}

QString auteur::renvoieAuteur()
{
    return (ui->lineEditAjouterAuteur->text());
}

QString auteur::renvoiePreAuteur()
{
    return (ui->lineEditAjouterPreAuteur->text());
}

void auteur::afficherTable()
{
    //afficher le select dans le tableau
    QSqlQuery query;
    query.exec("SELECT numeroAuteurs, libelleAuteurs FROM Auteurs");
    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value("numeroAuteurs").toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("nomAuteurs").toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value("prenomAuteurs").toString()));
        i++;
    }
}

void auteur::on_pushButton_clicked()
{
    //recuperation des informations
    QString nom, prenom;
    nom=ui->lineEditAjouterAuteur->text();
    prenom=ui->lineEditAjouterPreAuteur->text();

    //calcul du numero d'auteur le plus haut
    QString txtReqMax="SELECT MAX(numeroAuteurs) FROM Auteurs";
    QSqlQuery queryReqMax(txtReqMax);
    queryReqMax.next();
    noMax=queryReqMax.value(0).toInt();
    noMax++;

    //requete d'insertion dans la base
    QString txtReqInsertion="INSERT INTO Auteurs (numeroAuteurs, nomAuteurs, prenomAuteurs) VALUES ('"+QString::number(noMax)+"',UPPER('"+nom+"'),'"+prenom+"')";
    QSqlQuery queryReqInsertion(txtReqInsertion);

    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(noLigne);
    ui->tableWidget->setItem(noLigne,0,new QTableWidgetItem(QString::number(noMax)));
    ui->tableWidget->setItem(noLigne,1,new QTableWidgetItem(nom.toUpper()));
    ui->tableWidget->setItem(noLigne,1,new QTableWidgetItem(prenom));
    accept();
}
