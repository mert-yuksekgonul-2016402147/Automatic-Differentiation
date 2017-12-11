#include "variable.h"


Variable::Variable(int _id, string _name, double _value) {
    id = _id;
    name = _name;
    value = _value;
    from = nullptr;

}