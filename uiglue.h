#ifndef UIGLUE_H
#define UIGLUE_H

#include <QObject>

class uiGlue : public QObject {
    Q_OBJECT
    int x, y, x_pre, y_pre;
    QObject* canvas;
public:
    explicit uiGlue(QObject *canvas, QObject *parent = nullptr);
    void drawLine(int x, int y, int x_end, int y_end);
public slots:
    void mousePressed(int x, int y);
    void mouseMoved(int x, int y);
    void mouseReleased(int x, int y);
signals:
};

#endif // UIGLUE_H
