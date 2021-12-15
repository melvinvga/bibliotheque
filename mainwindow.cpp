#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auteur.h"
#include "categorie.h"
#include <QStringList>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QDebug>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tableau responsif
    ui->tableWidgetAuteurs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //tableau responsif
    ui->tableWidgetCategories->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //tableau responsif
    ui->tableWidgetAdherent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //lancement de l'initialisation des tableaux
    afficherTable();
    ui->groupBoxLivre->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//--------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------INITIALISATION---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
void MainWindow::afficherTable()
{
    //afficher le tableau principal
    QSqlQuery queryTable;
    queryTable.exec("SELECT numeroLivres, titreLivres, resumeLivres, datepubliLivres, atr.nomAuteurs, atr.prenomAuteurs, ctr.libelleCategories FROM Livres INNER JOIN Auteurs atr ON Livres.numeroAuteurs=atr.numeroAuteurs INNER JOIN Categories ctr ON Livres.numeroCategories=ctr.numeroCategories");
    while(queryTable.next())
    {
        ui->tableWidget->insertRow(i);
        QCheckBox* cocher = new QCheckBox();
        liste.append(cocher);
        ui->tableWidget->setCellWidget(i,0, cocher);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(queryTable.value("numeroLivres").toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(queryTable.value("titreLivres").toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(queryTable.value("datepubliLivres").toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(queryTable.value("nomAuteurs").toString()+ " " +queryTable.value("prenomAuteurs").toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(queryTable.value("libelleCategories").toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(queryTable.value("resumeLivres").toString()));
        i++;
    }

    //afficher combobox auteur
    QSqlQuery queryComboAuteur;
    queryComboAuteur.exec("SELECT numeroAuteurs, nomAuteurs, prenomAuteurs FROM Auteurs");
    while(queryComboAuteur.next())
    {
        ui->comboBoxAuteur->addItem(queryComboAuteur.value("nomAuteurs").toString()+ " " +queryComboAuteur.value("prenomAuteurs").toString(),queryComboAuteur.value("numeroAuteurs").toString());
    }

    //afficher combobox categorie
    QSqlQuery queryComboCategorie;
    queryComboCategorie.exec("SELECT numeroCategories, libelleCategories FROM Categories");
    while(queryComboCategorie.next())
    {
        ui->comboBoxCategorie->addItem(queryComboCategorie.value("libelleCategories").toString(),queryComboCategorie.value("numeroCategories").toInt());
    }

    //afficher le tableau Auteurs
    QSqlQuery queryTableActeurs;
    queryTableActeurs.exec("SELECT numeroAuteurs, nomAuteurs, prenomAuteurs FROM Auteurs");
    while(queryTableActeurs.next())
    {
        ui->tableWidgetAuteurs->insertRow(j);
        ui->tableWidgetAuteurs->setItem(j,0,new QTableWidgetItem(queryTableActeurs.value("numeroAuteurs").toString()));
        ui->tableWidgetAuteurs->setItem(j,1,new QTableWidgetItem(queryTableActeurs.value("nomAuteurs").toString()));
        ui->tableWidgetAuteurs->setItem(j,2,new QTableWidgetItem(queryTableActeurs.value("prenomAuteurs").toString()));
        QCheckBox* cocher = new QCheckBox();
        liste2.append(cocher);
        ui->tableWidgetAuteurs->setCellWidget(j,3, cocher);
        j++;
    }

    //afficher le tableau Categories
    QSqlQuery queryTableCategories;
    queryTableCategories.exec("SELECT numeroCategories, libelleCategories FROM Categories");
    while(queryTableCategories.next())
    {
        ui->tableWidgetCategories->insertRow(k);
        ui->tableWidgetCategories->setItem(k,0,new QTableWidgetItem(queryTableCategories.value("numeroCategories").toString()));
        ui->tableWidgetCategories->setItem(k,1,new QTableWidgetItem(queryTableCategories.value("libelleCategories").toString()));
        QCheckBox* cocher = new QCheckBox();
        liste3.append(cocher);
        ui->tableWidgetCategories->setCellWidget(k,2, cocher);
        k++;
    }

    //afficher le tableau Adherents
    QSqlQuery queryTableAdherent;
    queryTableAdherent.exec("SELECT numeroAdherent, nomAdherent, prenomAdherent, mailAdherent FROM Adherent");
    while(queryTableAdherent.next())
    {
        ui->tableWidgetAdherent->insertRow(l);
        ui->tableWidgetAdherent->setItem(l,0,new QTableWidgetItem(queryTableAdherent.value("numeroAdherent").toString()));
        ui->tableWidgetAdherent->setItem(l,1,new QTableWidgetItem(queryTableAdherent.value("nomAdherent").toString()));
        ui->tableWidgetAdherent->setItem(l,2,new QTableWidgetItem(queryTableAdherent.value("prenomAdherent").toString()));
        ui->tableWidgetAdherent->setItem(l,3,new QTableWidgetItem(queryTableAdherent.value("mailAdherent").toString()));
        QCheckBox* cocher = new QCheckBox();
        liste3.append(cocher);
        ui->tableWidgetAdherent->setCellWidget(l,4, cocher);
        l++;
    }
}



//----------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB LIVRES---------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonAjouter_clicked()
{
    //recuperation des informations
    QString titre, resume, date, auteur,cat;
    titre=ui->lineEditTitre->text().replace("'","''");
    resume=ui->textEditResume->toPlainText().replace("'","''");
    date=ui->lineEditDatepubli->text().replace("'","''");
    auteur=ui->comboBoxAuteur->currentText().replace("'","''");

    QStringList listAut = auteur.split(" ");
    QString nomAd=listAut[0];
    QString preAd=listAut[1];

    cat=ui->comboBoxCategorie->currentText().replace("'","''");

    //calcul du numero de livre le plus haut
    QString txtReqMax="SELECT MAX(numeroLivres) FROM Livres";
    QSqlQuery queryReqMax(txtReqMax);
    queryReqMax.next();
    noMax=queryReqMax.value(0).toInt();
    noMax++;


    //recuperation du numero de catégorie et du numero d'ateurs
    QString txtReqNoAut="SELECT numeroAuteurs FROM Auteurs WHERE nomAuteurs='"+nomAd+"' AND prenomAuteurs='"+preAd+"'";
    qDebug()<<txtReqNoAut;
    QSqlQuery queryReqNoAut(txtReqNoAut);
    queryReqNoAut.next();
    int noAut=queryReqNoAut.value(0).toInt();
    QString txtReqNoCat="SELECT numeroCategories FROM Categories WHERE libelleCategories='"+cat+"'";
    qDebug()<<txtReqNoCat;
    QSqlQuery queryReqNoCat(txtReqNoCat);
    queryReqNoCat.next();
    int noCat=queryReqNoCat.value(0).toInt();

    //requete d'insertion dans la base
    QString txtReqInsertion="INSERT INTO Livres (numeroLivres, titreLivres, resumeLivres, datepubliLivres, numeroAuteurs, numeroCategories) VALUES ('"+QString::number(noMax)+"','"+titre+"','"+resume+"','"+date+"','"+QString::number(noAut)+"','"+QString::number(noCat)+"')";
    qDebug()<<txtReqInsertion;
    QSqlQuery query(txtReqInsertion);

    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(noLigne);
    QCheckBox* cocher = new QCheckBox();
    liste.append(cocher);
    ui->tableWidget->setCellWidget(noLigne,0, cocher);
    ui->tableWidget->setItem(noLigne,1,new QTableWidgetItem(QString::number(noMax)));
    ui->tableWidget->setItem(noLigne,2,new QTableWidgetItem(titre));
    ui->tableWidget->setItem(noLigne,3,new QTableWidgetItem(date));
    ui->tableWidget->setItem(noLigne,4,new QTableWidgetItem(auteur));
    ui->tableWidget->setItem(noLigne,5,new QTableWidgetItem(cat));
    ui->tableWidget->setItem(noLigne,6,new QTableWidgetItem(resume));
}


void MainWindow::on_tableWidget_cellClicked(int i, int column)
{
    //recuperation des cellules
    no= ui->tableWidget->item(i,1)->text();
    ui->labelNo->setText(no);
    ui->lineEditTitre->setText(ui->tableWidget->item(i,2)->text());
    ui->textEditResume->setText(ui->tableWidget->item(i,6)->text());
    ui->lineEditDatepubli->setText(ui->tableWidget->item(i,3)->text());

    QString textToFindAut = ui->tableWidget->item(i,4)->text();
    ui->comboBoxAuteur->setCurrentIndex(ui->comboBoxAuteur->findText(textToFindAut));

    QString textToFindCat = ui->tableWidget->item(i,5)->text();
    ui->comboBoxCategorie->setCurrentIndex(ui->comboBoxCategorie->findText(textToFindCat));
}


void MainWindow::on_pushButtonModifier_clicked()
{
    if(!ui->tableWidget->selectedItems().empty())
    {
        //mise a jour des champs du tableau
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->lineEditTitre->text());
        ui->tableWidget->item(ui->tableWidget->currentRow(),6)->setText(ui->textEditResume->toPlainText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),4)->setText(ui->comboBoxAuteur->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),5)->setText(ui->comboBoxCategorie->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(ui->lineEditDatepubli->text());

        //mise a jour de la base
        //recuperation des informations
        QString titre, resume, date, nomAuteur,cat;
        titre=ui->lineEditTitre->text().replace("'","''");
        resume=ui->textEditResume->toPlainText().replace("'","''");
        date=ui->lineEditDatepubli->text();
        nomAuteur=ui->comboBoxAuteur->currentText();
        cat=ui->comboBoxCategorie->currentText();

        //recuperation du numero de catégorie et du numero d'ateurs
        QString txtReqNoAut="SELECT numeroAuteurs FROM Auteurs WHERE nomAuteurs='"+nomAuteur+"'";
        qDebug()<<txtReqNoAut;
        QSqlQuery queryReqNoAut(txtReqNoAut);
        queryReqNoAut.next();
        int noAut=queryReqNoAut.value(0).toInt();
        QString txtReqNoCat="SELECT numeroCategories FROM Categories WHERE libelleCategories='"+cat+"'";
        qDebug()<<txtReqNoCat;
        QSqlQuery queryReqNoCat(txtReqNoCat);
        queryReqNoCat.next();
        int noCat=queryReqNoCat.value(0).toInt();
        qDebug()<<noAut;
        qDebug()<<noCat;
        QString txtReqUpdate="UPDATE Livres SET titreLivres = '"+titre+"', resumeLivres = '"+resume+"', datepubliLivres = '"+date+"', numeroAuteurs = '"+QString::number(noAut)+"', numeroCategories = '"+QString::number(noCat)+"' WHERE numeroLivres ='"+no+"'";
        qDebug()<<txtReqUpdate;
        QSqlQuery query(txtReqUpdate);
    }
    else
    {
        ui->statusBar->showMessage("Merci de séléctionner une ligne", 3000);
    }
}


void MainWindow::on_pushButtonSupprimer_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprimer_clicked()";
    //supprimer du tableau
    for(int noLigne=ui->tableWidget->rowCount()-1;noLigne>0;noLigne--)
    {
        if(((QCheckBox*)ui->tableWidget->cellWidget(noLigne,0))->isChecked())
        {
            QString txtSup="DELETE FROM Livres WHERE numeroLivres="+ui->tableWidget->item(noLigne,1)->text();
            qDebug()<<txtSup;
            QSqlQuery querySup(txtSup);
            ui->tableWidget->removeRow(noLigne);
        }
    }
}


void MainWindow::on_pushButtonCategorie_clicked()
{
    categorie feneCategorie(this);
    feneCategorie.exec();
    int sonNum=feneCategorie.renvoieNumCategorie();
    QString sonNom=feneCategorie.renvoieCategorie();

    //j'ajoute une ligne dans la tabCategorie
    int noLigne=ui->tableWidgetCategories->rowCount();
    ui->tableWidgetCategories->insertRow(noLigne);
    ui->tableWidgetCategories->setItem(noLigne,0,new QTableWidgetItem(QString::number(sonNum)));
    ui->tableWidgetCategories->setItem(noLigne,1,new QTableWidgetItem(sonNom));
    QCheckBox* cocher = new QCheckBox();
    liste.append(cocher);
    ui->tableWidgetCategories->setCellWidget(noLigne,2, cocher);
}


void MainWindow::on_pushButtonAuteur_clicked()
{
    auteur feneAuteur(this);
    feneAuteur.exec();
    int sonNum=feneAuteur.renvoieNumAuteur();
    QString sonNom=feneAuteur.renvoieAuteur();
    QString sonPrenom=feneAuteur.renvoiePreAuteur();

    //j'ajoute une ligne dans la tabAuteur
    int noLigne=ui->tableWidgetAuteurs->rowCount();
    ui->tableWidgetAuteurs->insertRow(noLigne);
    ui->tableWidgetAuteurs->setItem(noLigne,0,new QTableWidgetItem(QString::number(sonNum)));
    ui->tableWidgetAuteurs->setItem(noLigne,1,new QTableWidgetItem(sonNom.toUpper()));
    ui->tableWidgetAuteurs->setItem(noLigne,2,new QTableWidgetItem(sonPrenom));
    QCheckBox* cocher = new QCheckBox();
    liste.append(cocher);
    ui->tableWidgetAuteurs->setCellWidget(noLigne,3, cocher);
}

//-----------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB AUTEURS---------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void MainWindow::on_tableWidgetAuteurs_cellClicked(int j, int column)
{
    //recuperation des cellules
    no= ui->tableWidgetAuteurs->item(j,0)->text();
    ui->labelNoAuteurs->setText(no);
    ui->lineEditNomAuteur->setText(ui->tableWidgetAuteurs->item(j,1)->text());
    ui->lineEditPrenomAuteur->setText(ui->tableWidgetAuteurs->item(j,2)->text());
}


void MainWindow::on_pushButtonModifierAuteur_clicked()
{
    if(!ui->tableWidgetAuteurs->selectedItems().empty())
    {
        //mise a jour des champs du tableau
        ui->tableWidgetAuteurs->item(ui->tableWidgetAuteurs->currentRow(),1)->setText(ui->lineEditNomAuteur->text());
        ui->tableWidgetAuteurs->item(ui->tableWidgetAuteurs->currentRow(),2)->setText(ui->lineEditPrenomAuteur->text());
        //mise a jour de la base
        //recuperation des informations
        QString nom, prenom;
        nom=ui->lineEditNomAuteur->text();
        prenom=ui->lineEditPrenomAuteur->text();

        QString txtReqUpdate2="UPDATE Auteurs SET nomAuteurs = '"+nom+"', prenomAuteurs = '"+prenom+"' WHERE numeroAuteurs ='"+no+"'";
        qDebug()<<txtReqUpdate2;
        QSqlQuery query(txtReqUpdate2);
    }
    else
    {
        ui->statusBar->showMessage("Merci de séléctionner une ligne", 3000);
    }
}


void MainWindow::on_pushButtonSupprimerAuteur_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprimerAuteur_clicked()";
    //supprimer du tableau
    for(int noLigne=ui->tableWidgetAuteurs->rowCount()-1;noLigne>0;noLigne--)
    {
        if(((QCheckBox*)ui->tableWidgetAuteurs->cellWidget(noLigne,3))->isChecked())
        {
            QString txtSup="DELETE FROM Auteurs WHERE numeroAuteurs="+ui->tableWidgetAuteurs->item(noLigne,0)->text();
            qDebug()<<txtSup;
            QSqlQuery querySup(txtSup);
            ui->tableWidgetAuteurs->removeRow(noLigne);
        }
    }
}


