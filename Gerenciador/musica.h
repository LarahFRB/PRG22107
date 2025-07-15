#ifndef MUSICA_H
#define MUSICA_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

class Musica : public QWidget
{
    Q_OBJECT

public:
    Musica(QWidget *parent = nullptr);
    ~Musica();
public slots:
    void inputMaskChanged(int);
    void newMusic();


private:
    QPushButton * button_ok;
    QLineEdit *nameLineEdit;
    QLineEdit *duracaoLineEdit;
    QLineEdit *alignmentLineEdit;
    QLineEdit *inputMaskLineEdit;
    QListWidget * instrumentList;

};

#endif // MUSICA_H
