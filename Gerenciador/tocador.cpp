#include "tocador.h"
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QSqlQuery>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

//! [0]
Tocador::Tocador(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *tocadorGroup = new QGroupBox(tr("Novo Tocador"));

    button_ok = new QPushButton("OK");

    QLabel *nameLabel = new QLabel(tr("Nome:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setPlaceholderText("Inserir Nome");

    QLabel *musLabel = new QLabel(tr("Musica:"));
    QComboBox *inputMusBox = new QComboBox;
    inputMusBox->setPlaceholderText(tr("Selecionar Musica"));
    QSqlQuery query("SELECT name FROM musica");
    while (query.next()) {
        QString name = query.value(0).toString();
        inputMusBox->addItem(name);
    }

    musList = new QListWidget();

    //! [0]
    connect(inputMusBox, &QComboBox::activated,
            this, &Tocador::inputMusChanged);
    //! [6]
    QGridLayout *tocadorLayout = new QGridLayout;
    tocadorLayout->addWidget(nameLabel, 0, 0);
    tocadorLayout->addWidget(nameLineEdit, 0, 1);
    // tocadorLayout->addWidget(musLabel, 1, 0);
    // tocadorLayout->addWidget(inputMusBox, 1, 1);
    // tocadorLayout->addWidget(musList, 2, 0, 1, 2);
    tocadorLayout->addWidget(button_ok, 3, 1);
    tocadorGroup->setLayout(tocadorLayout);
    //! [6]

    //! [8]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tocadorGroup, 0, 0);
    setLayout(layout);

    setWindowTitle(tr("Cadastrar Tocador"));

    connect(button_ok, &QPushButton::clicked, this, &Tocador::newTocador);
}
//! [8]

//! [9]
void Tocador::newTocador()
{
    QSqlQuery query;
    QString nome = nameLineEdit ->text();
    query.exec("SELECT id FROM tocador ORDER BY id DESC LIMIT 1");
    query.next();
    int id = query.value(0).toInt()+1;
    //std::cout << "id eeee" << id << "aaa" << std::endl;
    query.prepare("INSERT INTO tocador (id, name) VALUES (:id, :name)");
    query.bindValue(":id", id);
    query.bindValue(":name", nome);
    query.exec();
    close();
}
//! [9]
void Tocador::inputMusChanged(int index)
{
    switch (index) {
    case 0:
        // okedo
        musList->addItem("OKEDODAIKO");
        break;
    case 1:
        // nagado
        musList->addItem("NAGADODAIKO");
        break;
    case 2:
        // odaiko
        musList->addItem("ODAIKO");
        break;
    case 3:
        //shime
        musList->addItem("SHIMEDAIKO");
        break;
    case 4:
        //fue
        musList->addItem("FUE");
        break;
    }
}

Tocador::~Tocador()
{
}
