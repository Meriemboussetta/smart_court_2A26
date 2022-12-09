#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTableView>
class Salle
{
public:
    Salle();
    Salle(int,QString,int,int);
    int getnum();
    QString getloc();
    int getheurd();
    int getheuref();
    void setnum(int);
    void setloc(QString);
    void setheurd(int);
    void setheurf(int);
   bool ajouter();
   QSqlQueryModel *afficher();
   bool supprimer(int);
   QSqlQueryModel *Horloge();
   QSqlQueryModel *Timetable();
   Salle recherche(int);
       void chercheNUM(QTableView *table, int NUM);
       void clearTable(QTableView *table);
          QSqlQueryModel* tri_num();

private:
    int num,heurd,heurf;
    QString loc;
};

#endif // SALLE_H
