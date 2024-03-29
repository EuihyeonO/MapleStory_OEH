#include "PrecompileHeader.h"
#include "UIWindowManager.h"
#include "StatusWindow.h"
#include "SkillWindow.h"
#include "EquipWindow.h"
#include "InventoryWindow.h"
#include "UIController.h"
#include "EquipItemList.h"
#include "CheatNPCWindow.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

extern int a;

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
		GameEngineInput::CreateKey("InventoryWindowOpen", 'I');
		GameEngineInput::CreateKey("EquipWindowOpen", 'E');
		GameEngineInput::CreateKey("Cheat", 'T');
	}
}

void UIWindowManager::UIOnOff()
{
	if (GameEngineInput::IsDown("Cheat") == true)
	{
		if (MyCheatNPC == nullptr)
		{
			MyCheatNPC = GetLevel()->CreateActor<CheatNPCWindow>();
		}
		else
		{
			MyCheatNPC->WindowDeath();
			MyCheatNPC->Death();
			MyCheatNPC = nullptr;
		}
	}

	if (GameEngineInput::IsDown("StatWindowOpen") == true)
	{
		if (MyStatusWindow == nullptr)
		{
			MyStatusWindow = GetLevel()->CreateActor<StatusWindow>();
		}
		else
		{
			MyStatusWindow->ButtonDeath();
			MyStatusWindow->Death();
			MyStatusWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("SkillWindowOpen") == true)
	{
		if (MySKillWindow == nullptr)
		{
			MySKillWindow = GetLevel()->CreateActor<SkillWindow>();
		}
		else
		{
			MySKillWindow->SkillListDeath();
			MySKillWindow->Death();
			MySKillWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("InventoryWindowOpen") == true)
	{
		if (MyInventoryWindow == nullptr)
		{
			MyInventoryWindow = GetLevel()->CreateActor<InventoryWindow>();
			UIController::GetUIController()->SetCurItemList(MyInventoryWindow->GetInventory());
		}
		else
		{
			MyInventoryWindow->ClearInventory();
			MyInventoryWindow->GetInventory()->Death();

			UIController::GetUIController()->SetCurInventoryWindow(nullptr);
			UIController::GetUIController()->SetCurItemList(nullptr);

			MyInventoryWindow->Death();
			MyInventoryWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("EquipWindowOpen") == true)
	{
		if (MyEquipWindow == nullptr)
		{
			MyEquipWindow = GetLevel()->CreateActor<EquipWindow>();
			UIController::GetUIController()->SetCurEquipItemList(MyEquipWindow->GetEquipItemList());
		}
		else
		{
			MyEquipWindow->GetEquipItemList()->ClearEquipItem();
			MyEquipWindow->GetEquipItemList()->Death();

			UIController::GetUIController()->SetCurEquipItemList(nullptr);
			MyEquipWindow->Death();
			MyEquipWindow = nullptr;
		}
	}
}

void UIWindowManager::AllWindowDeath()
{
	if(MyStatusWindow != nullptr)
	{
		MyStatusWindow->ButtonDeath();
		MyStatusWindow->Death();
		MyStatusWindow = nullptr;
	}

	if (MySKillWindow != nullptr)
	{
		MySKillWindow->SkillListDeath();
		MySKillWindow->Death();
		MySKillWindow = nullptr;
	}

	if(MyInventoryWindow != nullptr)
	{
		MyInventoryWindow->ClearInventory();
		MyInventoryWindow->GetInventory()->Death();

		UIController::GetUIController()->SetCurInventoryWindow(nullptr);
		UIController::GetUIController()->SetCurItemList(nullptr);

		MyInventoryWindow->Death();
		MyInventoryWindow = nullptr;
	}

	if (MyEquipWindow != nullptr)
	{
		MyEquipWindow->GetEquipItemList()->ClearEquipItem();
		MyEquipWindow->GetEquipItemList()->Death();

		UIController::GetUIController()->SetCurEquipItemList(nullptr);

		MyEquipWindow->Death();
		MyEquipWindow = nullptr;
	}
}