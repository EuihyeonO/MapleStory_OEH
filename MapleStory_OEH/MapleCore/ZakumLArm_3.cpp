#include "PrecompileHeader.h"
#include "ZakumLArm_3.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

ZakumLArm_3::ZakumLArm_3()
{
	ArmIndex = 3;
	isLeft = true;
}

ZakumLArm_3::~ZakumLArm_3()
{
	Zakum::GetZakum()->LArm_3_UnLoad();
}

void ZakumLArm_3::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();
	
	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 60 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_3::Update(float _DeltaTime)
{
	DeltaTime = _DeltaTime;
}

void ZakumLArm_3::Render(float _DeltaTime)
{

}

void ZakumLArm_3::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	if (isStartDeath == true)
	{
		return;
	}


	int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	switch (Num)
	{
	case 0:
		GameEngineSound::Play("ZakumLArm3Att1.mp3");
		ArmRender->ChangeAnimation("1Attack");
		break;
	case 1:
		GameEngineSound::Play("ZakumLArm3Att2.mp3");
		ArmRender->ChangeAnimation("2Attack");
		break;

	}
}

void ZakumLArm_3::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "LArm3_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true});
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ -190, -25, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 40, -105 }); isAttack = true; isAtCoolTime = true; });
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			
			int RealAtt = Att;

			if (Zakum::GetZakum()->GetIsAtPowerUp() == true)
			{
				RealAtt *= 2;
			}

			Player::GetCurPlayer()->Hit(RealAtt);
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 40.0f, -10.0f });
			Eff->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "LArm3_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
			Eff->ChangeAnimation("1AtEffect");
			Eff->SetAnimationUpdateEvent("1AtEffect", 1, [Eff, this]
				{
					Eff->ColorOptionValue.MulColor.a -= 1.5f * DeltaTime;
					
					if (Eff->ColorOptionValue.MulColor.a <= 0)
					{
						Eff->Death();
					}
				});
		});
	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -80, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	// 2Attack
	ArmRender->CreateAnimation({ .AnimationName = "2Attack",.SpriteName = "LArm3_2Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("2Attack", 0, [this] {GetTransform()->SetLocalPosition({ -135, -65, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -15, -65 });  isAttack = true; isAtCoolTime = true; });
	ArmRender->SetAnimationStartEvent("2Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			
			int RealAtt = Att;

			if (Zakum::GetZakum()->GetIsAtPowerUp() == true)
			{
				RealAtt *= 2;
			}

			Player::GetCurPlayer()->Hit(RealAtt);
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 60.0f, -10.0f });
			Eff->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = "LArm3_2AtEffect",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.01f} });
			Eff->ChangeAnimation("2AtEffect");
			Eff->SetAnimationUpdateEvent("2AtEffect", 5, [Eff, this]
				{
					Eff->ColorOptionValue.MulColor.a -= 3.0f * DeltaTime;

					if (Eff->ColorOptionValue.MulColor.a <= 0)
					{
						Eff->Death();
					}
				});
		});
	ArmRender->SetAnimationUpdateEvent("2Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -80, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Stand
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm3_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, -80, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm3_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -135, -70, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				GetTransform()->SetLocalPosition({ -120, -80, -4.0f });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Death
	std::vector<float> FrameVec;
	FrameVec.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		FrameVec.push_back(0.11f);
	}

	FrameVec[19] = 1.0f;

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm3_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
	ArmRender->SetAnimationUpdateEvent("Death", 19, [this]
		{
			if (isArmDeath == true)
			{
				return;
			}

			ArmRender->ColorOptionValue.MulColor.a -= 4.0f * DeltaTime;

			if (ArmRender->ColorOptionValue.MulColor.a <= 0.0f)
			{
				ArmRender->ColorOptionValue.MulColor.a = 0.0f;

				Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);
				Zakum::GetZakum()->SubArmCount();
				Zakum::GetZakum()->BodyStart();

				isArmDeath = true;
			}
		});

	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			isStartDeath = true;
			GetTransform()->SetLocalPosition({ -150, -95, -4.0f });
			ArmCollision->Off();
		});
}