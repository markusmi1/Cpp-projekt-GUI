#ifndef PROJEKT_SORTEERMISMEETODID_H
#define PROJEKT_SORTEERMISMEETODID_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <QObject>
#include <QString>
#include <QDebug>

using namespace std;

class SorteerimisWrapper : public QObject {
    Q_OBJECT

private:
    vector<int> massiiv;
    int suurus;

public:
    SorteerimisWrapper(vector<int> sisend, int suurus) : massiiv(sisend), suurus(suurus) {}
    ~SorteerimisWrapper() {
        qDebug() << "kustutan klassi";
    }

    void setArray(vector<int> sisend, int suurus) {
        this->massiiv = sisend;
        this->suurus = suurus;
    }

    void mullisort(int mode) {
        bool vahetatud;
        for (int i = 0; i < suurus - 1; ++i) {
            vahetatud = false;
            for (int j = 0; j < suurus - 1; ++j) {
                if (massiiv[j] > massiiv[j + 1]) {
                    swap(massiiv[j], massiiv[j + 1]);
                    vahetatud = true;
                    if (mode == 1) {
                        emit arrayUpdated();
                        return;
                    }
                }
            }
            if (!vahetatud) break;
            if (mode == 2) {
                emit arrayUpdated();
                return;
            }
        }
        emit sortingFinished();
    }

    void valikumeetod(int mode) {
        int i, j, väikseimIndeks;
        for (i = 0; i < suurus - 1; i++) {
            väikseimIndeks = i;
            for (j = i + 1; j < suurus; j++) {
                if (massiiv[j] < massiiv[väikseimIndeks])
                    väikseimIndeks = j;
            }
            if (väikseimIndeks != i) {
                swap(massiiv[väikseimIndeks], massiiv[i]);
                if (mode == 1) {
                    emit arrayUpdated();
                    return;
                }
            }
            if (mode == 2) {
                emit arrayUpdated();
                return;
            }
        }
        emit sortingFinished();
    }

    vector<int> getMassiiv() {
        return massiiv;
    }

signals:
    void arrayUpdated();
    void sortingFinished();
};

vector<int> looVektor(const QString& m);

#endif //PROJEKT_SORTEERMISMEETODID_H
