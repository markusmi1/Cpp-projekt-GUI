#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include "sorteerimismeetodid.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    SorteerimisWrapper* sorter;
    QLineEdit* sisend;
    QPushButton* mulliNupp;
    QPushButton* valikuNupp;
    QPushButton* jargmineSammNupp;
    QPushButton* loppuNupp;
    QLabel* massiiviKuva;
    int praeguneMeetod;

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), sorter(new SorteerimisWrapper({}, 0)), praeguneMeetod(0) {
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        sisend = new QLineEdit(this);
        mulliNupp = new QPushButton("Bubble Sort", this);
        valikuNupp = new QPushButton("Selection Sort", this);
        jargmineSammNupp = new QPushButton("Next Step", this);
        loppuNupp = new QPushButton("Lõppu", this);
        massiiviKuva = new QLabel(this);

        layout->addWidget(sisend);
        layout->addWidget(mulliNupp);
        layout->addWidget(valikuNupp);
        layout->addWidget(jargmineSammNupp);
        layout->addWidget(loppuNupp);
        layout->addWidget(massiiviKuva);

        setCentralWidget(centralWidget);

        connect(mulliNupp, &QPushButton::clicked, this, &MainWindow::onMulliClicked);
        connect(valikuNupp, &QPushButton::clicked, this, &MainWindow::onValikuClicked);
        connect(jargmineSammNupp, &QPushButton::clicked, this, &MainWindow::onJargmineClicked);
        connect(loppuNupp, &QPushButton::clicked, this, &MainWindow::onLoppuClicked);
        connect(sorter, &SorteerimisWrapper::uuendatudMassiiv, this, &MainWindow::uuendaKuva);
        connect(sorter, &SorteerimisWrapper::lõpp, this, &MainWindow::onSortingFinished);
    }

private slots:
    void onMulliClicked() {
        if(valikuNupp->isVisible()){
            praeguneMeetod = 1;
            MainWindow::valikuNupp->setVisible(false);
            vector<int> array = looVektor(sisend->text());
            sorter->setArray(array, array.size());
            emit sorter->uuendatudMassiiv();
        } else
            sorter->mullisort(false);
    }

    void onValikuClicked() {
        if(mulliNupp->isVisible()){
            vector<int> array = looVektor(sisend->text());
            sorter->setArray(array, array.size());
            praeguneMeetod = 2;
            MainWindow::mulliNupp->setVisible(false);
            emit sorter->uuendatudMassiiv();
        }else{
            sorter->valikumeetod(false);
        }

    }

    void onJargmineClicked() {
        if (praeguneMeetod == 1) {
            sorter->mullisort(false);
        } else if (praeguneMeetod == 2) {
            sorter->valikumeetod(false);
        }
    }
    void onLoppuClicked() {
        if (praeguneMeetod == 1) {
            sorter->mullisort(true);
        } else if (praeguneMeetod == 2) {
            sorter->valikumeetod(true);
        }
    }

    void uuendaKuva() {
        vector<int> massiiv = sorter->getMassiiv();
        QString sisu = "[";
        for (size_t i = 0; i < massiiv.size(); ++i) {
            sisu += QString::number(massiiv[i]);
            if (i < massiiv.size() - 1) {
                sisu += ", ";
            }
        }
        sisu += "]";
        massiiviKuva->setText(sisu);
    }

    void onSortingFinished() {
        uuendaKuva();
        MainWindow::valikuNupp->setVisible(true);
        MainWindow::mulliNupp->setVisible(true);

    }
};

#endif // MAINWINDOW_H
