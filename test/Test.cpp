#include "tcpconnection.h"
#include "lobby.h"
#include <iostream>

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 8342))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_io_service(), &sLobby);

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
			sLobby.AddPlayer(new_connection);
		}

		start_accept();
	}

	tcp::acceptor acceptor_;
	lobby sLobby;
};

int main()
{
	//try
	{
		boost::asio::io_service io_service;
		tcp_server server(io_service);
		io_service.run();
	}
	//catch (std::exception& e)
	{
		//std::cerr << e.what() << std::endl;
	}

	return 0;
}