//--------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB CATEGORIES---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
void MainWindow::on_tableWidgetCategories_cellClicked(int k, int column)
{
    //recuperation des cellules
    no= ui->tableWidgetCategories->item(k,0)->text();
    ui->labelNoCategories->setText(no);
    ui->lineEditLibelleCategories->setText(ui->tableWidgetCategories->item(k,1)->text());
}


void MainWindow::on_pushButtonModifierCategorie_clicked()
{
    if(!ui->tableWidgetCategories->selectedItems().empty())
    {
        //mise a jour des champs du tableau
        ui->tableWidgetCategories->item(ui->tableWidgetCategories->currentRow(),1)->setText(ui->lineEditLibelleCategories->text());

        //mise a jour de la base
        //recuperation des informations
        QString libelle;
        libelle=ui->lineEditLibelleCategories->text();

        QString txtReqUpdate2="UPDATE Categories SET libelleCategories = '"+libelle+"' WHERE numeroCategories ='"+no+"'";
        qDebug()<<txtReqUpdate2;
        QSqlQuery query(txtReqUpdate2);
    }
    else
    {
        ui->statusBar->showMessage("Merci de séléctionner une ligne", 3000);
    }
}


void MainWindow::on_pushButtonSupprimeCategorie_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprimeCategorie_clicked()";
    //supprimer du tableau
    for(int noLigne=ui->tableWidgetCategories->rowCount()-1;noLigne>0;noLigne--)
    {
        if(((QCheckBox*)ui->tableWidgetCategories->cellWidget(noLigne,2))->isChecked())
        {
            QString txtSup="DELETE FROM Categories WHERE numeroCategories="+ui->tableWidgetCategories->item(noLigne,0)->text();
            qDebug()<<txtSup;
            QSqlQuery querySup(txtSup);
            ui->tableWidgetCategories->removeRow(noLigne);
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB ADHERENTS---------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonAjouterAdherent_clicked()
{
    //recuperation des informations
    QString nom, prenom, mail;
    nom=ui->lineEditNomAdherent->text().replace("'","''");
    prenom=ui->lineEditPrenomAdherent->text().replace("'","''");
    mail=ui->lineEditMailAdherent->text().replace("'","''");


    //calcul du numero de livre le plus haut
    QString txtReqMax="SELECT MAX(numeroAdherent) FROM Adherent";
    QSqlQuery queryReqMax(txtReqMax);
    queryReqMax.next();
    noMaxAd=queryReqMax.value(0).toInt();
    qDebug()<<noMaxAd;
    noMaxAd++;
    qDebug()<<noMaxAd;
    //requete d'insertion dans la base
    QString txtReqInsertion="INSERT INTO Adherent (numeroAdherent, nomAdherent, prenomAdherent, mailAdherent) VALUES ('"+QString::number(noMaxAd)+"',UPPER('"+nom+"'),'"+prenom+"','"+mail+"')";
    qDebug()<<txtReqInsertion;
    QSqlQuery query(txtReqInsertion);

    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidgetAdherent->rowCount();
    ui->tableWidgetAdherent->insertRow(noLigne);
    ui->tableWidgetAdherent->setItem(noLigne,0,new QTableWidgetItem(QString::number(noMaxAd)));
    ui->tableWidgetAdherent->setItem(noLigne,1,new QTableWidgetItem(nom.toUpper()));
    ui->tableWidgetAdherent->setItem(noLigne,2,new QTableWidgetItem(prenom));
    ui->tableWidgetAdherent->setItem(noLigne,3,new QTableWidgetItem(mail));
    QCheckBox* cocher = new QCheckBox();
    liste.append(cocher);
    ui->tableWidgetAdherent->setCellWidget(noLigne,4, cocher);
}


void MainWindow::on_tableWidgetAdherent_cellClicked(int l, int column)
{
    //recuperation des cellules
    no= ui->tableWidgetAdherent->item(l,0)->text();
    ui->labelNoAdherent->setText(no);
    ui->lineEditNomAdherent->setText(ui->tableWidgetAdherent->item(l,1)->text());
    ui->lineEditPrenomAdherent->setText(ui->tableWidgetAdherent->item(l,2)->text());
    ui->lineEditMailAdherent->setText(ui->tableWidgetAdherent->item(l,3)->text());
}


void MainWindow::on_pushButtonModifierAdherent_clicked()
{
    if(!ui->tableWidgetAdherent->selectedItems().empty())
    {
        //mise a jour des champs du tableau
        ui->tableWidgetAdherent->item(ui->tableWidgetAdherent->currentRow(),1)->setText(ui->lineEditNomAdherent->text());
        ui->tableWidgetAdherent->item(ui->tableWidgetAdherent->currentRow(),2)->setText(ui->lineEditPrenomAdherent->text());
        ui->tableWidgetAdherent->item(ui->tableWidgetAdherent->currentRow(),3)->setText(ui->lineEditMailAdherent->text());

        //mise a jour de la base
        //recuperation des informations
        QString nom, prenom, mail;
        nom=ui->lineEditNomAdherent->text().replace("'","''");
        prenom=ui->lineEditPrenomAdherent->text().replace("'","''");
        mail=ui->lineEditMailAdherent->text().replace("'","''");

        QString txtReqUpdate2="UPDATE Adherent SET nomAdherent = '"+nom+"', prenomAdherent = '"+prenom+"', mailAdherent = '"+mail+"' WHERE numeroAdherent ='"+no+"'";
        qDebug()<<txtReqUpdate2;
        QSqlQuery query(txtReqUpdate2);
    }
    else
    {
        ui->statusBar->showMessage("Merci de séléctionner une ligne", 3000);
    }
}


void MainWindow::on_pushButtonSupprimeAdherent_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprimeAdherent_clicked()";
    //supprimer du tableau
    for(int noLigne=ui->tableWidgetAdherent->rowCount()-1;noLigne>0;noLigne--)
    {
        if(((QCheckBox*)ui->tableWidgetAdherent->cellWidget(noLigne,4))->isChecked())
        {
            QString txtSup="DELETE FROM Adherent WHERE numeroAdherent="+ui->tableWidgetAdherent->item(noLigne,0)->text();
            qDebug()<<txtSup;
            QSqlQuery querySup(txtSup);
            ui->tableWidgetAdherent->removeRow(noLigne);
        }
    }
}



//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB PRETS---------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
void MainWindow::on_lineEditGroupAdherent_textEdited(const QString &arg1)
{
    //rendre la liste vide
    ui->listWidgetAdherent->clear();

    //recuperation des informations
    QString line;
    line=ui->lineEditGroupAdherent->text().replace("'","''");

    //requete de recherche adherent dans le list widget
    QString txtReqTextEditAdherent="SELECT numeroAdherent, nomAdherent, prenomAdherent FROM Adherent WHERE numeroAdherent LIKE '%"+line+"%' OR nomAdherent LIKE '%"+line+"%' OR prenomAdherent LIKE '%"+line+"%'";
    qDebug()<<txtReqTextEditAdherent;
    QSqlQuery query(txtReqTextEditAdherent);
    while(query.next())
    {
        ui->listWidgetAdherent->addItem(new QListWidgetItem(query.value("numeroAdherent").toString()+ " " +query.value("nomAdherent").toString()+ " " +query.value("prenomAdherent").toString()));
    }

}

void MainWindow::on_listWidgetAdherent_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"void MainWindow::on_listWidgetAdherent_itemClicked(QListWidgetItem *item)";
    //recuperation des cellules
    QStringList listLineAdherent = ui->listWidgetAdherent->currentItem()->text().split(" ");
    qDebug()<<listLineAdherent;
    QString numAd, nomAd, preAd;
    numAd=listLineAdherent[0];
    preAd=listLineAdherent[1];
    nomAd=listLineAdherent[2];

    //remplir les cellules
    ui->labelNumeroGroupAdherent->setText(numAd);
    ui->labelNomGroupAdherent_2->setText(nomAd);
    ui->labelPrenomGroupAdherent->setText(preAd);

    ui->groupBoxLivre->setVisible(true);
}

