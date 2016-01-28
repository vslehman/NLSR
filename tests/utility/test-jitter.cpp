/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2016,  The University of Memphis,
 *                           Regents of the University of California,
 *                           Arizona Board of Regents.
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
 **/

#include "utility/jitter.hpp"

#include "tests/test-common.hpp"

namespace nlsr {
namespace test {

BOOST_AUTO_TEST_SUITE(TestJitter)

BOOST_AUTO_TEST_CASE(Basic)
{
  uint32_t seconds = 10;
  uint32_t ms = 1000 * seconds;
  ndn::time::milliseconds jitter = util::jitter::getTimeWithJitter(seconds);

  BOOST_CHECK_GE(jitter, ndn::time::milliseconds(ms - ms / 2));
  BOOST_CHECK_LE(jitter, ndn::time::milliseconds(ms + ms / 2));

  BOOST_CHECK_NE(util::jitter::getTimeWithJitter(seconds),
                 util::jitter::getTimeWithJitter(seconds));
}

BOOST_AUTO_TEST_SUITE_END()

} //namespace test
} //namespace nlsr
