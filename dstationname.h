//dstationname.h
#ifndef DSTATIONNAME_H
#define DSTATIONNAME_H

#include <QObject>
#include<QString>

class DStationName : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit DStationName(QObject *parent = nullptr): QObject(parent){}
    DStationName(QString _name=""):Name(_name){}

signals:
    QString nameChanged();
public slots:
    QString name()const{
        return Name;
    }
    void setName(const QString& _name=""){
        if(Name!=_name){
            Name=_name;
            emit nameChanged();
        }
    }
private:
    QString Name;
};

#endif // DSTATIONNAME_H
