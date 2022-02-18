#include <util/Formatter.h>

string cFormatter::str() const
{
    return psStream.str();
}

cFormatter::operator string() const
{
    return psStream.str();
}

std::string cFormatter::operator>>(cFormatter::eConvertToString)
{
    return psStream.str();
}
