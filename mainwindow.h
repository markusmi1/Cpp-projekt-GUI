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
    QLineEdit* inputField;
    QPushButton* bubbleSortButton;
    QPushButton* selectionSortButton;
    QPushButton* nextStepButton;
    QLabel* arrayLabel;
    int sortMode;
    int currentSortAlgorithm;

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), sorter(new SorteerimisWrapper({}, 0)), sortMode(0), currentSortAlgorithm(0) {
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        inputField = new QLineEdit(this);
        bubbleSortButton = new QPushButton("Bubble Sort", this);
        selectionSortButton = new QPushButton("Selection Sort", this);
        nextStepButton = new QPushButton("Next Step", this);
        arrayLabel = new QLabel(this);

        layout->addWidget(inputField);
        layout->addWidget(bubbleSortButton);
        layout->addWidget(selectionSortButton);
        layout->addWidget(nextStepButton);
        layout->addWidget(arrayLabel);

        setCentralWidget(centralWidget);

        connect(bubbleSortButton, &QPushButton::clicked, this, &MainWindow::onBubbleSortClicked);
        connect(selectionSortButton, &QPushButton::clicked, this, &MainWindow::onSelectionSortClicked);
        connect(nextStepButton, &QPushButton::clicked, this, &MainWindow::onNextStepClicked);
        connect(sorter, &SorteerimisWrapper::arrayUpdated, this, &MainWindow::updateArrayDisplay);
        connect(sorter, &SorteerimisWrapper::sortingFinished, this, &MainWindow::onSortingFinished);
    }

private slots:
    void onBubbleSortClicked() {
        vector<int> array = looVektor(inputField->text());
        sorter->setArray(array, array.size());
        currentSortAlgorithm = 1;
        sortMode = 1;
        sorter->mullisort(sortMode);
    }

    void onSelectionSortClicked() {
        vector<int> array = looVektor(inputField->text());
        sorter->setArray(array, array.size());
        currentSortAlgorithm = 2;
        sortMode = 1;
        sorter->valikumeetod(sortMode);
    }

    void onNextStepClicked() {
        sortMode = 1;
        if (currentSortAlgorithm == 1) {
            sorter->mullisort(sortMode);
        } else if (currentSortAlgorithm == 2) {
            sorter->valikumeetod(sortMode);
        }
    }

    void updateArrayDisplay() {
        vector<int> array = sorter->getMassiiv();
        QString arrayText = "[";
        for (size_t i = 0; i < array.size(); ++i) {
            arrayText += QString::number(array[i]);
            if (i < array.size() - 1) {
                arrayText += ", ";
            }
        }
        arrayText += "]";
        arrayLabel->setText(arrayText);
    }

    void onSortingFinished() {
        updateArrayDisplay();
    }
};

#endif // MAINWINDOW_H
