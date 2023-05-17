#include "PrecompileHeader.h"
#include "Player.h"
#include "Star.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "SkillActor.h"
#include "BuffList.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <ctime>
#include <functional>


void Player::LuckySeven()
{
	if (MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{
		return;
	}

	int SwingType = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveType = "Swing" + std::to_string(SwingType);
	AniIndex = 0;
	isSwing = true;

	std::shared_ptr<GameEngineCollision> HitMonster = RangeCheck->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	std::function<void(Star&, float)> UpdateFunction = &Star::Move;

	std::shared_ptr<SkillActor> NewSkillActor = GetLevel()->CreateActor<SkillActor>();
	NewSkillActor->SetSkillActor("LuckySeven");
		
	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar1->SetStarName("shuriken");
	NewStar1->SetTimingTime(0.25f);
	NewStar1->SetUpdateFuction(UpdateFunction);
	NewStar1->SetTargetMonster(HitMonster);
	NewStar1->SetType("LuckySeven");

	std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar2->SetStarName("shuriken");
	NewStar2->SetTimingTime(0.40f);
	NewStar2->SetUpdateFuction(UpdateFunction);
	NewStar2->SetTargetMonster(HitMonster);
	NewStar2->SetType("LuckySeven");

}