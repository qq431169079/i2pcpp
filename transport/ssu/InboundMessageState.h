#ifndef SSUINBOUNDMESSAGESTATE_H
#define SSUINBOUNDMESSAGESTATE_H

#include <memory>
#include <map>
#include <list>

#include "../../datatypes/RouterHash.h"

#include "../../util/DoubleBitfield.h"

namespace i2pcpp {
	namespace SSU {
		class InboundMessageState {
			public:
				InboundMessageState(RouterHash const &rh, const uint32_t msgId);

				void addFragment(const unsigned char fragNum, ByteArray const &data, bool isLast);
				ByteArray assemble() const;

				RouterHash getRouterHash() const;
				uint32_t getMsgId() const;

				bool allFragmentsReceived() const;
				std::vector<bool> getAckStates() const;

			private:
				RouterHash m_routerHash;

				uint32_t m_msgId;
				bool m_gotLast = false;
				unsigned char m_lastFragment;
				uint32_t m_byteTotal = 0;

				std::map<unsigned char, ByteArray> m_fragments;
				
				DoubleBitfield m_states;
		};

		typedef std::shared_ptr<InboundMessageState> InboundMessageStatePtr;
	}
}

#endif