#pragma once
#include <Networking/SendableEventMessage.hxx>
#include <Math/Math.hxx>
#include <string>

class PlayerJoin
{
private:
	std::wstring player_name;
	size_t sender;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(player_name, sender);
	}

	UniqueClassId_Declare(PlayerJoin, true);

	PlayerJoin();

	const std::wstring GetName() const;
	const size_t GetSender() const;

	void SetName(const std::wstring& msg);
	void SetSender(size_t id);
};

class PlayerQuit
{
private:
	size_t sender;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(sender);
	}

	UniqueClassId_Declare(PlayerQuit, true);

	PlayerQuit();

	const size_t GetSender() const;
	void SetSender(size_t id);
};

class PlayerSpawn
{
public:
	uint32_t model_hash;
	Vector3 position;
	Vector3 rotation;
	size_t sender;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(model_hash, position, rotation, sender);
	}

	UniqueClassId_Declare(PlayerSpawn, true);

	PlayerSpawn();

	const uint32_t GetModelHash() const;
	void GetPosition(Vector3& _position) const;
	void GetRotation(Vector3& _rotation) const;
	const size_t GetSender() const;

	void SetModelHash(uint32_t hash);
	void SetPosition(const Vector3& _position);
	void SetRotation(const Vector3& _rotation);
	void SetSender(size_t id);
};

class PlayerDespawn
{
private:
	size_t sender;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(sender);
	}

	UniqueClassId_Declare(PlayerDespawn, true);

	PlayerDespawn();

	const size_t GetSender() const;
	void SetSender(size_t id);
};
