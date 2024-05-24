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
        cout << "kustutan klassi";
    }

    void setArray(vector<int> sisend, int suurus) {
        this->massiiv = sisend;
        this->suurus = suurus;
    }

    void mullisort(bool lõppu) {
        bool vahetatud;
        for (int i = 0; i < suurus - 1; ++i) {
            vahetatud = false;
            for (int j = 0; j < suurus - 1; ++j) {
                if (massiiv[j] > massiiv[j + 1]) {
                    swap(massiiv[j], massiiv[j + 1]);
                    vahetatud = true;
                    if(!lõppu){
                        emit uuendatudMassiiv();
                        return;
                    }
                }
            }
            if (!vahetatud) break;
        }
        emit lõpp();
    }

    void valikumeetod(bool lõppu) {
        int i, j, väikseimIndeks;
        for (i = 0; i < suurus - 1; i++) {
            väikseimIndeks = i;
            for (j = i + 1; j < suurus; j++) {
                if (massiiv[j] < massiiv[väikseimIndeks])
                    väikseimIndeks = j;
            }
            if (väikseimIndeks != i) {
                swap(massiiv[väikseimIndeks], massiiv[i]);
                if (!lõppu) {
                    emit uuendatudMassiiv();
                    return;
                }
            }
        }
        emit lõpp();
    }

    vector<int> getMassiiv() {
        return massiiv;
    }

signals:
    void uuendatudMassiiv();
    void lõpp();
};

vector<int> looVektor(const QString& m);

#endif //PROJEKT_SORTEERMISMEETODID_H
