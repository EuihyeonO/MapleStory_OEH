#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

BeginnersTown1::BeginnersTown1()
{
}

BeginnersTown1::~BeginnersTown1()
{
}

void BeginnersTown1::Start()
{
	LandScape0 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape0->SetTexture("MapBackGround0.png");
	LandScape0->GetTransform()->SetLocalScale({2000, 2000});

	Cloud = CreateComponent<GameEngineSpriteRenderer>();
	Cloud->SetScaleToTexture("MapBackGround1.png");
	float4 CloudScale = Cloud->GetTransform()->GetLocalScale();
	Cloud->GetTransform()->SetLocalPosition({ 0, 250 });
	Cloud->GetTransform()->AddLocalScale({ CloudScale.x * 2.0f, 0 });


	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("MapBackGround2.png");
	LandScape2->GetTransform()->SetLocalPosition({0, 200});

	BackGroundLayer = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundLayer->SetScaleToTexture("BeginnersTown1Layer.png");

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown1.png");
	
	Rope = CreateComponent<GameEngineSpriteRenderer>();
	Rope->SetScaleToTexture("BeginnersTown1Rope.png");

}

void BeginnersTown1::Update(float _DeltaTime)
{

	XMoveConstant += 0.03f * _DeltaTime;

	if (XMoveConstant > 3.0f)
	{
		XMoveConstant -= 3.0f;
	}

	Cloud->SetMoveConstants({ XMoveConstant, 0, 3});

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	LandScape2->GetTransform()->SetLocalPosition({ CameraPos.x * 0.5f , 200 });
}

void BeginnersTown1::Render(float _DeltaTime) 
{
}