#include "qtCommon.h"

msgEvent::msgEvent(net_connection_ptr ptr, const net::message<MSG_TYPE>& m) : QEvent(type),
		client(ptr),
		msg(std::move(m))
{

}
