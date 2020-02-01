#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QString>
#include<QQmlContext>
#include<QList>
#include"dstationname.h"
#include<QDebug>
#include<QtXml>
#include<dchkdata.h>
#include<dstation.h>
#include<dline.h>
#include<dtransferplan.h>
#include<dstalist.h>
#include<dtransferplanlist.h>
#include<dtransinfo.h>
#include<dtransmap.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    DStationName PosFrom(""),PosTo("");
    DChkData FTStaChk(false),doublechk(false);
    QQmlApplicationEngine engine;
    QQmlContext* rootContex = engine.rootContext();


    rootContex->setContextProperty("posfrom",  &PosFrom);
    rootContex->setContextProperty("posto",  &PosTo);
    rootContex->setContextProperty("stachk",&FTStaChk);
    rootContex->setContextProperty("doubleVerify",&doublechk);
    qmlRegisterType<DStation>("DStation",1,0,"DStation");
    qmlRegisterType<DLine>("DLine",1,0,"DLine");
    qmlRegisterType<DStaList>("DStaList",1,0,"DStaList");
    qmlRegisterType<DTransferPlan>("DTransferPlan",1,0,"DTransferPlan");
    qmlRegisterType<DTransferPlanList>("DTransferPlanList",1,0,"DTransferPlanList");
    qmlRegisterType<DTransInfo>("DTransInfo",1,0,"DTransInfo");
    qmlRegisterType<DTransMap>("DTransMap",1,0,"DTransMap");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
