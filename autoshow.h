#ifndef AUTOSHOW_H
#define AUTOSHOW_H

#include <QObject>

class AutoShow : public QObject
{
    Q_OBJECT
public:
    explicit AutoShow(QObject *parent = nullptr);

signals:

};

#endif // AUTOSHOW_H
