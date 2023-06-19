#pragma once
#include "ZakumBasicFunction.h"
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>

class Zakum : public ZakumBasicFunction
{
	friend class ZakumLArm_0;
	friend class ZakumLArm_1;
	friend class ZakumLArm_2;
	friend class ZakumLArm_3;
	friend class ZakumRArm_0;
	friend class ZakumRArm_1;
	friend class ZakumRArm_2;
	friend class ZakumRArm_3;

public:

	Zakum();
	~Zakum();

	Zakum(const Zakum& _Other) = delete;
	Zakum(Zakum&& _Other) noexcept = delete;
	Zakum& operator=(const Zakum& _Other) = delete;
	Zakum& operator=(Zakum&& _Other) noexcept = delete;
	
	void Hit(int _Damage, bool _isRealAttack) override {}
	
	bool GetIsAtPowerUp()
	{
		return isAtPowerUp;
	}

	bool GetIsDefUp()
	{
		return isDefUp;
	}

	void SetIsAtPowerUp(bool _Bool)
	{
		isAtPowerUp = _Bool;
	}

	void SetIsDefUp(bool _Bool)
	{
		isDefUp = _Bool;
	}

	int GetAtt()
	{
		return Att;
	}

	static std::shared_ptr<Zakum> GetZakum()
	{
		return GlobalZakum;
	}

	void SubHp(int _Damage)
	{
		Hp -= _Damage;
	}

	void SubArmCount()
	{
		ArmCount--;
	}

	void BodyStart()
	{
		if (ArmCount <= 0)
		{
			GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {BodyAttackStart = true;});
		}
	}

	void AtPowerUp();
	void DefUp();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ArmDeath(bool _isLeft, int _ArmIndex);
	
	std::function<void()> UpdateFunc = nullptr;

	void Spawn(float _DeltaTime) {}
	void MonsterDeath(float _DeltaTime) {}
	void CreateArm(bool _isLeft, int _ArmIndex);

	void SetAttack();

	void SetAnimation();
	void ArmAttack();
	void BodyAttack();
	
	void Attack() override;

	static std::shared_ptr<Zakum> GlobalZakum;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyRender = nullptr;
	std::string AnimationName = "";

	std::shared_ptr<class ZakumRArm_0> RArm_0 = nullptr;
	std::shared_ptr<class ZakumRArm_1> RArm_1 = nullptr;
	std::shared_ptr<class ZakumRArm_2> RArm_2 = nullptr;
	std::shared_ptr<class ZakumRArm_3> RArm_3 = nullptr;

	std::shared_ptr<class ZakumLArm_0> LArm_0 = nullptr;
	std::shared_ptr<class ZakumLArm_1> LArm_1 = nullptr;
	std::shared_ptr<class ZakumLArm_2> LArm_2 = nullptr;
	std::shared_ptr<class ZakumLArm_3> LArm_3 = nullptr;

	bool isArmAttCoolTime = false;
	bool isBodyAttCoolTime = false;

	int AniIndex = 0;
	float AniCount = 0;
	
	int CurPhase = 1;

	bool isAtPowerUp = false;
	bool isDefUp = false;

	bool BodyAttackStart = false;
	
	int ArmCount = 8;

	bool isArm = false;
	int Hp = 3000;

	std::shared_ptr<class ContentRenderer> BlackOut = nullptr;
};

