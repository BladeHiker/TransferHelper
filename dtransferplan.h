//dtransferplan.h
#ifndef DTRANSFERPLAN_H
#define DTRANSFERPLAN_H

#include <QObject>
#include<QString>
#include<QList>
#include<QDebug>
#include<QQmlListProperty>
#include<dstation.h>
#include"dstalist.h"
#include"dtransinfo.h"


class DTransferPlan : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<DLine> linelst READ linelst NOTIFY linelstChanged)
    Q_PROPERTY(QString note READ note WRITE setnote NOTIFY noteChanged)
    Q_PROPERTY(QQmlListProperty<DTransInfo> infolst READ infolst NOTIFY infolstChanged)
public:
    explicit DTransferPlan(QObject *parent = nullptr): QObject(parent){}
    QString _note;
    QList<DLine*>_linelst;
    int price;
    int buscnt;//5min
    int metrocnt;//2min
    QList<DTransInfo*> _infolst;

    void pushline(DLine* l){
        for(int i=0;i<_linelst.size();++i){
            if(l==_linelst[i]){
                return;
            }
        }
        _linelst.push_back(l);
    }
    void pushinfo(DTransInfo* in){
        for(int i=0;i<_infolst.size();++i){
            if(in==_infolst[i]){
                return;
            }
        }
        _infolst.push_back(in);
    }
    QString note()const{
        return _note;
    }
    void setnote(QString s){
        if(s==_note)return;
        _note=s;
        noteChanged();
    }
    QQmlListProperty<DTransInfo> infolst(){
        return QQmlListProperty<DTransInfo>(this,this,&infoAppend,&infoCount,&infolst,&infoClear);
    }
    void infoAppend(DTransInfo* l){
        _infolst.append(l);
    }
    int infoCount(){
        return _infolst.count();
    }
    DTransInfo* infolst(int x){
        return _infolst.at(x);
    }
    void infoClear(){
        _infolst.clear();
    }
    static void infoAppend(QQmlListProperty<DTransInfo>*list, DTransInfo* l){
        reinterpret_cast<DTransferPlan*>(list->data)->infoAppend(l);
    }
    static int infoCount(QQmlListProperty<DTransInfo>*list){
        return reinterpret_cast<DTransferPlan*>(list->data)->infoCount();
    }
    static DTransInfo* infolst(QQmlListProperty<DTransInfo>*list, int x){
        return reinterpret_cast<DTransferPlan*>(list->data)->infolst(x);
    }
    static void infoClear(QQmlListProperty<DTransInfo>*list){
        reinterpret_cast<DTransferPlan*>(list->data)->infoClear();
    }


    QQmlListProperty<DLine> linelst(){
        return QQmlListProperty<DLine>(this,this,&LineAppend,&LineCount,&linelst,&LineClear);
    }
    void LineAppend(DLine* l){
        _linelst.append(l);
    }
    int LineCount(){
        return _linelst.count();
    }
    DLine* linelst(int x){
        return _linelst.at(x);
    }
    void LineClear(){
        _linelst.clear();
    }
    static void LineAppend(QQmlListProperty<DLine>*list, DLine* l){
        reinterpret_cast<DTransferPlan*>(list->data)->LineAppend(l);
    }
    static int LineCount(QQmlListProperty<DLine>*list){
        return reinterpret_cast<DTransferPlan*>(list->data)->LineCount();
    }
    static DLine* linelst(QQmlListProperty<DLine>*list, int x){
        return reinterpret_cast<DTransferPlan*>(list->data)->linelst(x);
    }
    static void LineClear(QQmlListProperty<DLine>*list){
        reinterpret_cast<DTransferPlan*>(list->data)->LineClear();
    }
signals:
    void linelstChanged();
    void noteChanged();
    void infolstChanged();
private:

};

#endif // DTRANSFERPLAN_H
