#include "PrecompileHeader.h"
#include "StarHitEffect.h"
#include <ctime>

StarHitEffect::StarHitEffect()
{
}

StarHitEffect::~StarHitEffect()
{
}

void StarHitEffect::Start()
{
	TimeCounting();

	EffectRender = CreateComponent<GameEngineSpriteRenderer>();	
}

void StarHitEffect::Update(float _DeltaTime)
{
	HitAnimationUpdate();
}

void StarHitEffect::Render(float _DeltaTime)
{

}

void StarHitEffect::HitAnimationUpdate()
{
	TimeCounting();

	AnimationCount += TimeCount;

	if(AnimationCount >= FrameList[AniIndex])
	{
		AniIndex++;

		if (AniIndex >= FrameList.size())
		{
			Death();
			return;
		}

		AnimationCount = 0.0f;
		std::string TextureName = SkillType + "Hit" + std::to_string(AniIndex) + ".png";
		EffectRender->SetScaleToTexture(TextureName);
	}
}


void StarHitEffect::SetFrame()
{
	if (SkillType == "LuckySeven")
	{
		FrameList.reserve(4);

		FrameList.push_back(0.1f);
		FrameList.push_back(0.1f);
		FrameList.push_back(0.1f);
		FrameList.push_back(0.1f);

		EffectRender->SetScaleToTexture("LuckySevenHit0.png");
	}
}


void StarHitEffect::TimeCounting()
{
	CurTime = clock();
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;
}