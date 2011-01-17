#include "NetworkInterface.h"

#include "../OViSEAux/SocketMessage.h"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>





/* the implementation class */
class NetworkInterface::NetworkImplementation
{
public:
	NetworkImplementation(void);
	~NetworkImplementation(void);


	void disconnect(void);
	void connectEntityPool(EntityPool*);

	void write_handler(const boost::system::error_code &, std::size_t);
	void accept_handler(const boost::system::error_code &);
	void read_handler(const boost::system::error_code &, std::size_t);
	void StartListening(void);
	void RunThread(void);
	void StopThread(void);



	boost::asio::io_service				io_service;
	boost::asio::ip::tcp::endpoint		endpoint;
	boost::asio::ip::tcp::acceptor		acceptor;
	boost::asio::ip::tcp::socket		sock;
	boost::array<char, 4096>            buffer;
	boost::asio::streambuf              streamBuffer;

	//boost::thread                       serverThread;
	bool								poolConnected;


private:

//	EntityPool*							mEntityPool;
	SocketMessage                       mMessageHandler;


};

NetworkInterface::NetworkImplementation::NetworkImplementation(void) : endpoint(boost::asio::ip::tcp::v4(), 2121), acceptor(io_service, endpoint), sock(io_service) {
	poolConnected = false;
}


NetworkInterface::NetworkImplementation::~NetworkImplementation(void) {

}


void NetworkInterface::NetworkImplementation::StartListening(void) {
	if (poolConnected)
	{
		acceptor.listen();
		acceptor.async_accept(sock, boost::bind(&NetworkInterface::NetworkImplementation::accept_handler, this, _1));

		//start a new thread, with the listing server
		boost::thread thread(boost::bind(&NetworkInterface::NetworkImplementation::RunThread, this));
		//serverThread = thread;
	}

}



/*  */
void NetworkInterface::NetworkImplementation::write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
}


/* read from the socket, give the recieved XML definition of an Entity to the message parser and write the ID of the entity (the existing one,
    if it was an update operation, or the new one if it was the creation of a Entity
*/
void NetworkInterface::NetworkImplementation::read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
  if (!ec)
  {
    std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;

    const char* data=boost::asio::buffer_cast<const char*>(streamBuffer.data());
    int id = mMessageHandler.HandleMessage(data);
    streamBuffer.consume(bytes_transferred);
    boost::asio::write(sock, boost::asio::buffer(boost::lexical_cast<std::string>(id)));


    boost::asio::async_read_until(sock, streamBuffer, "</Entity>",boost::bind(&NetworkInterface::NetworkImplementation::read_handler, this, _1, _2));
  }
}



void NetworkInterface::NetworkImplementation::accept_handler(const boost::system::error_code &ec)
{
	if (!ec)
	{
        boost::asio::write(sock, boost::asio::buffer("ready"));
        boost::asio::async_read_until(sock, streamBuffer, "</Entity>", boost::bind(&NetworkInterface::NetworkImplementation::read_handler, this, _1, _2));
	}
}



/** give the pointer to the entity pool to the message handler.
*/
void NetworkInterface::NetworkImplementation::connectEntityPool(EntityPool* pool) {
	mMessageHandler.connectEntityPool(pool);
	poolConnected = true;

}



void NetworkInterface::NetworkImplementation::RunThread() {
    std::cout << "server thread running" << std::endl;
	io_service.run();
	std::cout << "server thread finished" << std::endl;

}

void NetworkInterface::NetworkImplementation::StopThread() {
    io_service.stop();
    std::cout << "the io_service was interrupted" << std::endl;

}



NetworkInterface::NetworkInterface(void) : nImpl(new NetworkInterface::NetworkImplementation())
{
}



NetworkInterface::~NetworkInterface(void)
{
	//delete nImpl;
}


void NetworkInterface::connectEntityPool(EntityPool* pool) {
	nImpl->connectEntityPool(pool);
}

void NetworkInterface::StartListening() {
	nImpl->StartListening();
}

void NetworkInterface::StopListening() {
	nImpl->StopThread();
}


