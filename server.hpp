//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <set>
#include <boost/noncopyable.hpp>
#include "connection.hpp"
#include "http_answer_parser.hpp"
//#include "connection_manager.hpp"
//#include "request_handler.hpp"


/// The top-level class of the HTTP server.
class server
  : private boost::noncopyable
{
public:
  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit server(const std::string& address, const std::string& port,
      const std::string& doc_root);

  /// Run the server's io_service loop.
  //void run();

private:
  /// Initiate an asynchronous accept operation.
  void start_accept();

  /// Handle completion of an asynchronous accept operation.
  void handle_accept(const boost::system::error_code& e);

  /// Handle a request to stop the server.
  void handle_stop();

  void start(connection_ptr c);

  void stop(connection_ptr c);

  boost::asio::ip::tcp::socket& socket();

  boost::asio::io_service io_service_;

  boost::asio::signal_set signals_;

  boost::asio::ip::tcp::acceptor acceptor_;

  std::set<connection_ptr> connections_;

  http_answer_parser parser;

  connection_ptr new_connection_;
};


#endif // HTTP_SERVER_HPP
