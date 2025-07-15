#include "bd.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#define TEST

bd::bd(QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

int bd::init(){
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return 1;
    }
    QSqlQuery query;

    // Create Tables (if it doesn't exist)
    if (!db.tables().contains("tocador")) {
        create_table(&query, "tocador", "id INTEGER PRIMARY KEY, name VARCHAR(100) NOT NULL");

#ifdef TEST
        QStringList pessoas = {"pessoa1", "pessoa2"};
        query.prepare("INSERT INTO tocador (id, name) VALUES (:id, :name)");
        int id = 1;
        for (const QString &nome : pessoas) {
            query.bindValue(":id", id++);
            query.bindValue(":name", nome);
            query.exec();
        }
#endif
    }

    if (!db.tables().contains("musica")) {
        create_table(&query, "musica", "id INTEGER PRIMARY KEY, name VARCHAR(50) NOT NULL, duracao INTEGER NOT NULL");

#ifdef TEST
        QStringList musicas = {"musica1", "musica2"};
        query.prepare("INSERT INTO musica (id, name, duracao) VALUES (:id, :name, :duracao)");
        int id = 1;
        for (const QString &nome : musicas) {
            query.bindValue(":id", id++);
            query.bindValue(":name", nome);
            query.bindValue(":duracao", 57+id);
            query.exec();
        }
#endif
    }

    if (!db.tables().contains("instrumento")) {
        create_table(&query, "instrumento", "id INTEGER PRIMARY KEY, name VARCHAR(20) NOT NULL");

        QStringList instrumentos = {"OKEDODAIKO", "NAGADODAIKO", "ODAIKO", "SHIMEDAIKO", "FUE"};
        query.prepare("INSERT INTO instrumento (id, name) VALUES (:id, :name)");
        int id = 1;
        for (const QString &nome : instrumentos) {
            query.bindValue(":id", id++);
            query.bindValue(":name", nome);
            query.exec();
        }
    }

    if (!db.tables().contains("instr_musica")) {
        create_table(&query, "instr_musica",
                     "id INTEGER PRIMARY KEY,"
                     "id_musica INTEGER NOT NULL,"
                     "id_instr INTEGER NOT NULL,"
                     "tipo VARCHAR(20),"
                     "FOREIGN KEY (id_musica) REFERENCES musica(id),"
                     "FOREIGN KEY (id_instr) REFERENCES instrumento(id)"
                     );

#ifdef TEST
        QStringList tipos = {"direita", "esquerda"};
        query.prepare("INSERT INTO instr_musica (id, id_musica, id_instr, tipo) VALUES (:id, :mus, 1, :tipo)");
        int id = 1;
        for (int mus=1; mus<3; mus++) {
            for (const QString &tipo : tipos) {
                query.bindValue(":id", id++);
                query.bindValue(":mus", mus);
                query.bindValue(":tipo", tipo);
                query.exec();
            }
        }
#endif
    }

    if (!db.tables().contains("sabe_tocar")) {
        create_table(&query, "sabe_tocar",
                     "id_tocador INTEGER NOT NULL,"
                     "id_instr_musica INTEGER NOT NULL,"
                     "FOREIGN KEY (id_tocador) REFERENCES tocador(id),"
                     "FOREIGN KEY (id_instr_musica) REFERENCES instr_musica(id),"
                     "PRIMARY KEY (id_tocador, id_instr_musica)"
                     );

#ifdef TEST
        query.prepare("INSERT INTO sabe_tocar (id_tocador, id_instr_musica) VALUES (:toc, :inst)");
        for (int i=1; i<5; i++) {
            query.bindValue(":toc", 1+(i-1)%2);
            query.bindValue(":inst", i);
            query.exec();
        }
#endif
    }

    if (!db.tables().contains("indisponibilidade")) {
        create_table(&query, "indisponibilidade",
                     "id_tocador INTEGER NOT NULL,"
                     "data timestamp NOT NULL,"
                     "FOREIGN KEY (id_tocador) REFERENCES tocador(id),"
                     "PRIMARY KEY (id_tocador, data)"
                     );
    }

    // Create Views
    if (!query.exec(
            "CREATE VIEW IF NOT EXISTS instr_musica_view AS SELECT "
            "instr_musica.id as id_instr_musica, "
            "instr_musica.tipo as tipo, "
            "musica.id as id_musica, "
            "musica.name as musica, "
            "musica.duracao as musica_duracao, "
            "instrumento.id as id_instr, "
            "instrumento.name as instr "
            "FROM "
            "instr_musica INNER JOIN musica ON instr_musica.id_musica=musica.id "
            "INNER JOIN instrumento ON instr_musica.id_instr=instrumento.id "
            )) {
        qDebug() << "Error creating view:" << query.lastError().text();
        return 1;
    }

    if (!query.exec(
            "CREATE VIEW IF NOT EXISTS tocador_instr_musica_view AS SELECT "
            "tocador.id as id_tocador, "
            "tocador.name as tocador, "
            "sabe_tocar.id_instr_musica, tipo, id_musica, musica, musica_duracao, id_instr, instr "
            "FROM "
            "tocador INNER JOIN sabe_tocar ON tocador.id=sabe_tocar.id_tocador "
            "INNER JOIN instr_musica_view ON sabe_tocar.id_instr_musica=instr_musica_view.id_instr_musica"
            )) {
        qDebug() << "Error creating view:" << query.lastError().text();
        return 1;
    }

    // Select Data


#ifdef TEST
    QStringList pessoas = {"pessoa1", "pessoa2"};
    if (!query.exec("SELECT * FROM tocador_instr_musica_view")) {
        qDebug() << "Error selecting data:" << query.lastError().text();
        return 1;
    }
    while (query.next()) {
        QString tocador = query.value("tocador").toString();
        QString musica = query.value("musica").toString();
        QString instr = query.value("instr").toString();
        QString tipo = query.value("tipo").toString();
        qDebug() << "Tocador:" << tocador << "\t| Music:" << musica << "\t| Instr:" << instr << "\t| Tipo:" << tipo;
    }
#endif
    /*
    if (!query.exec("SELECT * FROM instrumento")) {
        qDebug() << "Error selecting data:" << query.lastError().text();
        return 1;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        qDebug() << "ID:" << id << "Name:" << name;
    }
    */

    return 0;
}

int bd::close(){
    // 5. Close the connection
    db.close();
    return 0;
};
