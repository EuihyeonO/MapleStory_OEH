#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class BeginnersTown1 : public GameEngineActor
{
public:
	const std::string_view& GetColMapName()
	{
		return ColMapName;
	}

	BeginnersTown1();
	~BeginnersTown1();

	BeginnersTown1(const BeginnersTown1& _Other) = delete;
	BeginnersTown1(BeginnersTown1&& _Other) noexcept = delete;
	BeginnersTown1& operator=(const BeginnersTown1& _Other) = delete;
	BeginnersTown1& operator=(BeginnersTown1&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string ColMapName = "ColBeginnersTown1.png";

	float XMoveConstant = 0.0f;

	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Rope = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundLayer = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> LandScape0 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LandScape2 = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> Cloud = nullptr;

};
