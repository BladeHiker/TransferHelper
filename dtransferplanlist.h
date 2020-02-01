//dtransferplanlist.h
#ifndef DTRANSFERPLANLIST_H
#define DTRANSFERPLANLIST_H

#include<QObject>
#include<dtransferplan.h>
#include<QString>
#include<QList>
#include<QDebug>
#include<QQmlListProperty>
#include<dstation.h>
#include"dstalist.h"
#include"dline.h"
#include<dtransinfo.h>
#include<QThread>

class DTransMap;
using namespace std;
class DTransferPlanList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<DTransferPlan> planlst READ planlst NOTIFY planlstChanged)
public:
    explicit DTransferPlanList(QObject *parent = nullptr);
    QList<DTransferPlan*> _planlist;
    DTransMap* _Map;
    Q_INVOKABLE bool query(QString from,QString to);
    QQmlListProperty<DTransferPlan> planlst(){
        return QQmlListProperty<DTransferPlan>(this,this,&PlanAppend,&PlanCount,&planlst,&PlanClear);
    }
    void PlanAppend(DTransferPlan* l){
        _planlist.append(l);
        planlstChanged();
    }
    int PlanCount(){
        return _planlist.count();
    }
    DTransferPlan* planlst(int x){
        return _planlist.at(x);
    }
    void PlanClear(){
        _planlist.clear();
    }
    static void PlanAppend(QQmlListProperty<DTransferPlan>*list, DTransferPlan* l){
        reinterpret_cast<DTransferPlanList*>(list->data)->PlanAppend(l);
    }
    static int PlanCount(QQmlListProperty<DTransferPlan>*list){
        return reinterpret_cast<DTransferPlanList*>(list->data)->PlanCount();
    }
    static DTransferPlan* planlst(QQmlListProperty<DTransferPlan>*list, int x){
        return reinterpret_cast<DTransferPlanList*>(list->data)->planlst(x);
    }
    static void PlanClear(QQmlListProperty<DTransferPlan>*list){
        reinterpret_cast<DTransferPlanList*>(list->data)->PlanClear();
    }
signals:
    void planlstChanged();
};

#endif // DTRANSFERPLANLIST_H
