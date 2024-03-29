#include "PrecompileHeader.h"
#include "Level_SouthFerry.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "GlobalFunction.h"
#include "SouthFerry.h"
#include "MapleCore.h"
#include "UIController.h"

#include <GameEnginePlatform/GameEngineSound.h>

Level_SouthFerry::Level_SouthFerry()
{
}

Level_SouthFerry::~Level_SouthFerry()
{
}

void Level_SouthFerry::Start()
{
	SetName("SOUTHFERRY");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_SouthFerry::Update(float _DeltaTime)
{

}

void Level_SouthFerry::LevelChangeStart()
{
	MapleCore::BGMPlayer.Stop();
	MapleCore::BGMPlayer = GameEngineSound::Play("SouthFerry.mp3");
	LoadResources();
	ActorCreate();
}

void Level_SouthFerry::LevelChangeEnd()
{
	PlayerValue::GetValue()->SetPrevLevelName("Level_SouthFerry");

	ActorDeath();
	UnLoadResources();
}

void Level_SouthFerry::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<SouthFerry>();
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);
		GlobalFunction::GetValue()->SetColMap(ColMap);
	}

	if (MyPlayer == nullptr)
	{
		MyPlayer = CreateActor<Player>();
		MyPlayer->SetCurPlayer(MyPlayer);
		MyPlayer->SetColMap(Map->GetColMapName());
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse == nullptr)
	{
		MyMouse = CreateActor<Mouse>();
		MyMouse->SetCurMouse(MyMouse);
	}

	if (MyQuickSlot == nullptr)
	{
		MyQuickSlot = CreateActor<QuickSlot>();
	}

	if (MyBottomBar == nullptr)
	{
		MyBottomBar = CreateActor<BottomBar>();
	}

	if (MyUIWindowManager == nullptr)
	{
		MyUIWindowManager = CreateActor<UIWindowManager>();
	}


	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_CrossRoad")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -2250, -430 });
	}

}

void Level_SouthFerry::ActorDeath()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->Death();
		MyPlayer = nullptr;
	}

	if (MyMouse != nullptr)
	{
		MyMouse->Death();
		MyMouse = nullptr;
	}

	if (MyQuickSlot != nullptr)
	{
		MyQuickSlot = nullptr;
	}

	if (MyBottomBar != nullptr)
	{
		MyBottomBar = nullptr;
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
		MyUIWindowManager->Death();
		MyUIWindowManager = nullptr;
	}

	if (Map != nullptr)
	{
		Map->Death();
		Map = nullptr;
	}
}

void Level_SouthFerry::LoadResources()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("MapleResources");
	NewDir.Move("MapleResources");
	NewDir.Move("SouthFerry");
	NewDir.Move("SouthFerryNotSprite");

	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

	for (size_t i = 0; i < File.size(); i++)
	{
		std::string FileFullPath = File[i].GetFullPath();
		std::string FileName = "";
		size_t Count = 0;

		for (Count = FileFullPath.size(); Count > 0; Count--)
		{
			char a = FileFullPath[Count];
			if (FileFullPath[Count] == '\\')
			{
				break;
			}
		}

		for (size_t j = Count + 1; j < FileFullPath.size(); j++)
		{
			FileName.push_back(FileFullPath[j]);
		}

		if (GameEngineTexture::Find(FileName) != nullptr)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
		else
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

void Level_SouthFerry::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("SouthFerry.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("SouthFerry");
		NewDir.Move("SouthFerryNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{

			std::string FileFullPath = File[i].GetFullPath();
			std::string FileName = "";
			size_t Count = 0;

			for (Count = FileFullPath.size(); Count > 0; Count--)
			{
				char a = FileFullPath[Count];
				if (FileFullPath[Count] == '\\')
				{
					break;
				}
			}

			for (size_t j = Count + 1; j < FileFullPath.size(); j++)
			{
				FileName.push_back(FileFullPath[j]);
			}

			GameEngineTexture::UnLoad(FileName);
		}
	}
}

