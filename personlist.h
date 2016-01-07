#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QObject>

class PersonList : public QObject
{
    Q_OBJECT
public:
    explicit PersonList(QObject *parent = 0);

signals:

public slots:
};

#endif // PERSONLIST_H
