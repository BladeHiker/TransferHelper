//dtransferplanlist.cpp
#include "dtransferplanlist.h"
#include"dtransmap.h"

DTransferPlanList::DTransferPlanList(QObject *parent) : QObject(parent)
{
    _Map=new DTransMap();
}
Q_INVOKABLE bool DTransferPlanList::query(QString from,QString to){//核心算法
    this->PlanClear();
    if(from!=to)
        _Map->PlanLstCre(this,from,to);
    return from!=to;
}
