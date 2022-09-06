#include "OnFootSync.hxx"

OnFootSync::OnFootSync()
{ }

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
