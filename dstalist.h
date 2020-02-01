//dstalist.h
#ifndef DSTALIST_H
#define DSTALIST_H

#include <QObject>
#include<QString>
#include<QList>
#include<QDebug>
#include<QQmlListProperty>
#include<dstation.h>
class DLine;
class DStation;
class DStaList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<DStation> stalst READ stalst NOTIFY stalstChanged)
public:
    QList<DStation*> staList;
    DStation* findSta(QString name){
        for(int i=0;i<staList.size();++i){
            if(staList[i]->name()==name){
                return staList[i];
            }
        }
        return nullptr;
    }
    explicit DStaList(QObject *parent = nullptr);
    QQmlListProperty<DStation> stalst(){
        return QQmlListProperty<DStation>(this,this,&append,&Count,&linelst,&clear);
    }
    Q_INVOKABLE void append(DStation* l){
        staList.append(l);
    }
    Q_INVOKABLE int Count(){
        return staList.count();
    }
    Q_INVOKABLE DStation* stalst(int x){
        return staList.at(x);
    }
    Q_INVOKABLE void clear(){
        staList.clear();
    }
    Q_INVOKABLE void dbin(QString str=":/stadb.xml");

signals:
    void stalstChanged();
private:

    static void append(QQmlListProperty<DStation>*list, DStation* s){
        reinterpret_cast<DStaList*>(list->data)->append(s);
    }
    static int Count(QQmlListProperty<DStation>*list){
        return reinterpret_cast<DStaList*>(list->data)->Count();
    }
    static DStation* linelst(QQmlListProperty<DStation>*list, int x){
        return reinterpret_cast<DStaList*>(list->data)->stalst(x);
    }
    static void clear(QQmlListProperty<DStation>*list){
        reinterpret_cast<DStaList*>(list->data)->clear();
    }
};

#endif // DSTALIST_H
