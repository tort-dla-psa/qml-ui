#include "properties.h"

Properties::Properties(QObject *parent)
    :QObject(parent)
{
}

Properties::~Properties(){
}
const decltype(Properties::props)& Properties::items() const {
    return this->props;
}
size_t Properties::size()const{
    return this->props.size();
}

bool Properties::addItem(unsigned index, const Property &prop) {
    if(index >= this->props.size()){
        return false;
    }
    props[index] = prop;
    return true;
}

void Properties::addItem(const Property &prop){
    emit pre_append();
    props.append(prop);
    emit post_append();
}
void Properties::addItem(){
    addItem({"",""});
}
void Properties::remove(const Property &prop){
    auto i = props.indexOf(prop);
    if(i < 0){
        return;
    }
    emit pre_remove(i);
    props.removeAt(i);
    emit post_remove();
}
