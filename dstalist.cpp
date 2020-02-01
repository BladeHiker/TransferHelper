//dstalist.cpp
#include "dstalist.h"
#include <QFile>
#include <QtXml\QtXml>
#include <QtXml\QDomDocument>
#include <QXmlStreamReader>
#include<QColor>
DStaList::DStaList(QObject *parent) : QObject(parent)
{

}
Q_INVOKABLE void DStaList::dbin(QString str){
    QFile file(str);
    file.open(QIODevice::ReadOnly| QFile::Text  );
    QXmlStreamReader xmlreader;
    xmlreader.setDevice(&file);
    while(!xmlreader.atEnd()){
        if(xmlreader.isStartElement()){
            if(xmlreader.name()=="station"){
                xmlreader.readNext();
                while(!xmlreader.atEnd()){
                    if(xmlreader.isEndElement()){
                        xmlreader.readNext();
                        break;
                    }
                    while(!xmlreader.atEnd()){
                    DStation *sta;
                    if(xmlreader.isStartElement()){
                        if(xmlreader.name()=="item"){
                            sta=new DStation;
                            while(!xmlreader.atEnd()){
                                xmlreader.readNext();
                            if(xmlreader.isEndElement()&&xmlreader.name()=="item"){
                                xmlreader.readNext();
                                break;
                            }
                            if(!xmlreader.isStartElement()) continue;
                            if(xmlreader.name()=="name"){
                                sta->setName(xmlreader.readElementText().toUtf8());
                            }else
                            if(xmlreader.name()=="line"){
                                DLine *line=new DLine;
                                QColor *color=new QColor(xmlreader.attributes().value("color").toString());
                                line->setColor(*color);
                                sta->type=xmlreader.attributes().value("type").toInt();
                                line->isBus=sta->type==0?0:1;
                                line->setName(xmlreader.readElementText().toUtf8());
                                sta->LineAppend(line);
                            }
                        }
                            append(sta);

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
