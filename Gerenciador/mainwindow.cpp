#include "mainwindow.h"
#include "tocador.h"
#include "tocadorv.h"
#include "musica.h"
#include <QSqlQuery>
#include <QDebug>
//#include <iostream>
#include <filesystem>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Inicializa widgets
    label = new QLabel("<h2>Gerenciador de Apresentações</h2>");
    button_scheduleshow = new QPushButton("Agendar Apresentação");
    button_music = new QPushButton("Cadastrar Música");
    button_musician = new QPushButton("Cadastrar Tocador");
    button_musicianV = new QPushButton("Vincular Tocador");
    button_checkSchedMusician = new QPushButton("Verificar disponibilidade de Tocador");
    button_instrument = new QPushButton("Listar Instrumentos");
    spin = new QSpinBox();
    slider = new QSlider(Qt::Horizontal);
    instrumentList = new QListWidget();
    scheduleScreen = new QListWidget();
    scheduleshow = new QListWidget();

    // Layout principal
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    //mainLayout->addWidget(spin);
    //mainLayout->addWidget(slider);
    mainLayout->addWidget(button_scheduleshow);
    mainLayout->addWidget(button_music);
    mainLayout->addWidget(button_musician);
    mainLayout->addWidget(button_musicianV);
    mainLayout->addWidget(button_checkSchedMusician);
    mainLayout->addWidget(button_instrument);
    mainLayout->addWidget(instrumentList);
    mainLayout->addWidget(scheduleScreen);

    // Inicializa banco de dados
    filesystem::path dir = "Data";
    filesystem::create_directory(dir);

    filesystem::path file = "database.sqlite";
    string filepath = (dir / file).string();
    database = new bd(QString::fromStdString(filepath));
    database->init();

    connect(button_instrument, &QPushButton::clicked, this, [this]() {
        instrumentList->clear();

        QSqlQuery query("SELECT name FROM instrumento");
        while (query.next()) {
            QString name = query.value(0).toString();
            instrumentList->addItem(name);
        }

        if (instrumentList->count() == 0) {
            instrumentList->addItem("Nenhum instrumento encontrado.");
        }
    });

    connect(button_checkSchedMusician, &QPushButton::clicked, this, [this]() {
        scheduleScreen->clear();

        QSqlQuery query("SELECT name FROM instrumento");
        while (query.next()) {
            QString name = query.value(0).toString();
            scheduleScreen->addItem(name);
        }

        if (instrumentList->count() == 0) {
            scheduleScreen->addItem("Nenhum instrumento encontrado.");
        }
    });



    connect(button_music, &QPushButton::clicked, this, [this]() {
        Musica *newWidget = new Musica(); // Create an instance of the new widget
        newWidget->setAttribute(Qt::WA_DeleteOnClose); // Optional: automatically delete when closed
        newWidget->show(); // Display the new widget
    });

    connect(button_musician, &QPushButton::clicked, this, [this]() {
        Tocador *newWidget = new Tocador(); // Create an instance of the new widget
        newWidget->setAttribute(Qt::WA_DeleteOnClose); // Optional: automatically delete when closed
        newWidget->show(); // Display the new widget
    });
    connect(button_musicianV, &QPushButton::clicked, this, [this]() {
        TocadorV *newWidget = new TocadorV(); // Create an instance of the new widget
        newWidget->setAttribute(Qt::WA_DeleteOnClose); // Optional: automatically delete when closed
        newWidget->show(); // Display the new widget
    });
}

MainWindow::~MainWindow()
{
    delete database;
}
