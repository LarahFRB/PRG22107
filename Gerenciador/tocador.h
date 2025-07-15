#ifndef TOCADOR_H
#define TOCADOR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class Tocador : public QWidget
{
    Q_OBJECT

public:
    Tocador(QWidget *parent = nullptr);
    ~Tocador();
public slots:
    void newTocador();
    void inputMusChanged(int);

private:
    QLineEdit *nameLineEdit;
    QPushButton *button_ok;
    QListWidget * musList;
};

#endif // TOCADOR_H



