#include "PrecompileHeader.h"
#include "ZakumRArm_3.h"
#include "Zakum.h"

ZakumRArm_3::ZakumRArm_3()
{
	ArmIndex = 3;
	isLeft = false;
}

ZakumRArm_3::~ZakumRArm_3()
{
}


void ZakumRArm_3::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();
	
	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -40 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_3::Update(float _DeltaTime)
{

}

void ZakumRArm_3::Render(float _DeltaTime)
{

}


void ZakumRArm_3::SetAnimation()
{




	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm3_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 180, -80, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm3_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, -70, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm3_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, -90, -4.0f });
			ArmCollision->Off();
		});
}

