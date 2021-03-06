/**
 * @file Certificate.cpp
 * @brief Implements Certificate.h.
 */
#include <i2pcpp/datatypes/Certificate.h>

namespace i2pcpp {
    Certificate::Certificate() :
        m_type(Certificate::Type::NIL) {}

    Certificate::Certificate(ByteArrayConstItr &begin, ByteArrayConstItr end)
    {
        if(!std::distance(begin, end))
            throw std::runtime_error("malformed certificate");

        m_type = (Type)*(begin++);

        if(m_type < (Type)0 || m_type > (Type)4)
            throw std::runtime_error("malformed certificate type");
    
        uint16_t size = parseUint16(begin);
        if(std::distance(begin, end) < size)
            throw std::runtime_error("malformed certificate size");

        m_payload.resize(size);
        std::copy(begin, begin + size, m_payload.begin());
        begin += size;
    }

    uint16_t Certificate::getLength() const
    {
        return m_payload.size();
    }

    ByteArray Certificate::serialize() const
    {
        ByteArray b(m_payload);
        uint16_t length = m_payload.size();

        b.insert(b.begin(), length);
        b.insert(b.begin(), (length >> 8));
        b.insert(b.begin(), (unsigned char)m_type);

        return b;
    }
}
