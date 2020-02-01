//dtransmap.h
#ifndef DTRANSMAP_H
#define DTRANSMAP_H

#include <QObject>
#include<dtransferplanlist.h>
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
#include<map>
#include<dpathinfo.h>


using namespace std;

class DTransMap : public QObject
{
    Q_OBJECT
public:
    explicit DTransMap(QObject *parent = nullptr): QObject(parent){
        _stalst.dbin(":/stadb0.xml");
        _staset.dbin();
        linesLoad();
        mapCre();
        transdbin();
    }
    void transdbin();
    void PlanLstCre(DTransferPlanList* planlst,QString from,QString to);
    void linesLoad();
    void mapCre();
    DStaList _stalst;
    DStaList _staset;
    QVector<DLine*> lines;
    map<pair<QString,QString>,DPathInfo*> transmap;
    QString stamap[200];
    DTransferPlan* make_transplan(int deep);
    bool dfs(DTransferPlanList* planlst,QString from,QString to,int deep);
    DLine*uniline(DStation*a,DStation* b);
signals:

};

#endif // DTRANSMAP_H
