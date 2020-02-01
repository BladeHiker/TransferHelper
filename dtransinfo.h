//dtransinfo.h
#ifndef TRANSINFO_H
#define TRANSINFO_H

#include <QObject>
#include<QString>
#include<QList>
#include<QDebug>
#include<QColor>
#include<QQmlListProperty>

class DTransInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString line READ line CONSTANT)
    Q_PROPERTY(QColor color READ color CONSTANT)
    Q_PROPERTY(int sym READ sym CONSTANT)

public:
    explicit DTransInfo(QObject *parent = nullptr): QObject(parent){}
    int Sym;
    /*
        1色块 xx线 xx站-》xxx站
        2箭头 xx站
        3换乘箭头 xx线 xx站-》xxx站
        4到达符号 xx站
    */
    QString Text;
    QColor Color;
    QString Line;

    Q_INVOKABLE QString text()const{
        return Text;
    }
    Q_INVOKABLE QString line(){
        return Line;
    }
    Q_INVOKABLE QColor color(){
        return Color;
    }
    Q_INVOKABLE int sym(){
        return Sym;
    }
signals:

};

#endif // TRANSINFO_H
