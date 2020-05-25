#ifndef PROPERTY_H
#define PROPERTY_H

#include <QAbstractListModel>

class Properties;
class property : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(Properties * props READ getProps WRITE setProps)

    Properties* m_props;
public:
    enum {
        TextRole = Qt::UserRole,
        ValueRole
    };
    explicit property(QObject *parent = nullptr);

    // Header:
    /*
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    */

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames()const override;

    Properties *getProps() const;
    void setProps(Properties *value);
private:
};

#endif // PROPERTY_H
