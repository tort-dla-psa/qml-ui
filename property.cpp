#include "property.h"
#include "properties.h"

Properties *property::getProps() const {
    return m_props;
}

void property::setProps(Properties *value) {
    beginResetModel();
    if(this->m_props){
        this->m_props->disconnect(this);
    }
    m_props = value;
    if(m_props){
        connect(m_props, &Properties::pre_append,
            this, [this](){
                auto index = m_props->size();
                beginInsertRows(QModelIndex(), index, index);
        });
        connect(m_props, &Properties::post_append,
            this, [this](){
                endInsertRows();
        });
        connect(m_props, &Properties::pre_remove,
            this, [this](unsigned index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(m_props, &Properties::post_remove,
            this, [this](){
            endRemoveRows();
        });
    }
}

property::property(QObject *parent)
    : QAbstractListModel(parent)
{}

/*
QVariant property::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool property::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}
*/

int property::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !this->m_props)
        return 0;

    return m_props->size();
}

QVariant property::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || !m_props)
        return QVariant();

    auto item = m_props->items().at(index.row());
    if(role == TextRole){
        return QVariant(item.text);
    }else if(role == ValueRole){
        return QVariant(item.value);
    }
    return QVariant();
}

bool property::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!m_props)
        return false;

    auto item = m_props->items().at(index.row());
    if(role == TextRole){
        item.text = value.toString();
    }else if(role == ValueRole){
        item.value = value.toString();
    }

    auto rc = m_props->addItem(index.row(), item);
    if (rc) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags property::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> property::roleNames()const{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "text";
    roles[ValueRole] = "value";
    return roles;
}
