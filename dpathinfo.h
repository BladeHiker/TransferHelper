//dpathinfo.h
#ifndef DPATHINFO_H
#define DPATHINFO_H

#include <QObject>

class DPathInfo : public QObject
{
    Q_OBJECT
public:
    explicit DPathInfo(QObject *parent = nullptr);
    DPathInfo(double t,double p,double d):time(t),price(p),distan(d){}
    double time;
    double price;
    double distan;
signals:

};

#endif // DPATHINFO_H
