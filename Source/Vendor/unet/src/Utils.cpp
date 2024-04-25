#include <Unet_common.h>
#include <Unet/Utils.h>

std::vector<uint8_t> Unet::JsonPack(const json &js)
{
	return json::to_msgpack(js);
}

json Unet::JsonUnpack(const std::vector<uint8_t> &data)
{
	try {
		return json::from_msgpack(data);
	} catch (json::exception ex) {
		return json();
	}
}

json Unet::JsonUnpack(uint8_t* data, size_t size)
{
	try {
		return json::from_msgpack(data, size);
	} catch (json::exception ex) {
		return json();
	}
}
