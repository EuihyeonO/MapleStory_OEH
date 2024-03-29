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
#include <GameEnginePlatform/GameEngineSound.h>
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

	if(isSwing == false && isFalling == false && isKeyJump == false)
	{
		PlayerValue::Value.SetMp(CurMp - 10);
		GameEngineSound::Play("Haste.mp3");

		if (MyBuffList->IsBuffOn("Haste") == false)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			Haste->SetSkillActor("Haste");

			std::function<void(Player&)> EndFunction = [this](Player&) 
			{
				MoveSpeed = BasicMoveSpeed; 
				JumpPower -= 30.0f;
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("Haste", EndFunction, 50.0f);

			MoveSpeed = BasicMoveSpeed + 30.0f;
			JumpPower += 30.0f;
		}

		else if (MyBuffList->IsBuffOn("Haste") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			Haste->SetSkillActor("Haste");

			MyBuffList->Rebuff("Haste");
		}
	}
}

void Player::HeroesOfMaple()
{
	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	if (isSwing == false && isFalling == false && isKeyJump == false)
	{
		PlayerValue::Value.SetMp(CurMp - 10);
		GameEngineSound::Play("HeroesOfMaple.mp3");

		if (MyBuffList->IsBuffOn("HeroesOfMaple") == false)
		{
			std::shared_ptr<SkillActor> HeroesOfMaple = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			HeroesOfMaple->SetSkillActor("HeroesOfMaple");

			int Str = PlayerValue::GetValue()->GetStr();
			int Dex = PlayerValue::GetValue()->GetDex();
			int Int = PlayerValue::GetValue()->GetInt();
			int Luk = PlayerValue::GetValue()->GetLuk();

			std::function<void(Player&)> EndFunction = [=, this](Player&)
			{
				PlayerValue::GetValue()->AddStr(static_cast<int>(-Str * 0.15f));
				PlayerValue::GetValue()->AddDex(static_cast<int>(-Dex * 0.15f));
				PlayerValue::GetValue()->AddInt(static_cast<int>(-Int * 0.15f));
				PlayerValue::GetValue()->AddLuk(static_cast<int>(-Luk * 0.15f));
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("HeroesOfMaple", EndFunction, 50.0f);

			PlayerValue::GetValue()->AddStr(static_cast<int>(Str * 0.15f));
			PlayerValue::GetValue()->AddDex(static_cast<int>(Dex * 0.15f));
			PlayerValue::GetValue()->AddInt(static_cast<int>(Int * 0.15f));
			PlayerValue::GetValue()->AddLuk(static_cast<int>(Luk * 0.15f));
		}

		else if (MyBuffList->IsBuffOn("HeroesOfMaple") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			Haste->SetSkillActor("HeroesOfMaple");

			MyBuffList->Rebuff("HeroesOfMaple");
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

	if (isSwing == false && isMovable == true && isFalling == false && isKeyJump == false)
	{
		PlayerValue::Value.SetMp(CurMp - 10);
		GameEngineSound::Play("JavelinBooster.mp3");

		if (MyBuffList->IsBuffOn("JavelinBooster") == false)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			Haste->SetSkillActor("JavelinBooster");

			std::function<void(Player&)> EndFunction = [this](Player&)
			{
				PlayerValue::Value.SetAttackSpeedToBasic();
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("JavelinBooster", EndFunction, 50.0f);

			int GetJavelinBoosterLv = PlayerValue::Value.GetJavelinBoosterLv();
			PlayerValue::Value.PlusAttackSpeed(GetJavelinBoosterLv * 0.05f);
		}

		else if (MyBuffList->IsBuffOn("JavelinBooster") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
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


	if (isSwing == false && isMovable == true && isFalling == false && isKeyJump == false)
	{
		PlayerValue::Value.SetMp(CurMp - 10);
		GameEngineSound::Play("ShadowPartner.mp3");

		if (MyBuffList->IsBuffOn("ShadowPartner") == false)
		{
			std::shared_ptr<SkillActor> ShadowPartner = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			ShadowPartner->SetSkillActor("ShadowPartner");

			std::function<void(Player&)> EndFunction = [this](Player&)
			{
				isOnShadow = false;
			};

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("ShadowPartner", EndFunction, 50.0f);
			isOnShadow = true;
		}

		else if (MyBuffList->IsBuffOn("ShadowPartner") == true)
		{
			std::shared_ptr<SkillActor> ShadowPartner = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
			ShadowPartner->SetSkillActor("ShadowPartner", false);

			MyBuffList->Rebuff("ShadowPartner");
		}
	}
}