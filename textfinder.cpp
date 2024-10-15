#include "textfinder.h"
#include "./ui_textfinder.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>

TextFinder::TextFinder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextFinder)
{
    ui->setupUi(this);
    loadTextFile();
    connect(this, &TextFinder::clicked, this, &TextFinder::countClick);
}

TextFinder::~TextFinder()
{
    delete ui;
}

static int tid=0;

void TextFinder::on_findButton_clicked()
{
    qDebug() << "on_findButton_clicked";

    static int cnt=0;
    cnt++;

    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &TextFinder::countClick);
    // timer->setInterval(1000);
    // timer->start(1000);

    // QTimer::singleShot(2000, this, SLOT(countClick()));

    // tid = startTimer(1000);

    // connect(this, &TextFinder::clicked, this, &TextFinder::countClick); // connect只需要调用一次，否则槽函数会被调用多次
    emit clicked(new Count{.c=cnt});

    QString searchString = ui->lineEdit->text();
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
    QMessageBox::warning(this, QStringLiteral("Warning"), QStringLiteral("no match!"), QMessageBox::Cancel | QMessageBox::Ok);
}

void TextFinder::loadTextFile()
{
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}


void TextFinder::timerEvent(QTimerEvent *event){
    qDebug()<<"id="<<event->timerId();
    if (tid==event->timerId()){
        qDebug() << "timer loop";
    }
}


void TextFinder::countClick(Count *count){
    // static int count=0;
    qDebug()<<"count="<<count->c;
    // qDebug()<<"signal=" << signal;
}