void MainWindow::on_lineEditRechercheGroupLivre_textEdited(const QString &arg1)
{
    //rendre la liste vide
    ui->listWidgetLivre->clear();

    //recuperation des informations
    QString line;
    line=ui->lineEditRechercheGroupLivre->text().replace("'","''");

    //requete de recherche adherent dans le list widget
    QString txtReqTextEditLivre="SELECT numeroLivres, titreLivres, atr.nomAuteurs FROM Livres INNER JOIN Auteurs atr ON Livres.numeroAuteurs=atr.numeroAuteurs WHERE numeroLivres LIKE '%"+line+"%' OR titreLivres LIKE '%"+line+"%' OR nomAuteurs LIKE '%"+line+"%'";
    qDebug()<<txtReqTextEditLivre;
    QSqlQuery queryLivre(txtReqTextEditLivre);
    while(queryLivre.next())
    {
        ui->listWidgetLivre->addItem(new QListWidgetItem(queryLivre.value("numeroLivres").toString()+ " " +queryLivre.value("nomAuteurs").toString()+ " " +queryLivre.value("titreLivres").toString()));
    }
}

void MainWindow::on_pushAjouterGroupLivre_clicked()
{
    //recuperation des cellules
    QStringList listLineLivre = ui->listWidgetLivre->currentItem()->text().split(" ");
    QString numLi, titreLi, AuteurLi;
    numLi=listLineLivre[0];
    titreLi=listLineLivre[1];
    AuteurLi=listLineLivre[2];

    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidgetPret->rowCount();
    ui->tableWidgetPret->insertRow(noLigne);
    ui->tableWidgetPret->setItem(noLigne,0,new QTableWidgetItem(numLi));
    ui->tableWidgetPret->setItem(noLigne,1,new QTableWidgetItem(titreLi));
    ui->tableWidgetPret->setItem(noLigne,2,new QTableWidgetItem(AuteurLi));
}

