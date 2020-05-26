#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QObject>
#include <QString>
#include <QVector>

struct Property{
    QString text;
    QString value;

    friend bool operator == (const Property &lhs, const Property &rhs){
        return lhs.text == rhs.text &&
                lhs.value == rhs.value;
    }
    friend bool operator != (const Property &lhs, const Property &rhs){
        return !(lhs == rhs);
    }
};

class Properties : public QObject {
    Q_OBJECT

    QVector<Property> props;
public:
    explicit Properties(QObject *parent = nullptr);
    ~Properties();

    const decltype(props)& items()const;
    bool addItem(unsigned index, const Property &prop);
    size_t size()const;
signals:
    void prop_changed(Property);
    void pre_append();
    void post_append();
    void pre_remove(unsigned);
    void post_remove();
public slots:
    void addItem(const Property &prop);
    void addItem();
    void remove(const Property &prop);
};

#endif // PROPERTIES_H
