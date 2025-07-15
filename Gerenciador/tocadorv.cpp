#include "tocadorv.h"
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QSqlQuery>
#include <QPushButton>
#include <QVBoxLayout>

TocadorV::TocadorV(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *tocadorVGroup = new QGroupBox(tr("Novo Vinculo"));
    button_ok = new QPushButton("OK");

    QLabel *tocLabel = new QLabel(tr("Tocador:"));
    QComboBox *inputTocBox = new QComboBox;
    inputTocBox->setPlaceholderText(tr("Selecionar Tocador"));
    QSqlQuery queryToc("SELECT name FROM tocador");
    while (queryToc.next()) {
        QString name = queryToc.value(0).toString();
        inputTocBox->addItem(name);
    }
    tocList = new QListWidget();

    QLabel *musLabel = new QLabel(tr("Musica:"));
    QComboBox *inputMusBox = new QComboBox;
    inputMusBox->setPlaceholderText(tr("Selecionar Musica"));
    QSqlQuery query("SELECT name FROM musica");
    while (query.next()) {
        QString name = query.value(0).toString();
        inputMusBox->addItem(name);
    }
    musList = new QListWidget();

    connect(inputMusBox, &QComboBox::activated,
            this, &TocadorV::inputMusChanged);

    QGridLayout *tocadorVLayout = new QGridLayout;
    tocadorVLayout->addWidget(tocLabel, 0, 0);
    tocadorVLayout->addWidget(inputTocBox, 0, 1);
    //tocadorVLayout->addWidget(tocList, 1, 0, 1, 2);

    tocadorVLayout->addWidget(musLabel, 2, 0);
    tocadorVLayout->addWidget(inputMusBox, 2, 1);
    //tocadorVLayout->addWidget(musList, 3, 0, 1, 2);

    tocadorVLayout->addWidget(button_ok, 4, 1);
    tocadorVGroup->setLayout(tocadorVLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tocadorVGroup, 0, 0);
    setLayout(layout);

    setWindowTitle(tr("Vincular Tocador"));

    connect(button_ok, &QPushButton::clicked, this, &TocadorV::newTocadorV);
}
void TocadorV::newTocadorV(){

    // QSqlQuery query;
    // QSqlQuery queryIdToc;
    // QSqlQuery queryIdMus;
    // queryIdMus.prepare("SELECT id FROM musica WHERE name = (:name_mus) ");
    // QListWidgetItem* name_mus = musList->item(0);
    // queryIdMus.bindValue(":name_mus", name_mus->text());
    // queryIdMus.exec();
    // //queryInst.next();
    // int id_mus = queryIdMus.value(0).toInt();
    // //std::cout << "id eeee" << id << "aaa" << std::endl;
    // query.prepare("INSERT INTO sabe_tocar (id_tocador, id_instr_musica) VALUES (:toc, :inst)");
    // query.bindValue(":toc", id_toc);
    // query.bindValue(":inst", id_mus);
    // query.exec();
    close();
}
void TocadorV::inputMusChanged()
{
}

TocadorV::~TocadorV()
{
}
