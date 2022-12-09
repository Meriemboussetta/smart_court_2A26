#include "salle.h"
#include<QObject>
#include<QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
Salle::Salle()
{
num=0; heurd=0; heurf=0; loc="";
}

Salle::Salle(int num,QString loc,int heurd,int heurf)
{this->num=num; this->loc=loc; this->heurd=heurd; this->heurf=heurf;}
int Salle::getnum(){return num;}
QString Salle::getloc(){return loc;}
int Salle::getheurd(){return heurd;}
int Salle::getheuref(){return heurf;}
void Salle::setnum(int num){this->num=num;}
void Salle::setloc(QString loc){this->loc=loc;}
void Salle::setheurd(int heurd){this->heurd=heurd;}
void Salle::setheurf(int heurf){this->heurf=heurf;}


bool Salle::ajouter()
{
    //bool test=false;
    QSqlQuery query;

          query.prepare("INSERT INTO salle (num,loc, heurd,heurf) "
                        "VALUES (:num, :loc, :heurd, :heurf)");
          query.bindValue(":num", num);
          query.bindValue(":loc", loc);
          query.bindValue(":heurd", heurd);
          query.bindValue(":heurf", heurf);

    return query.exec();

}
bool Salle::supprimer(int num)
    {

        QSqlQuery query;

              query.prepare("Delete from SALLE where num=:num");
              query.bindValue(0,num);

          return query.exec();


    }

    QSqlQueryModel * Salle::afficher()
           {
        QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT * FROM SALLE");
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("location"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("debut"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("fin"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("fin"));


        return model;

           }
    QSqlQueryModel * Salle::Horloge()
           {
        QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT HEURD FROM SALLE");
      model->setHeaderData(1,Qt::Horizontal ,QObject::tr("NUM"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("LOC"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("HEURD"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("HEURF"));


        return model;

           }
    QSqlQueryModel * Salle::Timetable()
           {
        QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT * FROM SALLE");
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("Location"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("debut d'heure"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("fin"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("fin"));


        return model;

           }
    void Salle::chercheNUM(QTableView *table, int num)
       {
          QSqlQueryModel *model=new QSqlQueryModel();
          QSqlQuery *query =new QSqlQuery;
          query->prepare("select * from SALLE where regexp_like(NUM,:NUM);");
          query->bindValue(":NUM",num);
          if(num==0)
          {
              query->prepare("select * from SALLE;");
          }
          query->exec();
          model->setQuery(*query);
          table->setModel(model);
          table->show();
       }
       void Salle::clearTable(QTableView *table)
       {
           QSqlQueryModel *model=new QSqlQueryModel();
           model->clear();
           table->setModel(model);
       }
       QSqlQueryModel * Salle::tri_num()
       {QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("select * from SALLE order by NUM");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("LOC"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURD"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURF"));

           return model;
       }


