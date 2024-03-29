#include "PrecompileHeader.h"
#include "Zakum.h"
#include "ZakumRArm_0.h"
#include "ZakumRArm_1.h"
#include "ZakumRArm_2.h"
#include "ZakumRArm_3.h"

#include "ZakumLArm_0.h"
#include "ZakumLArm_1.h"
#include "ZakumLArm_2.h"
#include "ZakumLArm_3.h"

#include "Boogie.h"
#include "SmallZakum0.h"
#include "SmallZakum1.h"
#include "SmallZakum2.h"

#include "Player.h"
#include "PlayerValue.h"

#include "DropItem.h"

#include "ContentUIRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>

std::shared_ptr<Zakum> Zakum::GlobalZakum = nullptr;

Zakum::Zakum()
{
}

Zakum::~Zakum()
{
}

void Zakum::Start()
{
	GameEngineSoundPlayer Sound = GameEngineSound::Play("ZakumSpawn.mp3");
	Sound.SetVolume(1.0f);

	GlobalZakum = DynamicThis<Zakum>();

	TimeCounting();

	BodyRender = CreateComponent<GameEngineSpriteRenderer>();
	GetTransform()->SetLocalPosition({ -10.0f , 40.0f, -5.0f });
	
	SetAnimation();

	MoveType = "";
	isSpawnAnimationEnd = false;
	BodyRender->ChangeAnimation("Spawn");

	BodyCollision = CreateComponent<GameEngineCollision>();
	BodyCollision->SetColType(ColType::AABBBOX2D);
	BodyCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	BodyCollision->GetTransform()->SetWorldPosition({ 20, 0 });
	BodyCollision->GetTransform()->SetWorldScale({ 160, 400 });
	BodyCollision->Off();
}

void Zakum::Update(float _DeltaTime)
{
	TimeCounting();
	DeltaTime = _DeltaTime;

	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
		GameEngineInput::CreateKey("MyTest1", 'V');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
		LArm_0->Hit(201, true);
		LArm_1->Hit(201, true);
		LArm_2->Hit(201, true);
		LArm_3->Hit(201, true);
					  
		RArm_0->Hit(201, true);
		RArm_1->Hit(201, true);
		RArm_2->Hit(201, true);
		RArm_3->Hit(201, true);
	}

	FunctionUpdate();
	Attack();

}

void Zakum::Attack()
{
	if (isHit == true)
	{
		return;
	}

	if (BodyAttackStart == true)
	{
		BodyAttack();
	}
	else
	{
		ArmAttack();
	}
}

void Zakum::Render(float _DeltaTime)
{

}

void Zakum::CreateArm(bool _isLeft, int _ArmIndex)
{
	if (_isLeft == true)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (LArm_0 == nullptr)
			{
				LArm_0 = GetLevel()->CreateActor<ZakumLArm_0>();
				LArm_0->GetTransform()->SetLocalPosition({ -110, 110, -4.0f });
			}
			break;
		case 1:
			if (LArm_1 == nullptr)
			{
				LArm_1 = GetLevel()->CreateActor<ZakumLArm_1>();
				LArm_1->GetTransform()->SetLocalPosition({ -140, 60, -4.0f });
			}
			break;
		case 2:
			if (LArm_2 == nullptr)
			{
				LArm_2 = GetLevel()->CreateActor<ZakumLArm_2>();
				LArm_2->GetTransform()->SetLocalPosition({ -140, -10, -4.0f });
			}
			break;
		case 3:
			if (LArm_3 == nullptr)
			{
				LArm_3 = GetLevel()->CreateActor<ZakumLArm_3>();
				LArm_3->GetTransform()->SetLocalPosition({ -140, -80, -4.0f });
			}
			break;
		}
	}
	else if (_isLeft == false)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (RArm_0 == nullptr)
			{
				RArm_0 = GetLevel()->CreateActor<ZakumRArm_0>();
				RArm_0->GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
			}
			break;
		case 1:
			if (RArm_1 == nullptr)
			{
				RArm_1 = GetLevel()->CreateActor<ZakumRArm_1>();
				RArm_1->GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
			}
			break;
		case 2:
			if (RArm_2 == nullptr)
			{
				RArm_2 = GetLevel()->CreateActor<ZakumRArm_2>();
				RArm_2->GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
			}
			break;
		case 3:
			if (RArm_3 == nullptr)
			{
				RArm_3 = GetLevel()->CreateActor<ZakumRArm_3>();
				RArm_3->GetTransform()->SetLocalPosition({ 180, -80, -4.0f });
			}
			break;
		}
	}
}

