//
// is_read_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IS_READ_BUFFERED_HPP
#define ASIO_IS_READ_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "RCF/external/asio/asio/detail/config.hpp"
#include "RCF/external/asio/asio/buffered_read_stream_fwd.hpp"
#include "RCF/external/asio/asio/buffered_stream_fwd.hpp"

#include "RCF/external/asio/asio/detail/push_options.hpp"

namespace asio {

namespace detail {

template <typename Stream>
char is_read_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_read_buffered_helper(buffered_read_stream<Stream>* s);

struct is_read_buffered_big_type { char data[10]; };
is_read_buffered_big_type is_read_buffered_helper(...);

} // namespace detail

/// The is_read_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of read data.
template <typename Stream>
class is_read_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// read data.
  static const bool value;
#else
  BOOST_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_read_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio

#include "RCF/external/asio/asio/detail/pop_options.hpp"

#endif // ASIO_IS_READ_BUFFERED_HPP
