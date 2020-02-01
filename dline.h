//dline.h
#ifndef DLINE_H
#define DLINE_H

#include <QObject>
#include<QString>
#include<QList>
#include<QQmlListProperty>
#include<dstation.h>
#include<QColor>
class DStation;
class DLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool isbus READ isbus WRITE setBus NOTIFY busChanged)
public:
    QString Name;
    QColor Color;
    QList<DStation*>staList;
    QString timeRange;
    bool isBus;
    bool isbus(){
        return isBus;
    }
    explicit DLine(QObject *parent = nullptr): QObject(parent){}

    DLine(QString name,QColor color){
        setName(name);
        setColor(color);
        timeRange="6:00~22:00";
    }
    QString name(){
        return Name;
    }
    void setName(QString str){
        if(str!=Name){
            Name=str;
            nameChanged();
        }
    }
    void setColor(QColor &color){
        if(color==Color)
            return;
        Color=color;
        colorChanged();
    }
    QColor color()const{
        return Color;
    }
    void setBus(bool b){
        if(isBus==b)
            return;
        isBus=b;
        busChanged();
    }
signals:
    void nameChanged();
    void colorChanged();
    void busChanged();
private:

};

#endif // DLINE_H
