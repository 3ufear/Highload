//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>

//#include "connection_manager.hpp"
//#include "request_handler.hpp"

connection::connection(boost::asio::io_service& io_service, http_answer_parser& parser)  : socket_(io_service),
         head(),
         answer_parser(parser)//connection_manager& manager), request_handler& handler) : socket_(io_service)
    //connection_manager_(manager),
    //request_handler_(handler)
{

}
boost::asio::ip::tcp::socket& connection::socket()
{
  return socket_;
}

void connection::start()
{
  socket_.async_read_some(boost::asio::buffer(buffer_),
      boost::bind(&connection::handle_read, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void connection::stop()
{
  socket_.close();
}

void connection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  if (!e)
  {
   // boost::tribool result;
   // boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
   //     request_, buffer_.data(), buffer_.data() + bytes_transferred);
	  head.parse(buffer_.data());
	  answer_parser.handle(head.get_valid_url(),head.get_method(),answer);
	  boost::asio::async_write(socket_,answer.to_buf(),
	  		            boost::bind(&connection::handle_write, shared_from_this(),
	  		              boost::asio::placeholders::error));

/*	  if(head.parse(buffer_.data())) {
		  //std::string buffer("HTTP/1.1\n200 OK\nContent-Type: text/html\n\n<html> <title>Test</title><BODY>Hello!</BODY></html>\n");
		  std::vector<boost::asio::const_beforebuffer> buffer;
		  buffer.push_back("HTTP/1.1\n200 OK\nContent-Type: text/html\n\n");
		  boost::asio::async_write(socket_, buffer,
		            boost::bind(&connection::handle_write, shared_from_this(),
		              boost::asio::placeholders::error));
	  }*/

   /* if (result)
    {
      request_handler_.handle_request(request_, reply_);
      boost::asio::async_write(socket_, reply_.to_buffers(),
          boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else if (!result)
    {
      reply_ = reply::stock_reply(reply::bad_request);
      boost::asio::async_write(socket_, reply_.to_buffers(),
          boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      socket_.async_read_some(boost::asio::buffer(buffer_),
          boost::bind(&connection::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }*/
  }
 // else if (e != boost::asio::error::operation_aborted)
  //{
   // connection_manager_.stop(shared_from_this());
  //}
}

void connection::handle_write(const boost::system::error_code& e)
{
  if (!e)
  {
    // Initiate graceful connection closure.
    boost::system::error_code ignored_ec;

    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
  }

  if (e != boost::asio::error::operation_aborted)
  {
	  std::cout<<"Handle STOP"<<std::endl;
    stop();
  }
}

