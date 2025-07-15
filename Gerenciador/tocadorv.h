#ifndef TocadorV_H
#define TocadorV_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class TocadorV : public QWidget
{
    Q_OBJECT
public:
    TocadorV(QWidget *parent = nullptr);
    ~TocadorV();
public slots:
    void newTocadorV();
    void inputMusChanged();

private:
    QLineEdit *nameLineEdit;
    QPushButton *button_ok;
    QListWidget * musList;
    QListWidget * tocList;

};

#endif // TocadorV_H
