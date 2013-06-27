//
// detail/win_iocp_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_WIN_IOCP_OPERATION_HPP
#define ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "RCF/external/asio/asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP)

#include "RCF/external/asio/asio/detail/op_queue.hpp"
#include "RCF/external/asio/asio/detail/win_iocp_io_service_fwd.hpp"
#include "RCF/external/asio/asio/error_code.hpp"

#include "RCF/external/asio/asio/detail/push_options.hpp"

namespace asio {
namespace detail {

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class win_iocp_operation
  : public OVERLAPPED
{
public:
  void complete(win_iocp_io_service& owner,
      const asio::error_code& ec = asio::error_code(),
      std::size_t bytes_transferred = 0)
  {
    func_(&owner, this, ec, bytes_transferred);
  }

  void destroy()
  {
    func_(0, this, asio::error_code(), 0);
  }

protected:
  typedef void (*func_type)(win_iocp_io_service*,
      win_iocp_operation*, asio::error_code, std::size_t);

  win_iocp_operation(func_type func)
    : next_(0),
      func_(func)
  {
    reset();
  }

  // Prevents deletion through this type.
  ~win_iocp_operation()
  {
  }

  void reset()
  {
    Internal = 0;
    InternalHigh = 0;
    Offset = 0;
    OffsetHigh = 0;
    hEvent = 0;
    ready_ = 0;
  }

private:
  friend class op_queue_access;
  friend class win_iocp_io_service;
  win_iocp_operation* next_;
  func_type func_;
  long ready_;
};

} // namespace detail
} // namespace asio

#include "RCF/external/asio/asio/detail/pop_options.hpp"

#endif // defined(ASIO_HAS_IOCP)

#endif // ASIO_DETAIL_WIN_IOCP_OPERATION_HPP