void Zakum::SetAnimation()
{
	BodyRender->CreateAnimation({ .AnimationName = "Spawn",.SpriteName = "ZakumSpawn",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	
	BodyRender->SetAnimationStartEvent("Spawn", 1, [this]
		{
			BodyRender->CreateAnimation({ .AnimationName = "Phase1Die",.SpriteName = "Phase1Die",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase2Die",.SpriteName = "Phase2Die",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase3Die",.SpriteName = "Phase3Die",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
			
			BodyRender->SetAnimationUpdateEvent("Phase1Die", 0, [this]
				{
					GetTransform()->SetLocalPosition({ 12, 0, -4.0f });
				});

			BodyRender->SetAnimationUpdateEvent("Phase1Die", 9, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						GetTransform()->SetLocalPosition({ 12, 3, -4.0f });
						BodyRender->ChangeAnimation("Phase2Stand");

						GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
							{
								BodyCollision->On();
								isHit = false;
								CurPhase = 2;
							});
					}
				});

			BodyRender->SetAnimationUpdateEvent("Phase2Die", 0, [this]
				{
					GetTransform()->SetLocalPosition({ 3, 15, -4.0f });
				});

			BodyRender->SetAnimationUpdateEvent("Phase2Die", 9, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						BodyRender->ChangeAnimation("Phase3Stand");
						GetTransform()->SetLocalPosition({ 12, 18, -4.0f });

						GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
							{
								BodyCollision->On();
								isHit = false;
								CurPhase = 3;
							});
					}
				});

			BodyRender->SetAnimationUpdateEvent("Phase3Die", 16, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						BodyRender->ColorOptionValue.MulColor.a -= 1.0f * DeltaTime;

						if (BodyRender->ColorOptionValue.MulColor.a <= 0)
						{
							BodyRender->ColorOptionValue.MulColor.a = 0.0f;

							GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
								{
									std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
									NewItem->SetQuadraticFunction(1.0f, GetTransform()->GetWorldPosition() + float4{ 0, -150.0f }, 250.0f);
									NewItem->SetDropItemInfo("CAPOFZAKUM", static_cast<int>(ItemType::Equip));
									
									for (int i = 0; i < 10; i++)
									{
										std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
										NewItem->SetQuadraticFunction(1.0f - 30.0f * (i + 1), GetTransform()->GetWorldPosition() + float4{ 0, -150.0f }, 250.0f);
										NewItem->SetDropItemInfo("ZAKUMSTONE", static_cast<int>(ItemType::Etc));
									}

									for (int i = 0; i < 10; i++)
									{
										std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
										NewItem->SetQuadraticFunction(1.0f + 30.0f * (i + 1), GetTransform()->GetWorldPosition() + float4{ 0, -150.0f }, 250.0f);
										NewItem->SetDropItemInfo("ZAKUMSTONE", static_cast<int>(ItemType::Etc));
									}
								});

							GetLevel()->TimeEvent.AddEvent(10.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {Death();});

							BodyRender->Off();
							BodyRender->ChangeAnimation("Phase3Stand");
						}
					}
				});
		});

	BodyRender->SetAnimationStartEvent("Spawn", 2, [this]
		{

			BodyRender->CreateAnimation({ .AnimationName = "Phase1Hit",.SpriteName = "Phase1Hit",.FrameInter = 0.6f,.Loop = false,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase2Hit",.SpriteName = "Phase2Hit",.FrameInter = 0.6f,.Loop = false,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase3Hit",.SpriteName = "Phase3Hit",.FrameInter = 0.6f,.Loop = false,.ScaleToTexture = true });
			

			BodyRender->SetAnimationUpdateEvent("Phase1Hit", 0, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						isHit = false;
						BodyRender->ChangeAnimation("Phase1Stand");
					}
				});

			BodyRender->SetAnimationUpdateEvent("Phase2Hit", 0, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						isHit = false;
						BodyRender->ChangeAnimation("Phase2Stand");
					}
				});

			BodyRender->SetAnimationUpdateEvent("Phase3Hit", 0, [this]
				{
					if (BodyRender->IsAnimationEnd() == true)
					{
						isHit = false;
						BodyRender->ChangeAnimation("Phase3Stand");
					}
				});
		});

	BodyRender->SetAnimationStartEvent("Spawn", 3, [this]
		{
			BodyRender->CreateAnimation({ .AnimationName = "Phase1Stand",.SpriteName = "Phase1Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase2Stand",.SpriteName = "Phase2Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });
			BodyRender->CreateAnimation({ .AnimationName = "Phase3Stand",.SpriteName = "Phase3Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true }); 
		});

	BodyRender->SetAnimationStartEvent("Spawn", 5, [this]
		{
			SetPhase1Attack();
		});
	BodyRender->SetAnimationStartEvent("Spawn", 10, [this]
		{
			SetPhase2Attack();
		});
	BodyRender->SetAnimationStartEvent("Spawn", 15, [this]
		{
			SetPhase3Attack();
		});

	BodyRender->SetAnimationStartEvent("Spawn", 20, [this]
		{
			BodyRender->ChangeAnimation("Phase1Stand");
			GetTransform()->AddLocalPosition({ 22, -33, 0.0f });
			CreateArm(true, 0);
			CreateArm(true, 1);
			CreateArm(true, 2);
			CreateArm(true, 3);
			CreateArm(false, 0);
			CreateArm(false, 1);
			CreateArm(false, 2);
			CreateArm(false, 3);
		});
}

void Zakum::ArmDeath(bool _isLeft, int _ArmIndex)
{
	if (_isLeft == true)
	{
		switch (_ArmIndex)
		{
		case 0:
			if(LArm_0 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {LArm_0->Death(); LArm_0 = nullptr; });
			}
			break;
		case 1:
			if (LArm_1 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {LArm_1->Death(); LArm_1 = nullptr; });
			}
			break;
		case 2:
			if (LArm_2 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {LArm_2->Death(); LArm_2 = nullptr; });
			}
			break;
		case 3:
			if (LArm_3 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {LArm_3->Death(); LArm_3 = nullptr; });
			}
			break;
		}
	}
	else if (_isLeft == false)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (RArm_0 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {RArm_0->Death(); RArm_0 = nullptr; });
			}
			break;
		case 1:
			if (RArm_1 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {RArm_1->Death(); RArm_1 = nullptr; });
			}
			break;
		case 2:
			if (RArm_2 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {RArm_2->Death(); RArm_2 = nullptr;  });
			}
			break;
		case 3:
			if (RArm_3 != nullptr)
			{
				GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {RArm_3->Death(); RArm_3 = nullptr; });
			}
			break;
		}
	}
}


