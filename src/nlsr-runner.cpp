/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2015,  The University of Memphis,
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

#include "nlsr-runner.hpp"

#include "conf-file-processor.hpp"
#include "logger.hpp"

namespace nlsr {

INIT_LOGGER("NlsrRunner");

NlsrRunner::NlsrRunner(std::string& configFileName, bool isDaemonProcess)
  : m_scheduler(m_ioService)
  , m_face(m_ioService)
  , m_nlsr(m_ioService, m_scheduler, m_face)
{
  m_nlsr.setConfFileName(configFileName);
  m_nlsr.setIsDaemonProcess(isDaemonProcess);
}

void
NlsrRunner::run()
{
  ConfFileProcessor configProcessor(m_nlsr, m_nlsr.getConfFileName());

  if (!configProcessor.processConfFile()) {
    throw Error("Error in configuration file processing! Exiting from NLSR");
  }

  if (m_nlsr.getConfParameter().isLog4CxxConfAvailable()) {
    INIT_LOG4CXX(m_nlsr.getConfParameter().getLog4CxxConfPath());
  }
  else {
    INIT_LOGGERS(m_nlsr.getConfParameter().getLogDir(), m_nlsr.getConfParameter().getLogLevel());
  }

  m_nlsr.initialize();

  if (m_nlsr.getIsSetDaemonProcess()) {
    m_nlsr.daemonize();
  }

  try {
    m_nlsr.startEventLoop();
  }
  catch (std::exception& e) {
    _LOG_FATAL("ERROR: " << e.what());
    std::cerr << "ERROR: " << e.what() << std::endl;

    m_nlsr.getFib().clean();
    m_nlsr.destroyFaces();
  }

  	/*

    STATISTICS COUNT

	Data collection printed on file

    */

  //_LOG_DEBUG("StatisticsCollection" << m_nlsr.getStatistics());
  /*
  _LOG_DEBUG("\nHello Interest " << m_nlsr.getStatistics().getSentHelloInt());
  _LOG_DEBUG("\nHello Data " << m_nlsr.getStatistics().getSentHelloData());
  _LOG_DEBUG("\nSync Interest " << m_nlsr.getStatistics().getSyncInt());
  _LOG_DEBUG("\nRe Sync Interest " << m_nlsr.getStatistics().getReSyncInt());
  _LOG_DEBUG("\nSync Data " << m_nlsr.getStatistics().getSentSyncData());
  _LOG_DEBUG("\nLSA Interest " << m_nlsr.getStatistics().getSentLSAInt());
  _LOG_DEBUG("\nAdj Data " << m_nlsr.getStatistics().getSentAdjData());
  _LOG_DEBUG("\nCoord Data " << m_nlsr.getStatistics().getSentCoorData());
  _LOG_DEBUG("\nName Data " << m_nlsr.getStatistics().getSentNameData());

  _LOG_DEBUG("\n\nHello Interest " << m_nlsr.getStatistics().getRcvHelloInt());
  _LOG_DEBUG("\nHello Data " << m_nlsr.getStatistics().getRcvHelloData());
  _LOG_DEBUG("\nSync Interest " << m_nlsr.getStatistics().getRcvSyncInt());

  _LOG_DEBUG("\nSync Data " << m_nlsr.getStatistics().getRcvSyncData());
  _LOG_DEBUG("\nLSA Interest " << m_nlsr.getStatistics().getRcvLSAInt());
  _LOG_DEBUG("\nAdj Data " << m_nlsr.getStatistics().getRcvAdjData());
  _LOG_DEBUG("\nCoord Data " << m_nlsr.getStatistics().getRcvCoorData());
  _LOG_DEBUG("\nName Data " << m_nlsr.getStatistics().getRcvNameData());

  _LOG_DEBUG("\nERROR " << m_nlsr.getStatistics().getError());*/
}

void
NlsrRunner::printUsage(const std::string& programName)
{
  std::cout << "Usage: " << programName << " [OPTIONS...]" << std::endl;
  std::cout << "   NDN routing...." << std::endl;
  std::cout << "       -d          Run in daemon mode" << std::endl;
  std::cout << "       -f <FILE>   Specify configuration file name" << std::endl;
  std::cout << "       -V          Display version information" << std::endl;
  std::cout << "       -h          Display this help message" << std::endl;
}

} // namespace nlsr