void MainWindow::on_pushButtonPret_clicked()
{
    //ajout dans la base de données
    for(int i=0;i<ui->tableWidgetPret->rowCount();i++)
    {
        //calcul du numero de l'emprunt le plus haut
        QString txtMaxEmprunt="SELECT MAX(numeroEmprunt)+1 FROM Emprunt";
        QSqlQuery maxEmprunt(txtMaxEmprunt);
        maxEmprunt.next();

        //requête insertion
        QString txtRequeteInsertionEmprunt="INSERT INTO Emprunt (numeroEmprunt,dateDebutEmprunt,numeroAdherent) VALUES ('"+maxEmprunt.value(0).toString()+"',NOW(),'"+ui->labelNumeroGroupAdherent->text()+"')";
        QString txtRequeteInsertionEmprunte="INSERT INTO emprunte (numeroLivres,numeroEmprunt) VALUES ('"+ui->tableWidgetPret->item(i,0)->text()+"','"+maxEmprunt.value(0).toString()+"')";

        qDebug()<<txtRequeteInsertionEmprunt;
        QSqlQuery query(txtRequeteInsertionEmprunt);

        qDebug()<<txtRequeteInsertionEmprunte;
        QSqlQuery query2(txtRequeteInsertionEmprunte);

        //message d'affichage
        ui->statusBar->showMessage("Emprunt ajouté!",2000);
    }
}



