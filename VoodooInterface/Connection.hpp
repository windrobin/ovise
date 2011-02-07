#ifndef OVISE_VOODOO_CONNECTION_H
#define OVISE_VOODOO_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/signals2.hpp>

using namespace boost::asio;

namespace
{
	unsigned int DecodeInt( std::vector<char> Data )
	{
		unsigned int Result = 0;
		if( Data.size() == 4 )
			Result =
			        ( Data[0] +
			          128 ) * 16777216 +
			        ( Data[1] +
			          128 ) * 65536 +
			        ( Data[2] + 128 ) * 256 + ( Data[3] + 128 );

		return Result;
	}
}

const int HEADER_SIZE = 8;

class CVoodooConnection :
	public boost::enable_shared_from_this<CVoodooConnection>
{
public:
	typedef boost::shared_ptr<CVoodooConnection> CtnPointer;

	static CtnPointer Create( io_service& IOService )
	{
		return CtnPointer( new CVoodooConnection( IOService ) );
	}

	ip::tcp::socket& Socket()
	{
		return mSocket;
	}

	void Connect( std::string Host = "localhost",
	              std::string Port = "22613" )
	{
		ip::tcp::resolver::query    Query( Host, Port );
		ip::tcp::resolver::iterator I = mResolver.resolve( Query );

		ip::tcp::endpoint Endpoint = *I;

		mSocket.async_connect( Endpoint,
			boost::bind( &CVoodooConnection::HandleConnect,
				this,
				placeholders::error,
				++I ) );
	}

	boost::signals2::signal<void (const std::string&)> MessageSignal;


private:
	CVoodooConnection( io_service& IOService )
		: mResolver( IOService ), mSocket( IOService )
	{}

	void HandleConnect( const boost::system::error_code& Error,
	                    ip::tcp::resolver::iterator      EI )
	{
		if( !Error )
		{
			mHeaderData.assign( HEADER_SIZE, '0' );
			async_read( mSocket,
				buffer( mHeaderData ),
				transfer_at_least( HEADER_SIZE ),
				boost::bind( &CVoodooConnection::
					HandleReadHeader,
					this,
					placeholders::error ) );
		}
		else if( EI != ip::tcp::resolver::iterator() )
		{
			mSocket.close();
			ip::tcp::endpoint Endpoint = *EI;
			mSocket.async_connect( Endpoint,
				boost::bind( &CVoodooConnection::HandleConnect,
					this,
					placeholders::error,
					++EI ) );
		}
		else
		{
			std::cout << "Error: " << Error.message() << std::endl;
		}
	}

	void HandleReadHeader( const boost::system::error_code& Error )
	{
		if( !Error )
		{
			std::vector<char>::iterator i = mHeaderData.begin() + 4;
			std::vector<char>           PacketSize;
			PacketSize.assign( mHeaderData.begin(), i );
			std::vector<char> PacketType;
			PacketType.assign( i, mHeaderData.end() );
			unsigned int PSize =  DecodeInt( PacketSize );

			mPacketBuffer.resize( PSize - HEADER_SIZE );
			async_read( mSocket,
				buffer( mPacketBuffer ),
				boost::bind( &CVoodooConnection::
					HandleReadPacket,
					this,
					placeholders::error ) );
		}
		else
		{
			std::cout << "Error: " << Error.message() << std::endl;
		}
	}

	void HandleReadPacket( const boost::system::error_code& Error )
	{
		if( !Error )
		{
			mMessage.assign(
				mPacketBuffer.begin(), mPacketBuffer.end() );
			MessageSignal( mMessage );

			async_read( mSocket,
				buffer( mHeaderData ),
				transfer_at_least( HEADER_SIZE ),
				boost::bind( &CVoodooConnection::
					HandleReadHeader,
					this,
					placeholders::error ) );
		}
		else
		{
			std::cout << "Error: " << Error.message() << std::endl;
		}
	}

	ip::tcp::resolver mResolver;
	ip::tcp::socket   mSocket;

	std::vector<char> mHeaderData;
	std::vector<char> mPacketBuffer;

	std::string mMessage;

	boost::function<void ( const std::string& )> mMessageHandler;
};

#endif // OVISE_VOODOO_CONNECTION_H
