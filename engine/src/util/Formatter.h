#pragma once

#include <pch.h>

class cFormatter
{
public:
    cFormatter() = default;
    ~cFormatter() = default;

    template<typename Type>
    cFormatter& operator<<(const Type& value)
    {
        psStream << value;
        return *this;
    }

    string str() const;

    operator string() const;

    enum eConvertToString
    {
        to_str
    };

    std::string operator>>(eConvertToString);

private:
    std::stringstream psStream;

    cFormatter(const cFormatter&);
};

