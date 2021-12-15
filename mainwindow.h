#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QList>
#include <QCheckBox>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonAjouter_clicked();

    void on_pushButtonAuteur_clicked();

    void on_pushButtonCategorie_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonModifier_clicked();

    void on_tableWidgetAuteurs_cellClicked(int row, int column);

    void on_tableWidgetCategories_cellClicked(int row, int column);

    void on_pushButtonModifierAuteur_clicked();

    void on_pushButtonModifierCategorie_clicked();

    void on_pushButtonSupprimeCategorie_clicked();

    void on_pushButtonSupprimerAuteur_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButtonAjouterAdherent_clicked();

    void on_tableWidgetAdherent_cellClicked(int row, int column);

    void on_pushButtonModifierAdherent_clicked();

    void on_pushButtonSupprimeAdherent_clicked();

    void on_lineEditGroupAdherent_textEdited(const QString &arg1);

    void on_listWidgetAdherent_itemClicked(QListWidgetItem *item);

    void on_lineEditRechercheGroupLivre_textEdited(const QString &arg1);

    void on_pushAjouterGroupLivre_clicked();

    void on_pushButtonPret_clicked();

    void on_lineEditRestitution_textEdited(const QString &arg1);

    void on_listWidgetRestitution_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    void afficherTable();
    int i=0,j=0,k=0,l=0;
    QString no;
    int noMax, noMaxAd;
    QList <QCheckBox *> liste;
    QList <QCheckBox *> liste2;
    QList <QCheckBox *> liste3;
    QList <QCheckBox *> liste4;
};

#endif // MAINWINDOW_H
