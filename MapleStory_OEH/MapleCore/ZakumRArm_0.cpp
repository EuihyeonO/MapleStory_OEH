#include "PrecompileHeader.h"
#include "ZakumRArm_0.h"
#include "Zakum.h"

ZakumRArm_0::ZakumRArm_0()
{
	ArmIndex = 0;
	isLeft = false;
}

ZakumRArm_0::~ZakumRArm_0()
{
}

void ZakumRArm_0::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Hit").GetFullPath());
	}

	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm0_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm0_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 140, 125, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm0_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 160, 145, -4.0f });
			ArmCollision->Off();
		});

	
	ArmRender->ChangeAnimation("Stand");

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 100 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, 10 });
}

void ZakumRArm_0::Update(float _DeltaTime) 
{

}

void ZakumRArm_0::Render(float _DeltaTime) 
{

}
