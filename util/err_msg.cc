#include <err_msg.h>

namespace util{
    Error::Error():no(0){
    }

    Error::Error(const Error &other):no(other.no), msg(other.msg){
    }

    Error & Error::operator=(const Error &other){
        if (this == &other){
            return *this;
        }
        no = other.no;
        msg = other.msg;
        return *this;
    }

    void Error::setCode(int err){
        no = err;
    }

    void Error::setStr(const std::string &str){
        msg = str;
    }

    void Error::errorf(const char *fmt, ...){
        char buf[1024] = {0};
        va_list arglist;
        va_start( arglist, fmt);
        vsnprintf(buf, sizeof(buf), fmt, arglist);
        va_end(arglist);
        msg = buf;
    }

    int Error::code() const{
        return no;
    }

    std::string Error::str() const {
        return msg;
    }
}
