#pragma once

#include <Unet_common.h>

namespace Unet
{
	struct LobbyData
	{
		std::string Name;
		std::string Value;

		LobbyData();
		LobbyData(const std::string &name, const std::string &value);
	};

	class LobbyDataContainer
	{
		friend class Lobby;

	public:
		std::vector<LobbyData> m_data;

	public:
		virtual void SetData(const std::string &name, const std::string &value);
		virtual std::string GetData(const std::string &name) const;
		virtual void RemoveData(const std::string &name);

		virtual json SerializeData() const;
		virtual void DeserializeData(const json &js);

	protected:
		void InternalSetData(const std::string &name, const std::string &value);
		void InternalRemoveData(const std::string &name);
	};
}
