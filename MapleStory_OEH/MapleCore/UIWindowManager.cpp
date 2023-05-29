#include "PrecompileHeader.h"
#include "UIWindowManager.h"
#include "StatusWindow.h"
#include "SkillWindow.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

UIWindowManager::UIWindowManager()
{
}

UIWindowManager::~UIWindowManager()
{
}

void UIWindowManager::Start()
{
	CreateUIKey();
}

void UIWindowManager::Update(float _DeltaTime) 
{
	UIOnOff();
}

void UIWindowManager::Render(float _DeltaTime) 
{
}

void UIWindowManager::CreateUIKey()
{
	if (GameEngineInput::IsKey("StatWindowOpen") == false)
	{
		GameEngineInput::CreateKey("StatWindowOpen", 'S');
		GameEngineInput::CreateKey("SkillWindowOpen", 'K');
	}
}

void UIWindowManager::UIOnOff()
{
	if (GameEngineInput::IsDown("StatWindowOpen") == true)
	{
		if (MyStatusWindow == nullptr)
		{
			MyStatusWindow = GetLevel()->CreateActor<StatusWindow>(static_cast<int>(RenderOrder::UI));
		}
		else
		{
			MyStatusWindow->Death();
			MyStatusWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("SkillWindowOpen") == true)
	{
		if (MySKillWindow == nullptr)
		{
			MySKillWindow = GetLevel()->CreateActor<SkillWindow>(static_cast<int>(RenderOrder::UI));
		}
		else
		{
			MySKillWindow->SkillListDeath();
			MySKillWindow->Death();
			MySKillWindow = nullptr;
		}
	}

}