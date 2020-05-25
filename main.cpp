#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "property.h"
#include "properties.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Properties props;
    props.addItem({"a", "a_"});
    props.addItem({"b", "b_"});
    props.addItem({"c", "c_"});

    qmlRegisterType<property>("Property", 1, 0, "PropertyModel");
    qmlRegisterUncreatableType<Properties>("Property", 1, 0, "Properties",
        QStringLiteral("don't create Properties in QML!"));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("Properties"), &props);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
