#include "sorteerimismeetodid.h"

vector<int> looVektor(const QString& m) {
    stringstream ss{m.toStdString()};
    string e;
    vector<int> v;
    while (ss >> e) {
        v.push_back(stoi(e));
    }
    for(auto el : v){
        cout << el << endl;
    }
    return v;
}
