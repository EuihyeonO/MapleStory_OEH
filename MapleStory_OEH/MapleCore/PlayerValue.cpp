#include "PrecompileHeader.h"
#include "PlayerValue.h"
#include "Player.h"

PlayerValue PlayerValue::Value;

PlayerValue::PlayerValue()
{
 
}

PlayerValue::~PlayerValue()
{

}

void PlayerValue::AddToPlayerToPlayerList(Player* _Player)
{
	Value.PlayerList.push_back(_Player);
}