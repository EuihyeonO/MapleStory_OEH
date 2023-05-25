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

void Player::Haste()
{
	int CurMp = PlayerValue::Value.GetMp();
	
	if (CurMp < 10)
	{
		return;
	}

	if(isSwing == false && isGround == true)
	{
		PlayerValue::Value.SetMp(CurMp - 10);

		if (MyBuffList->IsBuffOn("Haste") == false)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("Haste");

			std::function<void(Player&)> EndFunction = [this](Player&) 
			{
				MoveSpeed = BasicMoveSpeed; 
				JumpPower -= 30.0f;
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("Haste", EndFunction, 5.0f);

			MoveSpeed = BasicMoveSpeed + 30.0f;
			JumpPower += 30.0f;
		}

		else if (MyBuffList->IsBuffOn("Haste") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("Haste");

			MyBuffList->Rebuff("Haste");
		}
	}
}


void Player::JavelinBooster()
{
	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	if (isSwing == false && isGround == true)
	{
		PlayerValue::Value.SetMp(CurMp - 10);

		if (MyBuffList->IsBuffOn("JavelinBooster") == false)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("JavelinBooster");

			std::function<void(Player&)> EndFunction = [this](Player&)
			{
				PlayerValue::Value.SetAttackSpeedToBasic();
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("JavelinBooster", EndFunction, 5.0f);

			int GetJavelinBoosterLv = PlayerValue::Value.GetJavelinBoosterLevel();
			PlayerValue::Value.PlusAttackSpeed(GetJavelinBoosterLv * 0.05f);
		}

		else if (MyBuffList->IsBuffOn("JavelinBooster") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("JavelinBooster");

			MyBuffList->Rebuff("JavelinBooster");
		}
	}
}

void Player::ShadowPartner()
{
	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	if (isSwing == false && isGround == true)
	{
		PlayerValue::Value.SetMp(CurMp - 10);

		if (MyBuffList->IsBuffOn("ShadowPartner") == false)
		{
			std::shared_ptr<SkillActor> ShadowPartner = GetLevel()->CreateActor<SkillActor>();
			ShadowPartner->SetSkillActor("ShadowPartner");

			std::function<void(Player&)> EndFunction = [this](Player&)
			{
				isOnShadow = false;
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("ShadowPartner", EndFunction, 20.0f);
			isOnShadow = true;
		}

		else if (MyBuffList->IsBuffOn("ShadowPartner") == true)
		{
			std::shared_ptr<SkillActor> ShadowPartner = GetLevel()->CreateActor<SkillActor>();
			ShadowPartner->SetSkillActor("ShadowPartner");

			MyBuffList->Rebuff("ShadowPartner");
		}
	}
}