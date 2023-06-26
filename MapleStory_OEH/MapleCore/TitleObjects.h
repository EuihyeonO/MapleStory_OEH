#pragma once
#include "BasicFunction.h"
#include "ContentButton.h"

class GameEngineSpriteRenderer;

class TitleObjects : public BasicFunction
{

public:

	TitleObjects();
	~TitleObjects();

	TitleObjects(const TitleObjects& _Other) = delete;
	TitleObjects(TitleObjects&& _Other) noexcept = delete;
	TitleObjects& operator=(const TitleObjects& _Other) = delete;
	TitleObjects& operator=(TitleObjects&& _Other) noexcept = delete;

	void SetLoginBtEvent(std::function<void()> _Event)
	{
		LoginBt->SetEvent(_Event);
	}

	void SetChannelClickFunc(std::function<void()> _Event)
	{
		ChannelClickFunc = _Event;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Create_LoginBox();
	void Create_ChannelButton();
	void Create_FrameObject();
	void Create_CharSelectButton();
	void Create_CharacterObject();
	void Create_CharCreateObject();
	void EmptySlotAnimation();

	void SetChScroll();

	void RollStatDice();
	void StatChange();

	std::shared_ptr<class GameEngineUIRenderer> Frame;
	std::shared_ptr<GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<GameEngineSpriteRenderer> Logo;
	float LogoAlphaAngle = 45.0f;

	std::shared_ptr<GameEngineSpriteRenderer> TitleLight0;
	std::shared_ptr<GameEngineSpriteRenderer> TitleLight1;
	std::shared_ptr<GameEngineSpriteRenderer> TitleLight2;
	std::shared_ptr<GameEngineSpriteRenderer> TitleLight3;
	std::shared_ptr<GameEngineSpriteRenderer> TitleLight4;
	std::shared_ptr<GameEngineSpriteRenderer> TitleLight5;

	float TitleLightAlphaAngle0 = 30.0f;
	float TitleLightAlphaAngle1 = 60.0f;
	float TitleLightAlphaAngle2 = 90.0f;
	float TitleLightAlphaAngle3 = 120.0f;
	float TitleLightAlphaAngle4 = 150.0f;
	float TitleLightAlphaAngle5 = 0.0f;

	void LoginObjectAlphaUpdate(float _DeltaTime);

	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectLope;
	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectFixture;

	std::shared_ptr<GameEngineSpriteRenderer> ChScroll;

	//로그인창
	std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;
	std::shared_ptr<class GameEngineButton> SignUp;
	std::shared_ptr<class ContentButton> LoginBt;
	std::shared_ptr<class GameEngineButton> HomePage;
	std::shared_ptr<class GameEngineButton> Exit;
	std::shared_ptr<GameEngineSpriteRenderer> SaveEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindPass;
	std::shared_ptr<GameEngineSpriteRenderer> Check;

	//채널
	std::shared_ptr<class ContentButton> Demetos;
	std::shared_ptr<class ContentButton> Bellokan;
	std::shared_ptr<class ContentButton> Bera;
	std::shared_ptr<class ContentButton> Broa;
	std::shared_ptr<class ContentButton> Mardia;
	std::shared_ptr<class ContentButton> Skania;
	std::shared_ptr<class ContentButton> Stierce;
	std::shared_ptr<class ContentButton> Akenia;
	std::shared_ptr<class ContentButton> Zenis;
	std::shared_ptr<class ContentButton> Kastia;
	std::shared_ptr<class ContentButton> Kiny;
	std::shared_ptr<class ContentButton> Croa;
	std::shared_ptr<class ContentButton> Yellond;
	std::shared_ptr<class ContentButton> Plana;

	//캐릭터선택창
	std::shared_ptr<GameEngineSpriteRenderer> CharSelectBox;
	std::shared_ptr<GameEngineSpriteRenderer> CharCreate;
	std::shared_ptr<GameEngineSpriteRenderer> CharSelect;
	std::shared_ptr<GameEngineSpriteRenderer> CharDelete;

	//캐릭터 관련 오브젝트
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot1;
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot2;
	std::shared_ptr<GameEngineSpriteRenderer> EmptySlot3;

	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation1;
	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation2;
	std::shared_ptr<GameEngineSpriteRenderer> EmptyAnimation3;
	
	//캐릭터 생성창 오브젝트
	std::shared_ptr<GameEngineSpriteRenderer> CharInfo;
	std::shared_ptr<GameEngineSpriteRenderer> InfoScroll;
	std::shared_ptr<GameEngineSpriteRenderer> InfoScrollLayer;
	std::shared_ptr<class GameEngineSpriteRenderer> Dice;
	std::shared_ptr<class GameEngineCollision> DiceCol;
	std::shared_ptr<GameEngineSpriteRenderer> OkButton;
	std::shared_ptr<GameEngineSpriteRenderer> NoButton;

	//프레임에 달려있는 버튼
	std::shared_ptr<GameEngineSpriteRenderer> ToLogin;
	std::shared_ptr<GameEngineSpriteRenderer> SelectedWorld;
	std::shared_ptr<GameEngineSpriteRenderer> SelectWorldStage;
	std::shared_ptr<GameEngineSpriteRenderer> SelectCharStage;
	std::shared_ptr<GameEngineSpriteRenderer> CreateCharStage;

	float EmptyAniTimeCount = 0.0f;
	int EmptyAniIndex = 0;
	int ScrollIndex = 0;

	std::shared_ptr<class GameEngineFontRenderer> StrRender;
	std::shared_ptr<class GameEngineFontRenderer> DexRender;
	std::shared_ptr<class GameEngineFontRenderer> IntRender;
	std::shared_ptr<class GameEngineFontRenderer> LukRender;

	float Counting = 0.0f;

	bool isChScrollOpen = false;
	
	std::vector<std::shared_ptr<class GameEngineCollision>> ChColVec;
	void SetChCollision();

	void AllChColOn();
	void AllChColOff();

	std::shared_ptr<GameEngineSpriteRenderer> ChannelCheck = nullptr;
	std::shared_ptr<GameEngineCollision> SelectedChannel = nullptr;
	void ChannelChecking();
	std::function<void()> ChannelClickFunc = nullptr;
};