//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------TAB RESTITUTION---------------------------------------------
//---------------------------------------------------------------------------------------------------------------
void MainWindow::on_lineEditRestitution_textEdited(const QString &arg1)
{
    qDebug()<<"void MainWindow::on_lineEditRestitution_textEdited(const QString &arg1)";
    //rendre la liste vide
    ui->listWidgetRestitution->clear();

    //recuperation des informations
    QString line;
    line=ui->lineEditRestitution->text().replace("'","''");

    //requete de recherche adherent dans le list widget
    QString txtReqTextRestitution="SELECT numeroAdherent, nomAdherent, prenomAdherent FROM Adherent WHERE numeroAdherent LIKE '%"+line+"%' OR nomAdherent LIKE '%"+line+"%' OR prenomAdherent LIKE '%"+line+"%'";
    qDebug()<<txtReqTextRestitution;
    QSqlQuery query(txtReqTextRestitution);
    while(query.next())
    {
        ui->listWidgetRestitution->addItem(new QListWidgetItem(query.value("numeroAdherent").toString()+ " " +query.value("nomAdherent").toString()+ " " +query.value("prenomAdherent").toString()));
    }

}

void MainWindow::on_listWidgetRestitution_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"void MainWindow::on_listWidgetRestitution_itemClicked(QListWidgetItem *item)";
    //recuperation des cellules
    QStringList listLineRestitution = ui->listWidgetRestitution->currentItem()->text().split(" ");
    qDebug()<<listLineRestitution;
    QString numAd, nomAd, preAd;
    numAd=listLineRestitution[0];
    preAd=listLineRestitution[1];
    nomAd=listLineRestitution[2];

    ui->labelNumeroRestitution->setText(numAd);
    ui->labelNomRestitution->setText(nomAd);
    ui->labelPrenomRestitution->setText(preAd);

    //calcul du numero de l'emprunt le plus haut
    QString txtNoEmrunt=("SELECT numeroEmprunt FROM Emprunt WHERE numeroAdherent='"+ui->labelNumeroRestitution->text()+"'");
    QSqlQuery reqNoEmprunt(txtNoEmrunt);
    while(reqNoEmprunt.next())
    {
        QString txtNoLivreEmprunt=("SELECT numeroEmprunt FROM Emprunt WHERE numeroAdherent='"+reqNoEmprunt.value(0).toString()+"'");
        QSqlQuery NoLivreEmprunt(txtNoLivreEmprunt);
        while(NoLivreEmprunt.next())
        {
            QSqlQuery queryTable;
            queryTable.exec("SELECT numeroLivres, titreLivres, emp.numeroEmprunt, atr.nomAuteurs FROM Livres INNER JOIN Auteurs atr ON Livres.numeroAuteurs=atr.numeroAuteurs INNER JOIN Emprunt emp ON Livres.numeroEmprunt=emp.numeroEmprunt");
            while(queryTable.next())
            {
                ui->tableWidgetRestitution->insertRow(i);
                QCheckBox* cocher = new QCheckBox();
                liste.append(cocher);
                ui->tableWidgetRestitution->setCellWidget(i,0, cocher);
                ui->tableWidgetRestitution->setItem(i,1,new QTableWidgetItem(queryTable.value("numeroEmprunt").toString()));
                ui->tableWidgetRestitution->setItem(i,2,new QTableWidgetItem(queryTable.value("numeroLivres").toString()));
                ui->tableWidgetRestitution->setItem(i,3,new QTableWidgetItem(queryTable.value("nomAuteurs").toString()));
                ui->tableWidgetRestitution->setItem(i,4,new QTableWidgetItem(queryTable.value("titreLivres").toString()));
                //ui->tableWidgetRestitution->setItem(i,5,new QTableWidgetItem(queryTable.value("dateFin.").toString()));
                i++;
            }
        }
    }
}
