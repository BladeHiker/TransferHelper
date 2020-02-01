//dtransmap.cpp
#include "dtransmap.h"
#include<QQueue>
#include <QFile>
#include <QtXml\QtXml>
#include <QtXml\QDomDocument>
#include <QXmlStreamReader>
#include<QColor>
#include<algorithm>
void DTransMap::linesLoad(){
    qDebug()<<"linesloadin";
    for(int i=0;i<this->_stalst.staList.size();++i){
        for(int ii=0;ii<_stalst.staList[i]->line.size();++ii){
            bool fg_get=false;
            for(int iii=0;iii<lines.size();++iii){
                if(lines[iii]->name()==_stalst.staList[i]->line[ii]->name()){
                    lines[iii]->staList.push_back(_stalst.staList[i]);
                    fg_get=true;
                }
            }
            if(!fg_get){
                DLine *lin= new DLine(_stalst.staList[i]->line[ii]->name(),_stalst.staList[i]->line[ii]->color());
                lin->staList.push_back(_stalst.staList[i]);
                lin->isBus=(_stalst.staList[i]->type==0)?0:1;
                lines.push_back(lin);
            }
        }
    }

}
void DTransMap::mapCre(){
    qDebug()<<"mapcrein";
    for(int i=0;i<lines.size();++i){
        for(int ii=0;ii<lines[i]->staList.size()-1;++ii){
            transmap[make_pair(lines[i]->staList[ii]->name(),lines[i]->staList[ii+1]->name())]=new DPathInfo(60,2,3);
            transmap[make_pair(lines[i]->staList[ii+1]->name(),lines[i]->staList[ii]->name())]=new DPathInfo(60,2,3);
        }
    }
}
DLine* DTransMap::uniline(DStation*a,DStation* b){
    for(int i=0;i<a->line.size();++i){
        for(int ii=0;ii<b->line.size();++ii){
            if(a->line[i]->name()==b->line[ii]->name())
                return a->line[i];
        }
    }
    return a->line[0];
}
DTransferPlan* DTransMap::make_transplan(int deep){
    DTransferPlan*plan=new DTransferPlan;
    int cnt=0;
    int money=0;
    bool fg_bus=true;
    plan->buscnt=0;
    plan->metrocnt=0;
    for(int i=0;i<=deep;++i){

        DTransInfo*in=new DTransInfo;
        if(_staset.findSta(stamap[i])->type==0){
            ++cnt;
            ++plan->metrocnt;
            fg_bus=true;
        }
        else{
            ++plan->buscnt;
            if(cnt)
                money+=(cnt<=7?3:(cnt<=14?5:8));
            cnt=0;
            if(fg_bus){
                fg_bus=false;
                money+=_staset.findSta(stamap[i])->type;
            }
        }

        in->Sym=2;
        in->Line=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->name();
        in->Color=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->Color;
        in->Text=stamap[i];
        if(i==0){
            DTransInfo*in0=new DTransInfo;
            in0->Sym=1;
            in0->Line=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->name();
            in0->Color=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->Color;
            in0->Text=stamap[i]+((_staset.findSta(stamap[i])->type)?"站上车":"进站");
            plan->pushinfo(in0);
            plan->pushline(uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1])));
        }else if(uniline(_staset.findSta(stamap[i-1]),_staset.findSta(stamap[i>deep?i-1:i]))->name()!=in->Line){
            DTransInfo*in0=new DTransInfo;
            in0->Sym=3;
            in0->Line=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->name();
            in0->Color=uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1]))->Color;
            in0->Text=stamap[i]+"换乘";
            plan->pushinfo(in0);
            plan->pushline(uniline(_staset.findSta(stamap[i]),_staset.findSta(stamap[i+1>deep?i:i+1])));
        }
        if(i==deep){
            in->Sym=4;
        }

        plan->pushinfo(in);
    }
    if(cnt){
        money+=(cnt<=7?3:(cnt<=14?5:8));
    }
    plan->setnote(" 共"+QString::number(deep)+"站  "+QString::number(money)+"元");
    plan->price=money;
    return plan;
}
bool DTransMap::dfs(DTransferPlanList* planlst,QString from,QString to,int deep){
    stamap[deep]=from;
    if(from==to){
        //TODO:stalst转plan
        planlst->PlanAppend(make_transplan(deep));
        return true;
    }
    for(int i=0;i<_staset.staList.size();++i){
        if(transmap.count(make_pair(from,_staset.staList[i]->name()))){
            bool fg_circle=false;
            for(int ii=0;ii<=deep;++ii){
                if(_staset.staList[i]->name()==stamap[ii]){
                    fg_circle=true;
                    break;
                }
            }
            if(!fg_circle)
                if(dfs(planlst,_staset.staList[i]->name(),to,deep+1))
                    break;

        }
    }
    return false;
}

void DTransMap::PlanLstCre(DTransferPlanList* planlst,QString from,QString to){
    planlst->PlanClear();
    dfs(planlst,from,to,0);
    sort(planlst->_planlist.begin(),planlst->_planlist.end(),[](DTransferPlan*a,DTransferPlan*b){
        if((a->buscnt*5+a->metrocnt*2)==(b->buscnt*5+b->metrocnt*2)){
            return a->price<b->price;
        }else{
            return (a->buscnt*5+a->metrocnt*2)<(b->buscnt*5+b->metrocnt*2);
        }
    });
    planlst->planlstChanged();
    if(planlst->_planlist.length()>2){
        planlst->_planlist[0]->_note.push_back(" ★推荐路线");
        planlst->_planlist[0]->noteChanged();
    }
}
void DTransMap::transdbin(){
    QFile file(":/transdb.xml");
    qDebug()<< file.open(QIODevice::ReadOnly| QFile::Text  );
    QXmlStreamReader xmlreader;
    xmlreader.setDevice(&file);
    while(!xmlreader.atEnd()){
        if(xmlreader.isStartElement()){
            if(xmlreader.name()=="transfer"){
                xmlreader.readNext();
                while(!xmlreader.atEnd()){
                    if(xmlreader.isEndElement()){
                        xmlreader.readNext();
                        break;
                    }
                    while(!xmlreader.atEnd()){
                    if(xmlreader.isStartElement()){
                        if(xmlreader.name()=="item"){
                            QString f,t;
                            while(!xmlreader.atEnd()){
                                xmlreader.readNext();
                            if(xmlreader.isEndElement()&&xmlreader.name()=="item"){
                                xmlreader.readNext();
                                break;
                            }
                            if(!xmlreader.isStartElement()) continue;
                            if(xmlreader.name()=="from"){
                                f=xmlreader.readElementText().toUtf8();
                            }else
                            if(xmlreader.name()=="to"){
                                t=xmlreader.readElementText().toUtf8();
                            }
                        }
                            transmap[make_pair(f,t)]=new DPathInfo(60,2,3);
                            transmap[make_pair(t,f)]=new DPathInfo(60,2,3);
                        }else{
                            xmlreader.readNext();
                        }

                    }else{
                        xmlreader.readNext();
                    }

                    }
                }
            }else{
                xmlreader.readNext();
            }

        }else{
            xmlreader.readNext();
        }
    }

    file.close();
}
