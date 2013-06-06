#include "DatabaseSearchReply.h"

#include "../i2np/DatabaseSearchReply.h"
#include "../i2np/DatabaseLookup.h"

#include "../RouterContext.h"

namespace i2pcpp {
	namespace Handlers {
		DatabaseSearchReply::DatabaseSearchReply(RouterContext &ctx) :
			Message(ctx),
			m_log(boost::log::keywords::channel = "H[DSR]") {}

		I2NP::Message::Type DatabaseSearchReply::getType() const
		{
			return I2NP::Message::Type::DB_SEARCH_REPLY;
		}

		void DatabaseSearchReply::handleMessage(RouterHash const from, I2NP::MessagePtr const msg)
		{
			std::shared_ptr<I2NP::DatabaseSearchReply> dsr = std::dynamic_pointer_cast<I2NP::DatabaseSearchReply>(msg);

			I2P_LOG_SCOPED_RH(m_log, from);
			I2P_LOG(m_log, debug) << "received DatabaseSearchReply message";

			for(auto h: dsr->getHashes()) {
				if(!m_ctx.getDatabase().routerExists(h)) {
					I2NP::MessagePtr dbl(new I2NP::DatabaseLookup(h, m_ctx.getIdentity().getHash(), 0));
					m_ctx.getOutMsgDisp().sendMessage(from, dbl);
				}
			}
		}
	}
}
