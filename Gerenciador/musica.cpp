#include "musica.h"
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


Musica::Musica(QWidget *parent)
    : QWidget(parent)
{
    //! [1]
    QGroupBox *validatorGroup = new QGroupBox(tr("Nova Musica"));

    button_ok = new QPushButton("OK");

    QLabel *nameLabel = new QLabel(tr("Nome:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setPlaceholderText("Inserir Nome");

    QLabel *validatorLabel = new QLabel(tr("Duração:"));
    duracaoLineEdit = new QLineEdit;
    duracaoLineEdit->setValidator(new QIntValidator());
    duracaoLineEdit->setPlaceholderText("Inserir Duração em segundos");

    QLabel *instrLabel = new QLabel(tr("Instrumentos:"));
    QComboBox *inputInstrumentsBox = new QComboBox;
    inputInstrumentsBox->setPlaceholderText(tr("Selecionar Instrumento"));
    QSqlQuery query("SELECT name FROM instrumento");
    while (query.next()) {
        QString name = query.value(0).toString();
        inputInstrumentsBox->addItem(name);
    }

    instrumentList = new QListWidget();

    //! [1]
    connect(inputInstrumentsBox, &QComboBox::activated,
            this, &Musica::inputMaskChanged);
    //! [7]
    QGridLayout *validatorLayout = new QGridLayout;
    validatorLayout->addWidget(nameLabel, 0, 0);
    validatorLayout->addWidget(nameLineEdit, 0, 1);
    validatorLayout->addWidget(validatorLabel, 1, 0);
    validatorLayout->addWidget(duracaoLineEdit, 1, 1);
    validatorLayout->addWidget(instrLabel, 2, 0);
    validatorLayout->addWidget(inputInstrumentsBox, 2, 1);
    validatorLayout->addWidget(instrumentList, 3, 0, 1, 2);
    //validatorLayout->addWidget(instrumentList, 4,0);
    validatorLayout->addWidget(button_ok, 4, 1);
    validatorGroup->setLayout(validatorLayout);

    //! [8]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(validatorGroup, 0, 0);
    setLayout(layout);
    setWindowTitle(tr("Cadastrar Musica"));

    connect(button_ok, &QPushButton::clicked, this, &Musica::newMusic);
}
//! [8]
void Musica::newMusic()
{
    QSqlQuery query;
    QSqlQuery queryInst;
    QString nome = nameLineEdit ->text();
    QString duracao = duracaoLineEdit ->text();
    query.exec("SELECT id FROM musica ORDER BY id DESC LIMIT 1");
    query.next();
    int id = query.value(0).toInt()+1;
    //std::cout << "id eeee" << id << "aaa" << std::endl;
    query.prepare("INSERT INTO musica (id, name, duracao) VALUES (:id, :name, :duracao)");
    query.bindValue(":id", id);
    query.bindValue(":name", nome);
    query.bindValue(":duracao", duracao);
    query.exec();

    query.exec("SELECT id FROM instr_musica ORDER BY id DESC LIMIT 1");
    query.next();
    int instMusica = query.value(0).toInt()+1;
    query.prepare("INSERT INTO instr_musica (id, id_musica, id_instr) VALUES (:id, :mus, :inst)");
    queryInst.prepare("SELECT id FROM instrumento WHERE name = (:instrument) ");
    //std::cout << "aaaa" << std::endl();
    qDebug() << "aaaaaaaaa" ;//<< db.lastError().text();

    for (int i =0; i< instrumentList->count(); i++) {
        QListWidgetItem* instrument = instrumentList->item(i);
        queryInst.bindValue(":instrument", instrument->text());
        queryInst.exec();
        queryInst.next();
        int inst = queryInst.value(0).toInt();
        query.bindValue(":id", instMusica++);
        query.bindValue(":mus", id);
        query.bindValue(":inst", inst);
        query.exec();
    }

    close();

}

//! [12]
void Musica::inputMaskChanged(int index)
{
    switch (index) {
    case 0:
        // okedo
        instrumentList->addItem("OKEDODAIKO");
        break;
    case 1:
        // nagado
        instrumentList->addItem("NAGADODAIKO");
        break;
    case 2:
        // odaiko
        instrumentList->addItem("ODAIKO");
        break;
    case 3:
        //shime
        instrumentList->addItem("SHIMEDAIKO");
        break;
    case 4:
        //fue
        instrumentList->addItem("FUE");
        break;
    }
}
//! [12]

Musica::~Musica()
{
}
