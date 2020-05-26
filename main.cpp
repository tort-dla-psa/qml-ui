#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "property.h"
#include "properties.h"
#include "uiglue.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<property>("Property", 1, 0, "PropertyModel");
    qmlRegisterUncreatableType<Properties>("Property", 1, 0, "Properties",
        QStringLiteral("don't create Properties in QML!"));

    Properties props;
    props.addItem({"a", "a_"});
    props.addItem({"b", "b_"});
    props.addItem({"c", "c_"});


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("PropertiesList"), &props);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto root = engine.rootObjects().value(0);
    auto canvas = root->findChild<QObject*>("canvas");
    auto glue = new uiGlue(canvas);
    auto rc = app.exec();
    delete glue;
    return rc;
}
