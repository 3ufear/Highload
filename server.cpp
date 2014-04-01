/*
 * server.cpp
 *
 *  Created on: 28.03.2014
 *      Author: phil
 */

#include "server.hpp"
#include <boost/bind.hpp>

server::server(const std::string& address, const std::string& port, const std::string& doc_root)
	  : io_service_(),
	    signals_(io_service_),
	    acceptor_(io_service_),
	    //connection_manager_(),
	    new_connection_()
	    //request_handler_(doc_root)
	{
	  // Register to handle the signals that indicate when the server should exit.
	  // It is safe to register for the same signal multiple times in a program,
	  // provided all registration for the specified signal is made through Asio.
	//std::cout<<"c"<<std::endl;
	signals_.add(SIGINT);
	signals_.add(SIGTERM);
	#if defined(SIGQUIT)
	  signals_.add(SIGQUIT);
	#endif // defined(SIGQUIT)
	  signals_.async_wait(boost::bind(&server::handle_stop, this));

	  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	  boost::asio::ip::tcp::resolver resolver(io_service_);
	  boost::asio::ip::tcp::resolver::query query(address, port);
	  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	  acceptor_.open(endpoint.protocol());
	  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	  //std::cout<<"before"<<std::endl;
	  try {
	   acceptor_.bind(endpoint);
	  }
	  catch(std::exception &e) {
		  std::cerr<<e.what()<<std::endl;
		  return;
	  }
	  std::cout<<"after"<<std::endl;
	  acceptor_.listen();

	  start_accept();
	  io_service_.run();

}

void server::start_accept() {

    //boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	//socket_.async_connect();
	std::cout<<"start accept"<<std::endl;
	  new_connection_.reset(new connection(io_service_)); //,request_handler_));
	  acceptor_.async_accept(new_connection_->socket(),
	      boost::bind(&server::handle_accept, this,
	        boost::asio::placeholders::error));
}



void server::handle_accept(const boost::system::error_code& e) {
	if (!acceptor_.is_open())
	  {
	    return;
	  }
	if (!e)
	  {
		start(new_connection_);
	  }
	start_accept();

}

void server::handle_stop()
{
  acceptor_.close();
}


void server::start(connection_ptr c)
{
  connections_.insert(c);
  c->start();
}

void server::stop(connection_ptr c)
{
  connections_.erase(c);
  c->stop();
}


