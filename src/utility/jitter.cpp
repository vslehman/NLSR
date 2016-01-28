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

#include "jitter.hpp"
#include "random.hpp"

namespace nlsr {
namespace util {
namespace jitter {

const ndn::time::milliseconds
getTimeWithJitter(uint32_t seconds)
{
  uint32_t ms = 1000 * seconds;
  uint32_t timeWithJitter = random::generateWord32InInterval(ms - ms / 2, ms + ms / 2);

  return ndn::time::milliseconds(timeWithJitter);
}

} // namespace jitter
} // namespace util
} // namespace nlsr
