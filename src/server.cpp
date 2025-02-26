
/*
 * DayTime Sever
 * */

#include <iostream>
#include <ctime>
#include <string>
#include <asio.hpp>

/*
 * ***Steps***
 *
 * 1 -> using asio::ip::tcp
 * 2 -> declare io context
 * 3 -> make an acceptor
 * 4 -> make a socket
 * 5 -> make acceptor listen for connection on endpoint number
 * 6 -> get current time using ctime 
 * 7 -> use asio::write to write to the socket using asio::buffer and passing the error
 * 8 -> catch error
 * */

using asio::ip::tcp;

std::string getDayTime()
{
	time_t currentTime = time(0);
	return ctime(&currentTime);
}

int main()
{
	try
	{
		asio::io_context io;

		tcp::acceptor acceptor(io, tcp::endpoint(asio::ip::address_v4::any(), 3000));

		for (;;)
		{
			tcp::socket socket(io);

			acceptor.accept(socket);

			std::string timeToSend = getDayTime();

			std::error_code error;
			asio::write(socket, asio::buffer(timeToSend), error);
		}
	}
	catch(std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