void Zakum::ArmAttack()
{
	if (isArmAttCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 7);

	switch (Num)
	{
	case 0:
		if(LArm_0 != nullptr)
		{
			LArm_0->Attack();
		}
		break;
	case 1:
		if (LArm_1 != nullptr)
		{
			LArm_1->Attack();
		}
		break;
	case 2:
		if (LArm_2 != nullptr)
		{
			LArm_2->Attack();
		}
		break;
	case 3:
		if (LArm_3 != nullptr)
		{
			LArm_3->Attack();
		}
		break;
	case 4:
		if (RArm_0 != nullptr)
		{
			RArm_0->Attack();
		}
		break;
	case 5:
		if (RArm_1 != nullptr)
		{
			RArm_1->Attack();
		}
		break;
	case 6:
		if (RArm_2 != nullptr)
		{
			RArm_2->Attack();
		}
		break;
	case 7:
		if (RArm_3 != nullptr)
		{
			RArm_3->Attack();
		}
		break;
	}

	isArmAttCoolTime = true;

	GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager){isArmAttCoolTime = false; }, false);
}

void Zakum::DefUp()
{
	std::weak_ptr<GameEngineSpriteRenderer> DefUpEff = CreateComponent<GameEngineSpriteRenderer>();
	DefUpEff.lock()->SetScaleToTexture("DefUp.png");
	DefUpEff.lock()->GetTransform()->SetWorldPosition({ 15, 80, -5.0f });

	Zakum::GetZakum()->SetIsDefUp(true);

	GetLevel()->TimeEvent.AddEvent(10.0f, [DefUpEff, this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {DefUpEff.lock()->Death(); Zakum::GetZakum()->SetIsDefUp(false); }, false);
}

void Zakum::AtPowerUp()
{
	std::weak_ptr<GameEngineSpriteRenderer> AtUpEff = CreateComponent<GameEngineSpriteRenderer>();
	AtUpEff.lock()->SetScaleToTexture("AtPowerUp.png");
	AtUpEff.lock()->GetTransform()->SetWorldPosition({ 0, 80, -5.0f });
	Zakum::GetZakum()->SetIsAtPowerUp(true);

	GetLevel()->TimeEvent.AddEvent(10.0f, [AtUpEff, this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {AtUpEff.lock()->Death(); Zakum::GetZakum()->SetIsAtPowerUp(false); }, false);
}

void Zakum::BodyAttack()
{
	bool a = isAttack;

	if (isBodyAttCoolTime == true)
	{
		return;
	}

	if (isHit == true)
	{
		return;
	}


	int Num = GameEngineRandom::MainRandom.RandomInt(0, 6);
	std::string AttackName = "";

	switch (Num)
	{
	case 0:
		AttackName = "Phase" + std::to_string(CurPhase) + "_1Attack";
		BodyRender->ChangeAnimation(AttackName);
		GameEngineSound::Play("ZakumAttack1.mp3");
		break;
	case 1:
		AttackName = "Phase" + std::to_string(CurPhase) + "_2Attack";
		BodyRender->ChangeAnimation(AttackName);
		GameEngineSound::Play("ZakumAttack2.mp3");
		break;
	case 2:
		AttackName = "Phase" + std::to_string(CurPhase) + "_3Attack";
		BodyRender->ChangeAnimation(AttackName);
		GameEngineSound::Play("ZakumAttack3.mp3");
		break;
	case 3:
		BlackOut();
		break;
	case 4:
		if (isBodyDefUp == false)
		{
			AttackName = "Phase" + std::to_string(CurPhase) + "_1Skill";
			BodyRender->ChangeAnimation(AttackName);
			GameEngineSound::Play("ZakumSKill1.mp3");
		}
		break;
	case 5:
		AttackName = "Phase" + std::to_string(CurPhase) + "_2Skill";
		BodyRender->ChangeAnimation(AttackName);
		GameEngineSound::Play("ZakumSKill2.mp3");
		break;
	case 6:
		AttackName = "Phase" + std::to_string(CurPhase) + "_3Skill";
		BodyRender->ChangeAnimation(AttackName);
		GameEngineSound::Play("ZakumSKill3.mp3");
		break;
	}

}

void Zakum::FunctionUpdate()
{
	if (UpdateFuncList.size() <= 0)
	{
		return;
	}

	std::list<std::function<bool()>>::iterator Start =  UpdateFuncList.begin();
	std::list<std::function<bool()>>::iterator End =  UpdateFuncList.end();

	for (; Start != End;)
	{
		if ((*Start)() == true)
		{
			Start = UpdateFuncList.erase(Start);
			continue;
		}

		Start++;
	}
}

void Zakum::BlackOut()
{
	if (isBlackOut == true)
	{
		return;
	}

	isBlackOut = true;

	std::weak_ptr<ContentUIRenderer> BlackOut = CreateComponent<ContentUIRenderer>();
	float* Counting = new float();
	*Counting = 0;

	UpdateFuncList.push_back([BlackOut, Counting, this]
		{
			float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();

			BlackOut.lock()->SetTexture("MouseTest.png");
			BlackOut.lock()->GetTransform()->SetWorldScale({ 800, 600 });
			BlackOut.lock()->GetTransform()->SetWorldPosition({ 0, 0, 1.0f });

			float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

			float4 PlayerPixelPos = { 400 + PlayerPos.x - CameraPos.x, 300 + CameraPos.y - PlayerPos.y };
			BlackOut.lock()->SetCircleMulColor({ PlayerPixelPos.x, PlayerPixelPos.y - 30.0f , 40.0f, 0.0f });

			*Counting += TimeCount;

			if (*Counting <= 10.0f)
			{
				return false;
			}
			else
			{
				delete Counting;
				BlackOut.lock()->Death();

				isBlackOut = false;
				return true;
			}
		});
}

void Zakum::Hit(int _Damage, bool _isRealAttack)
{
	GameEngineSound::Play("ZakumHit.mp3");

	if(isAttack == false && isHit == false)
	{
		std::string AniName = "Phase" + std::to_string(CurPhase) + "Hit";
		BodyRender->ChangeAnimation(AniName);
	}
	
	Hp -= _Damage;

	if (_isRealAttack == true)
	{
		if (Hp > 30000 && Hp <= 60000 && isAttack == false && CurPhase == 1)
		{
			BodyCollision->Off();
			BodyRender->ChangeAnimation("Phase1Die");
			GameEngineSound::Play("ZakumPhaseChange.mp3");
		}
		else if(Hp > 0 && Hp <= 30000 && isAttack == false && CurPhase == 2)
		{
			BodyCollision->Off();
			BodyRender->ChangeAnimation("Phase2Die");
			GameEngineSound::Play("ZakumPhaseChange.mp3");
		}
		else if (Hp <= 0)
		{
			BodyCollision->Off();
			BodyRender->ChangeAnimation("Phase3Die");
			GameEngineSound::Play("ZakumDeath.mp3");
		}
	}

	isHit = true;
}
