#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    TCF.BackgroundBrush;
    TCF.setFontItalic(true);
    ui->setupUi(this);
    QBrush brush;
    brush.setColor(Qt::yellow);
    TCF.setForeground(brush);
    brush.setColor(Qt::darkCyan);
    TCF.setBackground(brush);
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    ui->webView->page()->setPluginFactory(new WebPlugin(ui->webView->page()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered(bool checked)
{
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), QDir::currentPath(),/*"/home",*/ "Images (*.png *.xpm *.jpg)");
    ui->webView->load(QUrl("qrc:/HTML.html"));
}

void MainWindow::on_webView_loadFinished(bool arg1)
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QWebElementCollection ElementCollection = frame->findAllElements("div.report");//HTML only. The same as DIV[class~="warning"] - не работает

    foreach(QWebElement report, ElementCollection)
    {

        QString id = report.attribute("id");
        QRegExp rx("report_(\\d+)_(\\d+)_(\\d+)");
        if(!rx.exactMatch(id)) continue;
        QDate date(2000+rx.cap(3).toInt(),rx.cap(2).toInt(),rx.cap(1).toInt());
        Dates.insert(date,report);
        QWebElementCollection Collection = report.findAll("div.reportcontent");

        foreach(QWebElement RC, Collection)
        {
            //if (date == ui->calendarWidget->selectedDate())
            //{
            //    ReportContent.setStyleProperty("display", "block");
           //     //isOpenedNow = date;
            //}
            //else
            RC.setStyleProperty("display", "none");
        }
        //QWebElement child = report.firstChild();
        ui->calendarWidget->setDateTextFormat(date,TCF);

        ///////QWebElement RC = report.findFirst("div.reportcontent");
        ///////RC.firstChild().setStyleProperty("display","none");//??????

        //QWebElementCollection RcChild = frame->findAllElements("div.reportcontent");
        //RcChild.setStyleProperty("display","none");
        frame->addToJavaScriptWindowObject("calendar", ui->calendarWidget);//,QScriptEngine::QtOwnership);
    }
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    if(!PreviusReport.isNull())
    {
        PreviusReport.setStyleProperty("display","none");
    }
    QDate SD = ui->calendarWidget->selectedDate();
    qDebug()<<QString("create item")<<SD;
    QWebElement Element = Dates.value(SD);

    QWebElement EC = Element.findFirst("div.reportcontent");
    EC.setStyleProperty("display", "block");
    //QWebElementCollection EC = Element.findAll("div.reportcontent");
    //foreach (QWebElement E, EC)
    //{
    //    E.setStyleProperty("display", "block");
    //}
    PreviusReport = EC;
    //qDebug()<<QString("Debug")<<EC.isNull();
    //EC.setStyleProperty("display","block");


    //QMap<QDate,QWebElement>::iterator i = Dates.find(SD);


    /*foreach(QWebElement element, Elements)
    {
        element.setStyleProperty("display","block");
    }*/
}
