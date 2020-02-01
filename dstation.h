//dstation.h
#ifndef DSTATION_H
#define DSTATION_H

#include <QObject>
#include<QString>
#include<QList>
#include<QDebug>
#include<QQmlListProperty>
#include<dline.h>
class DLine;
class DStation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<DLine> linelst READ linelst NOTIFY linelstChanged)
public:
    QString staName;
    QList<DLine*> line;

    int type;//0地铁 1/2bus
    explicit DStation(QObject *parent = nullptr): QObject(parent){}

    QString name(){
        return staName;
    }
    void setName(QString str){
        if(str!=staName){
            staName=str;
            nameChanged();
        }
    }
    QQmlListProperty<DLine> linelst(){
        return QQmlListProperty<DLine>(this,this,&LineAppend,&LineCount,&linelst,&LineClear);
    }
    bool isChaSta();
    bool isAble();
    void LineAppend(DLine* l){
        line.append(l);
    }
    int LineCount(){
        return line.count();
    }
    DLine* linelst(int x){
        return line.at(x);
    }
    void LineClear(){
        line.clear();
    }
    static void LineAppend(QQmlListProperty<DLine>*list, DLine* l){
        reinterpret_cast<DStation*>(list->data)->LineAppend(l);
    }
    static int LineCount(QQmlListProperty<DLine>*list){
        return reinterpret_cast<DStation*>(list->data)->LineCount();
    }
    static DLine* linelst(QQmlListProperty<DLine>*list, int x){
        return reinterpret_cast<DStation*>(list->data)->linelst(x);
    }
    static void LineClear(QQmlListProperty<DLine>*list){
        reinterpret_cast<DStation*>(list->data)->LineClear();
    }

signals:
    void nameChanged();
    void linelstChanged();
private:


};
#endif // DSTATION_H
