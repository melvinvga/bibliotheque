#include "categorie.h"
#include "ui_categorie.h"

categorie::categorie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::categorie)
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

categorie::~categorie()
{
    delete ui;
}

int categorie::renvoieNumCategorie()
{
    return (noMax);
}

QString categorie::renvoieCategorie()
{
    return (ui->lineEditAjouterCategorie->text());
}

void categorie::afficherTable()
{
    //afficher le select dans le tableau
    QSqlQuery query;
    query.exec("SELECT numeroCategories, libelleCategories FROM Categories");
    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value("numeroCategories").toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("libelleCategories").toString()));
        i++;
    }
}

void categorie::on_pushButton_clicked()
{
    //recuperation des informations
    QString libelle;
    libelle=ui->lineEditAjouterCategorie->text();

    //calcul du numero de categorie le plus haut
    QString txtReqMax="SELECT MAX(numeroCategories) FROM Categories";
    QSqlQuery queryReqMax(txtReqMax);
    queryReqMax.next();
    noMax=queryReqMax.value(0).toInt();
    noMax++;

    //requete d'insertion dans la base
    QString txtReqInsertion="INSERT INTO Categories (numeroCategories, libelleCategories) VALUES ('"+QString::number(noMax)+"','"+libelle+"')";
    QSqlQuery query(txtReqInsertion);

    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(noLigne);
    ui->tableWidget->setItem(noLigne,0,new QTableWidgetItem(QString::number(noMax)));
    ui->tableWidget->setItem(noLigne,1,new QTableWidgetItem(libelle));
    accept();
}
