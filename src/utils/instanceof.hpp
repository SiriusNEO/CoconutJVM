/*
 *  instanceof function
 */

#pragma once

namespace cocotools {

// check a pointer of BaseClass whether it points to a SubClass
// SubClass must be a subclass of BaseClass

template<typename SubClass, typename BaseClass>
inline bool instanceof(const BaseClass *ptr) {
    return dynamic_cast<const SubClass*>(ptr) != nullptr;
}

}