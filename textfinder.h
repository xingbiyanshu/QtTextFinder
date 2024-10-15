#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class TextFinder;
}
QT_END_NAMESPACE

class Count{
public:
    int c;
};

class TextFinder : public QWidget
{
    Q_OBJECT

public:
    TextFinder(QWidget *parent = nullptr);
    ~TextFinder();

signals:
    void clicked(Count *count);

private slots:
    void on_findButton_clicked();
    void countClick(Count* count);

private:
    Ui::TextFinder *ui;
    void loadTextFile();
    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);

};
#endif // TEXTFINDER_H
