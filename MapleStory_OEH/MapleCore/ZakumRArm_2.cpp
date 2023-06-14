#include "PrecompileHeader.h"
#include "ZakumRArm_2.h"
#include "Zakum.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

ZakumRArm_2::ZakumRArm_2()
{
	ArmIndex = 2;
	isLeft = false;
}

ZakumRArm_2::~ZakumRArm_2()
{
}

void ZakumRArm_2::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -35 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_2::Update(float _DeltaTime)
{


	DeltaTime = _DeltaTime;
}

void ZakumRArm_2::Render(float _DeltaTime)
{

}

void ZakumRArm_2::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	switch (Num)
	{
	case 0:
		ArmRender->ChangeAnimation("1Skill");
		break;
	case 1:
		ArmRender->ChangeAnimation("2Skill");
		break;

	}
}

void ZakumRArm_2::SetAnimation()
{

	//1Skill
	ArmRender->CreateAnimation({ .AnimationName = "1Skill",.SpriteName = "RArm2_1Skill",.Loop = false,.ScaleToTexture = true ,.FrameTime = {0.115f, 0.12f, 0.125f, 0.115f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.125f, 0.115f, 0.125f, 0.115f } });
	ArmRender->SetAnimationUpdateEvent("1Skill", 0, [this] {GetTransform()->SetLocalPosition({ 235, -25, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -55, -20 }); isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("1Skill", 9, [this]
		{
			//����Ʈ
		});

	ArmRender->SetAnimationUpdateEvent("1Skill", 12, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, -35 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//2Skill
	ArmRender->CreateAnimation({ .AnimationName = "2Skill",.SpriteName = "RArm2_2Skill",.Loop = false,.ScaleToTexture = true ,.FrameTime = {0.115f, 0.12f, 0.12f, 0.125f, 0.120f, 0.115f, 0.12f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.125f } });
	ArmRender->SetAnimationUpdateEvent("2Skill", 0, [this] {GetTransform()->SetLocalPosition({ 235, -25, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -55, -20 }); isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("2Skill", 9, [this]
		{
			//����Ʈ
		});

	ArmRender->SetAnimationUpdateEvent("2Skill", 12, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAtCoolTime = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, -35 });
				ArmRender->ChangeAnimation("Stand");
			}
		});
	//

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm2_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, -10, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Death
	std::vector<float> FrameVec;
	FrameVec.reserve(19);

	for (int i = 0; i < 19; i++)
	{
		FrameVec.push_back(0.11f);
	}

	FrameVec[18] = 1.0f;

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm2_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this]
		{
			ArmRender->ColorOptionValue.MulColor.a -= 4.0f * DeltaTime;

			if (ArmRender->ColorOptionValue.MulColor.a <= 0.0f)
			{
				Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);
			}
		});

	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, 10, -4.0f });
			ArmCollision->Off();
		});


	//Stand
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm2_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
		});
}