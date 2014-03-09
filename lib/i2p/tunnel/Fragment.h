#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "../i2np/Message.h"

#include <i2pcpp/datatypes/ByteArray.h>

#include <list>
#include <memory>

namespace i2pcpp {
    class Fragment {
        public:
            virtual ~Fragment() {}

            void setMsgId(uint32_t id);
            uint32_t getMsgId() const;

            void setPayload(ByteArrayConstItr &begin, ByteArrayConstItr end, uint16_t max);
            const ByteArray& getPayload() const;
            uint16_t size() const;

            virtual ByteArray compile() const = 0;

            static std::vector<std::unique_ptr<Fragment>> fragmentMessage(ByteArray const &data);
            static std::unique_ptr<Fragment> parse(ByteArrayConstItr &begin, ByteArrayConstItr end);

        protected:
            uint32_t m_msgId = 0;
            ByteArray m_payload;

        private:
            virtual uint8_t headerSize() const = 0;
    };

    typedef std::unique_ptr<Fragment> FragmentPtr;
};

#endif
