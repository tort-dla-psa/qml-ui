#include "uiglue.h"
#include <QVariant>

uiGlue::uiGlue(QObject *canvas, QObject *parent)
    :QObject(parent),
      canvas(canvas)
{
    QObject::connect(canvas, SIGNAL(mousePress(int,int)), this, SLOT(mousePressed(int,int)));
    QObject::connect(canvas, SIGNAL(mouseRelease(int,int)), this, SLOT(mouseReleased(int,int)));
    QObject::connect(canvas, SIGNAL(mouseMove(int,int)), this, SLOT(mouseMoved(int,int)));
}

void uiGlue::drawLine(int x, int y, int x_end, int y_end){
    QVariant rval;
    QMetaObject::invokeMethod(canvas, "setDrawLine",
            Q_RETURN_ARG(QVariant, rval),
            Q_ARG(QVariant, x),
            Q_ARG(QVariant, y),
            Q_ARG(QVariant, x_end),
            Q_ARG(QVariant, y_end));
}
void uiGlue::mousePressed(int x, int y){
    x_pre = x;
    y_pre = y;
}
void uiGlue::mouseMoved(int x, int y){
    this->x = x;
    this->y = y;
    emit drawLine(x, y, x_pre, y_pre);
}
void uiGlue::mouseReleased(int x, int y){
    this->x = x;
    this->y = y;
    emit drawLine(x, y, x_pre, y_pre);
}

#include "moc_uiglue.cpp"
