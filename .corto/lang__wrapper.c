/* lang__wrapper.c
 *
 * This file contains generated wrapper functions for ::corto::lang.
 */

#include "corto::lang.h"
#include "lang__meta.h"

// Constructor
Alias::Alias(const corto::lang::Member &member) : corto::lang::Member((corto::lang::member)NULL) {
    this->__ref = ::corto::_new((::corto::lang::_typedef)corto::lang::alias_h);
    this->type(type);
    this->modifiers(modifiers);
    this->state(state);
    this->weak(weak);
    this->member(member);
    this->define();
}

// Constructor (declare & define)
Alias::Alias(corto::lang::Object *_parent,
       std::string _name,
       const corto::lang::Member &member) : corto::lang::Member((corto::lang::member)NULL) {
    this->__ref = ::corto::declare(_parent->_ref(), _name, (::corto::lang::_typedef)corto::lang::alias_h);
    this->type(type);
    this->modifiers(modifiers);
    this->state(state);
    this->weak(weak);
    this->member(member);
    this->define();
}

// ::corto::lang::member member
corto::lang::Member Alias::member() {
    corto::lang::Member result(((corto::lang::alias)this->__ref)->member);
    return result;
}
void Alias::member(const corto::lang::Member &v) {
    if(v) {
        corto::set((corto::lang::object*)&((corto::lang::alias)this->__ref)->member, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::alias)this->__ref)->member, NULL);
    }
}
g::Type &v) {
    if(v) {
        corto::set((corto::lang::object*)&((corto::lang::collection)this->__ref)->elementType, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::collection)this->__ref)->elementType, NULL);
    }
}

// ::corto::lang::uint32 max
corto::lang::uint32 Collection::max() {
    return ((corto::lang::collection)this->__ref)->max;
}
void Collection::max(corto::lang::uint32 v) {
    ((corto::lang::collection)this->__ref)->max = v;
}
tType);
    this->parentState(parentState);
    this->defaultType(defaultType);
    this->defaultProcedureType(defaultProcedureType);
    this->base(base);
    this->baseAccess(baseAccess);
    this->parentType(parentType);
    this->parentState(parentState);
    this->defaultType(defaultType);
    this->defaultProcedureType(defaultProcedureType);
    this->returnType(returnType);
    this->returnsReference(returnsReference);
    this->parameters(parameters);
    this->define();
}

// ::corto::lang::type returnType
corto::lang::Type Delegate::returnType() {
    corto::lang::Type result(((corto::lang::delegate)this->__ref)->returnType);
    return result;
}
void Delegate::returnType(const corto::lang::Type &v) {
    if(v) {
        corto::set((corto::lang::object*)&((corto::lang::delegate)this->__ref)->returnType, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::delegate)this->__ref)->returnType, NULL);
    }
}

// ::corto::lang::bool returnsReference
bool Delegate::returnsReference() {
    return ((corto::lang::delegate)this->__ref)->returnsReference;
}
void Delegate::returnsReference(bool v) {
    ((corto::lang::delegate)this->__ref)->returnsReference = v;
}

// ::corto::lang::parameterseq parameters
corto::lang::parameterseq Delegate::parameters() {
    return ((corto::lang::delegate)this->__ref)->parameters;
}
void Delegate::parameters(corto::lang::parameterseq v) {
    ((corto::lang::delegate)this->__ref)->parameters = v;
}
rameters() {
    return ((corto::lang::function)this->__ref)->parameters;
}
void Function::parameters(corto::lang::parameterseq v) {
    ((corto::lang::function)this->__ref)->parameters = v;
}

// ::corto::lang::uint32 nextParameterId
corto::lang::uint32 Function::nextParameterId() {
    return ((corto::lang::function)this->__ref)->nextParameterId;
}
void Function::nextParameterId(corto::lang::uint32 v) {
    ((corto::lang::function)this->__ref)->nextParameterId = v;
}
t*)&((corto::lang::observer)this->__ref)->delayedBinder, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::observer)this->__ref)->delayedBinder, NULL);
    }
}
       :parentState(corto::lang::state v) {
    ((corto::lang::_class)this->__ref)->parentState = v;
}

// ::corto::lang::type defaultType
corto::lang::Type Class::defaultType() {
    corto::lang::Type result(((corto::lang::_class)this->__ref)->defaultType);
    return result;
}
void Class::defaultType(const corto::lang::Type &v) {
    if(v) {
        corto::set((corto::lang::object*)&((corto::lang::_class)this->__ref)->defaultType, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::_class)this->__ref)->defaultType, NULL);
    }
}

// ::corto::lang::type defaultProcedureType
corto::lang::Type Class::defaultProcedureType() {
    corto::lang::Type result(((corto::lang::_class)this->__ref)->defaultProcedureType);
    return result;
}
void Class::defaultProcedureType(const corto::lang::Type &v) {
    if(v) {
        corto::set((corto::lang::object*)&((corto::lang::_class)this->__ref)->defaultProcedureType, v._ref());
    }else {
        corto::set((corto::lang::object*)&((corto::lang::_class)this->__ref)->defaultProcedureType, NULL);
    }
}

// ::corto::lang::interfaceVectorseq interfaceVector
corto::lang::interfaceVectorseq Class::interfaceVector() {
    return ((corto::lang::_class)this->__ref)->interfaceVector;
}
void Class::interfaceVector(corto::lang::interfaceVectorseq v) {
    ((corto::lang::_class)this->__ref)->interfaceVector = v;
}

// ::corto::lang::observerseq observers
corto::lang::observerseq Class::observers() {
    return ((corto::lang::_class)this->__ref)->observers;
}
void Class::observers(corto::lang::observerseq v) {
    ((corto::lang::_class)this->__ref)->observers = v;
}

// ::corto::lang::initAction construct
corto::lang::initAction Class::construct() {
    return ((corto::lang::_class)this->__ref)->construct;
}
void Class::construct(corto::lang::initAction v) {
    ((corto::lang::_class)this->__ref)->construct = v;
}

// ::corto::lang::destructAction destruct
corto::lang::destructAction Class::destruct() {
    return ((corto::lang::_class)this->__ref)->destruct;
}
void Class::destruct(corto::lang::destructAction v) {
    ((corto::lang::_class)this->__ref)->destruct = v;
}
