#ifndef MAPTOOLBAR_H
#define MAPTOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class MapToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit MapToolBar(QToolBar *parent = 0);

signals:
    void submitPressed(std::pair<double,double>);
    void jumpPressed(std::pair<double,double>);

private slots:
    void submitButtonPressed();
    void jumpButtonPressed();

private:

    QPushButton *submitButton;
    QPushButton *jumpButton;

    QLabel *longitudeLabel;
    QLabel *latitudeLabel;
    QLineEdit *longitude;
    QLineEdit *latitude;

};

#endif // MAPTOOLBAR_H