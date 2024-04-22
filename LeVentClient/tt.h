#ifndef TT_H
#define TT_H

#include <QObject>

class tt : public QObject
{
    Q_OBJECT
public:
    explicit tt(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TT_H