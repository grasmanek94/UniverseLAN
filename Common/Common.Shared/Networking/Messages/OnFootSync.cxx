#include "OnFootSync.hxx"

OnFootSync::OnFootSync()
{ }

void OnFootSync::GetPosition(Vector3& _position) const
{
	_position = position;
}

void OnFootSync::GetRotation(Vector3& _rotation) const
{
	_rotation = rotation;
}

void OnFootSync::GetVelocity(Vector3& _velocity) const
{
	_velocity = velocity;
}

const float OnFootSync::GetCurrentMoveBlendRatio() const
{
	return current_move_blend_ratio;
}

const float OnFootSync::GetTargetMoveBlendRatio() const
{
	return target_move_blend_ratio;
}

const uint32_t OnFootSync::GetCurrentWeaponHash() const
{
	return current_weapon_hash;
}

const bool OnFootSync::IsJumping() const
{
	return is_jumping;
}

const size_t OnFootSync::GetSender() const
{
	return sender;
}

void OnFootSync::SetPosition(const Vector3& _position)
{
	position = _position;
}

void OnFootSync::SetRotation(const Vector3& _rotation)
{
	rotation = _rotation;
}

void OnFootSync::SetVelocity(const Vector3& _velocity)
{
	velocity = _velocity;
}

void OnFootSync::SetCurrentMoveBlendRatio(float ratio)
{
	current_move_blend_ratio = ratio;
}

void OnFootSync::SetTargetMoveBlendRatio(float ratio)
{
	target_move_blend_ratio = ratio;
}

void OnFootSync::SetCurrentWeaponHash(uint32_t hash)
{
	current_weapon_hash = hash;
}

void OnFootSync::SetJumping(bool jumping)
{
	is_jumping = jumping;
}

void OnFootSync::SetSender(size_t id)
{
	sender = id;
}
