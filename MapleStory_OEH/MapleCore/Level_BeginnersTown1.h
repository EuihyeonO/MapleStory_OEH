#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

class Level_BeginnersTown1 : public GameEngineLevel
{

public:

	Level_BeginnersTown1();
	~Level_BeginnersTown1();

	Level_BeginnersTown1(const Level_BeginnersTown1& _Other) = delete;
	Level_BeginnersTown1(Level_BeginnersTown1&& _Other) noexcept = delete;
	Level_BeginnersTown1& operator=(const Level_BeginnersTown1& _Other) = delete;
	Level_BeginnersTown1& operator=(Level_BeginnersTown1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
private:
	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class BeginnersTown1> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
};

