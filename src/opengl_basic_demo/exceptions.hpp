#ifndef OPENGL_BASIC_DEMO_EXCEPTIONS_H
#define OPENGL_BASIC_DEMO_EXCEPTIONS_H

#include <stdexcept>

namespace opengl_basic_demo {

class GlObjectException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class ApplicationWindowException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

}  // opengl_basic_demo

#endif
