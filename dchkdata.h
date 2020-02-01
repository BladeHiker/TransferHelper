//dchkdata.h
#ifndef DCHKDATA_H
#define DCHKDATA_H

#include <QObject>
#include<QString>
#include<QDebug>
class DChkData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit DChkData(QObject *parent = nullptr) : QObject(parent){}
    DChkData(bool _chk=false):chk(_chk){}
    Q_INVOKABLE void setName(const bool name){
        if(chk!=name){
            chk=name;
            emit nameChanged();
        }
    }
    bool name()const{
        return chk;
    }
signals:
    void nameChanged();
public slots:


private:
    bool chk;
};

#endif // DCHKDATA_H
