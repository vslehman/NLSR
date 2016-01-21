/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014  University of Memphis,
 *                     Regents of the University of California
 *
 * This file is part of NLSR (Named-data Link State Routing).
 * See AUTHORS.md for complete list of NLSR authors and contributors.
 *
 * NLSR is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NLSR is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NLSR, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
 /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2014 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#include <ndn-cxx/security/key-chain.hpp>

#include "boost-test.hpp"

namespace nlsr {

// OSX KeyChain, when used on a headless server,
// forbids usage of a private key if that key isn't created by the calling process.
// Therefore, unit testing must create its own key pair.

class IdentityFixture
{
public:
  IdentityFixture()
  {
    // save the old default identity
    try {
      m_oldDefaultIdentity = m_keyChain.getDefaultIdentity();
      m_hasOldDefaultIdentity = true;
    }
    catch (ndn::SecPublicInfo::Error& e) {
      m_hasOldDefaultIdentity = false;
    }

    m_newIdentity = "/nlsr-test-identity";
    m_newIdentity.appendVersion();

    // create the new identity and self-signed certificate
    m_keyChain.createIdentity(m_newIdentity);

    // set the new identity as default identity,
    // and the corresponding certificate becomes the default certificate
    m_keyChain.setDefaultIdentity(m_newIdentity);
  }

  ~IdentityFixture()
  {
    // recover the old default setting
    if (m_hasOldDefaultIdentity) {
      m_keyChain.setDefaultIdentity(m_oldDefaultIdentity);
    }

    // remove the temporarily created identity and certificates
    // XXX This has no effect if oldDefaultIdentity doesn't exist.
    //     newIdentity would be kept as default.
    m_keyChain.deleteIdentity(m_newIdentity);
  }

private:
  ndn::KeyChain m_keyChain;
  bool m_hasOldDefaultIdentity;
  ndn::Name m_oldDefaultIdentity;
  ndn::Name m_newIdentity;
};

BOOST_GLOBAL_FIXTURE(IdentityFixture)
#if BOOST_VERSION >= 105900
;
#endif // BOOST_VERSION >= 105900

} // namespace nlsr
