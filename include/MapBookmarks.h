#ifndef MAPBOOKMARKS_H
#define MAPBOOKMARKS_H

#include <QToolBar>
#include <QPushButton>
#include <QLabel>

class MapBookmarks : public QToolBar
{
    Q_OBJECT

public:
    explicit MapBookmarks(QToolBar *parent = 0);

signals:
    void jumpTo(std::pair<double, double> longLat);

private slots:
    void jumpToCastle();
    void jumpToKakskerta();

private:

    QPushButton *castleButton;
    QPushButton *kakskertaButton;

};

#endif // MAPBOOKMARKS_H