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

#ifndef NLSR_UTIL_JITTER_HPP
#define NLSR_UTIL_JITTER_HPP

#include <ndn-cxx/util/time.hpp>

namespace nlsr {
namespace util {
namespace jitter {

/**
 * @brief Returns the passed time in milliseconds with jitter applied
 *
 * \param time in seconds
 * \return a time in milliseconds in interval [seconds - seconds / 2, seconds + seconds / 2)
 */
const ndn::time::milliseconds
getTimeWithJitter(uint32_t seconds);

} // namespace jitter
} // namespace util
} // namespace nlsr

#endif // NLSR_UTIL_JITTER_HPP
