//
// asio.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_HPP
#define ASIO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "RCF/external/asio/asio/basic_datagram_socket.hpp"
#include "RCF/external/asio/asio/basic_deadline_timer.hpp"
#include "RCF/external/asio/asio/basic_io_object.hpp"
#include "RCF/external/asio/asio/basic_raw_socket.hpp"
#include "RCF/external/asio/asio/basic_serial_port.hpp"
#include "RCF/external/asio/asio/basic_socket_acceptor.hpp"
#include "RCF/external/asio/asio/basic_socket_iostream.hpp"
#include "RCF/external/asio/asio/basic_socket_streambuf.hpp"
#include "RCF/external/asio/asio/basic_stream_socket.hpp"
#include "RCF/external/asio/asio/basic_streambuf.hpp"
#include "RCF/external/asio/asio/buffer.hpp"
#include "RCF/external/asio/asio/buffered_read_stream_fwd.hpp"
#include "RCF/external/asio/asio/buffered_read_stream.hpp"
#include "RCF/external/asio/asio/buffered_stream_fwd.hpp"
#include "RCF/external/asio/asio/buffered_stream.hpp"
#include "RCF/external/asio/asio/buffered_write_stream_fwd.hpp"
#include "RCF/external/asio/asio/buffered_write_stream.hpp"
#include "RCF/external/asio/asio/buffers_iterator.hpp"
#include "RCF/external/asio/asio/completion_condition.hpp"
#include "RCF/external/asio/asio/datagram_socket_service.hpp"
#include "RCF/external/asio/asio/deadline_timer_service.hpp"
#include "RCF/external/asio/asio/deadline_timer.hpp"
#include "RCF/external/asio/asio/error.hpp"
#include "RCF/external/asio/asio/error_code.hpp"
#include "RCF/external/asio/asio/handler_alloc_hook.hpp"
#include "RCF/external/asio/asio/handler_invoke_hook.hpp"
#include "RCF/external/asio/asio/io_service.hpp"
#include "RCF/external/asio/asio/ip/address.hpp"
#include "RCF/external/asio/asio/ip/address_v4.hpp"
#include "RCF/external/asio/asio/ip/address_v6.hpp"
#include "RCF/external/asio/asio/ip/basic_endpoint.hpp"
#include "RCF/external/asio/asio/ip/basic_resolver.hpp"
#include "RCF/external/asio/asio/ip/basic_resolver_entry.hpp"
#include "RCF/external/asio/asio/ip/basic_resolver_iterator.hpp"
#include "RCF/external/asio/asio/ip/basic_resolver_query.hpp"
#include "RCF/external/asio/asio/ip/host_name.hpp"
#include "RCF/external/asio/asio/ip/icmp.hpp"
#include "RCF/external/asio/asio/ip/multicast.hpp"
#include "RCF/external/asio/asio/ip/resolver_query_base.hpp"
#include "RCF/external/asio/asio/ip/resolver_service.hpp"
#include "RCF/external/asio/asio/ip/tcp.hpp"
#include "RCF/external/asio/asio/ip/udp.hpp"
#include "RCF/external/asio/asio/ip/unicast.hpp"
#include "RCF/external/asio/asio/ip/v6_only.hpp"
#include "RCF/external/asio/asio/is_read_buffered.hpp"
#include "RCF/external/asio/asio/is_write_buffered.hpp"
#include "RCF/external/asio/asio/local/basic_endpoint.hpp"
#include "RCF/external/asio/asio/local/connect_pair.hpp"
#include "RCF/external/asio/asio/local/datagram_protocol.hpp"
#include "RCF/external/asio/asio/local/stream_protocol.hpp"
#include "RCF/external/asio/asio/placeholders.hpp"
#include "RCF/external/asio/asio/posix/basic_descriptor.hpp"
#include "RCF/external/asio/asio/posix/basic_stream_descriptor.hpp"
#include "RCF/external/asio/asio/posix/descriptor_base.hpp"
#include "RCF/external/asio/asio/posix/stream_descriptor.hpp"
#include "RCF/external/asio/asio/posix/stream_descriptor_service.hpp"
#include "RCF/external/asio/asio/raw_socket_service.hpp"
#include "RCF/external/asio/asio/read.hpp"
#include "RCF/external/asio/asio/read_at.hpp"
#include "RCF/external/asio/asio/read_until.hpp"
#include "RCF/external/asio/asio/serial_port.hpp"
#include "RCF/external/asio/asio/serial_port_base.hpp"
#include "RCF/external/asio/asio/serial_port_service.hpp"
#include "RCF/external/asio/asio/socket_acceptor_service.hpp"
#include "RCF/external/asio/asio/socket_base.hpp"
#include "RCF/external/asio/asio/strand.hpp"
#include "RCF/external/asio/asio/stream_socket_service.hpp"
#include "RCF/external/asio/asio/streambuf.hpp"
#include "RCF/external/asio/asio/system_error.hpp"
#include "RCF/external/asio/asio/thread.hpp"
#include "RCF/external/asio/asio/time_traits.hpp"
#include "RCF/external/asio/asio/version.hpp"
#include "RCF/external/asio/asio/windows/basic_handle.hpp"
#include "RCF/external/asio/asio/windows/basic_random_access_handle.hpp"
#include "RCF/external/asio/asio/windows/basic_stream_handle.hpp"
#include "RCF/external/asio/asio/windows/overlapped_ptr.hpp"
#include "RCF/external/asio/asio/windows/random_access_handle.hpp"
#include "RCF/external/asio/asio/windows/random_access_handle_service.hpp"
#include "RCF/external/asio/asio/windows/stream_handle.hpp"
#include "RCF/external/asio/asio/windows/stream_handle_service.hpp"
#include "RCF/external/asio/asio/write.hpp"
#include "RCF/external/asio/asio/write_at.hpp"

#endif // ASIO_HPP
