#ifndef ROUTERIDENTITY_H
#define ROUTERIDENTITY_H

#include <array>

#include "Datatype.h"
#include "Certificate.h"
#include "ByteArray.h"
#include "RouterHash.h"

namespace i2pcpp {
	class RouterIdentity : public Datatype {
		public:
			RouterIdentity() {};
			RouterIdentity(ByteArray::const_iterator &idItr);
			RouterIdentity(ByteArray const &publicKey, ByteArray const &signingKey, Certificate const &certificate);

			ByteArray getBytes() const;
			RouterHash getHash() const;
			std::string getHashEncoded() const;
			ByteArray getSigningKey() const
			{
				ByteArray b(128);
				copy(m_signingKey.begin(), m_signingKey.end(), b.begin());
				return b;
			}

		private:
			std::array<unsigned char, 256> m_publicKey;
			std::array<unsigned char, 128> m_signingKey;
			Certificate m_certificate;
	};
}

#endif
