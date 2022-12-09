#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "salle.h"
#include <QMessageBox>
#include <QObject>
#include <QPdfWriter>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QTextDocument>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>



MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    int num=ui->num->text().toInt();
    QString loc=ui->loc->text();
    int heurd=ui->heurd->text().toInt();
    int heurf=ui->heurf->text().toInt();
    Salle E(num,loc,heurd,heurf);
    bool test=E.ajouter();

 if(test)
 {
     ui->tab_salle->setModel(E.afficher());
     ui->list->setModel(E.Horloge());
     ui->time->setModel(E.Timetable());

     QMessageBox::information(nullptr, QObject::tr("ok"),
                     QObject::tr("Ajouter effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
 }

 else
     QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("Ajouter non  effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_supprimer_clicked()
{


    Salle Etmp; Etmp.setnum (ui->num_sup ->text().toInt());
    bool test=Etmp.supprimer(Etmp.getnum());
    if(test)
    {
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("suppression effectuee \n"
                                            "click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("erreur"),
                               QObject::tr("suppression non effectuee.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);

}







void MainWindow::on_pushButton_clicked()
{

    QT_CHARTS_USE_NAMESPACE
    int argc; char *argv[100];
    QApplication a(argc, argv);

//![1]
    QBarSet *set0 = new QBarSet("");


    *set0 << 1 << 2 << 3 << 4 << 5 << 4;

//![1]

//![2]
    QBarSeries *series = new QBarSeries();
    series->append(set0);


//![2]

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("heures pour chaque salle");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![6]

//![7]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(420, 300);
    window.show();
//![7]


}

void MainWindow::on_pdf_rayen_clicked()
{
    QSqlDatabase db;

                        QTableView tableView;
                        QSqlQueryModel * Modal=new  QSqlQueryModel();

                        QSqlQuery qry;
                         qry.prepare("SELECT* FROM RECLAMATION");
                         qry.exec();
                         Modal->setQuery(qry);
                         tableView.setModel(Modal);

                         db.close();

                         QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = tableView.model()->rowCount();
                         const int columnCount =  tableView.model()->columnCount();

                         const QString strTitle ="ListeDesRECLAMATIONS";

                         out <<  "<html>\n"
                                 "<img src='C:/Users/rayan/Desktop/SmartCourt.png' height='155' width='140'/>"
                             "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             <<  QString("<title>%1</title>\n").arg(strTitle)
                             <<  "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                            << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES clients")
                            <<"<br>"

                            <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                         out << "<thead><tr bgcolor=#f0f0f0>";
                         for (int column = 0; column < columnCount; column++)
                             if (!tableView.isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(tableView.model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         for (int row = 0; row < rowCount; row++)
                         {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++)
                             {
                                 if (!tableView.isColumnHidden(column))
                                 {
                                     QString data = tableView.model()->data(tableView.model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                                 "<br><br>"
                                 <<"<br>"
                                 <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                             out << "<thead><tr bgcolor=#f0f0f0>";

                                 out <<  "</table>\n"

                             "</body>\n"
                             "</html>\n";

                         QTextDocument *reclamation= new QTextDocument();
                        reclamation->setHtml(strStream);

                         QPrinter printer;
                         QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                         if (dialog->exec() == QDialog::Accepted)
                         {

                             reclamation->print(&printer);
                         }
                         printer.setOutputFormat(QPrinter::PdfFormat);
                         printer.setPaperSize(QPrinter::A4);
                         printer.setOutputFileName("/tmp/reclamation.pdf");
                         printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                         delete reclamation;
}
void MainWindow::on_searchbutton_clicked()

{

    QMessageBox::information(nullptr, QObject::tr("Ok"),

             QObject::tr("tri effectué.\n"

                         "Click Cancel to exit."), QMessageBox::Cancel);

            ui->tab_salle->setModel(E.tri_num());

}





