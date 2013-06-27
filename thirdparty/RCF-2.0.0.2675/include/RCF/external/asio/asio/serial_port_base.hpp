//
// serial_port_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_SERIAL_PORT_BASE_HPP
#define ASIO_SERIAL_PORT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "RCF/external/asio/asio/detail/config.hpp"

#if defined(ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)
# include <termios.h>
#endif // !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

#include <boost/detail/workaround.hpp>
#include "RCF/external/asio/asio/detail/socket_types.hpp"
#include "RCF/external/asio/asio/error_code.hpp"

#if defined(GENERATING_DOCUMENTATION)
# define ASIO_OPTION_STORAGE implementation_defined
#elif defined(BOOST_WINDOWS) || defined(__CYGWIN__)
# define ASIO_OPTION_STORAGE DCB
#else
# define ASIO_OPTION_STORAGE termios
#endif

#include "RCF/external/asio/asio/detail/push_options.hpp"

namespace asio {

/// The serial_port_base class is used as a base for the basic_serial_port class
/// template so that we have a common place to define the serial port options.
class serial_port_base
{
public:
  /// Serial port option to permit changing the baud rate.
  /**
   * Implements changing the baud rate for a given serial port.
   */
  class baud_rate
  {
  public:
    explicit baud_rate(unsigned int rate = 0);
    unsigned int value() const;
    ASIO_DECL asio::error_code store(
        ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec) const;
    ASIO_DECL asio::error_code load(
        const ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec);
  private:
    unsigned int value_;
  };

  /// Serial port option to permit changing the flow control.
  /**
   * Implements changing the flow control for a given serial port.
   */
  class flow_control
  {
  public:
    enum type { none, software, hardware };
    ASIO_DECL explicit flow_control(type t = none);
    type value() const;
    ASIO_DECL asio::error_code store(
        ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec) const;
    ASIO_DECL asio::error_code load(
        const ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the parity.
  /**
   * Implements changing the parity for a given serial port.
   */
  class parity
  {
  public:
    enum type { none, odd, even };
    ASIO_DECL explicit parity(type t = none);
    type value() const;
    ASIO_DECL asio::error_code store(
        ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec) const;
    ASIO_DECL asio::error_code load(
        const ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the number of stop bits.
  /**
   * Implements changing the number of stop bits for a given serial port.
   */
  class stop_bits
  {
  public:
    enum type { one, onepointfive, two };
    ASIO_DECL explicit stop_bits(type t = one);
    type value() const;
    ASIO_DECL asio::error_code store(
        ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec) const;
    ASIO_DECL asio::error_code load(
        const ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the character size.
  /**
   * Implements changing the character size for a given serial port.
   */
  class character_size
  {
  public:
    ASIO_DECL explicit character_size(unsigned int t = 8);
    unsigned int value() const;
    ASIO_DECL asio::error_code store(
        ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec) const;
    ASIO_DECL asio::error_code load(
        const ASIO_OPTION_STORAGE& storage,
        asio::error_code& ec);
  private:
    unsigned int value_;
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~serial_port_base()
  {
  }

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
private:
  // Workaround to enable the empty base optimisation with Borland C++.
  char dummy_;
#endif
};

} // namespace asio

#include "RCF/external/asio/asio/detail/pop_options.hpp"

#undef ASIO_OPTION_STORAGE

#include "RCF/external/asio/asio/impl/serial_port_base.hpp"
#if defined(ASIO_HEADER_ONLY)
# include "RCF/external/asio/asio/impl/serial_port_base.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // defined(ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // ASIO_SERIAL_PORT_BASE_HPP
