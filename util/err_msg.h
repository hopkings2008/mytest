#pragma once

#include <string>
#include <stdarg.h>

namespace util{
    struct Error{
        int no;
        std::string msg;

        Error();
        Error(const Error &other);
        Error & operator=(const Error &other);

        void setCode(int err);
        void setStr(const std::string &str);
        void errorf(const char *fmt, ...);
        int code() const;
        std::string str() const;
    };
}
