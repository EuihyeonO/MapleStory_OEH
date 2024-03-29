#include "PrecompileHeader.h"
#include "Level_Title.h"
#include "Logo.h"
#include "Player.h"
#include "Mouse.h"
#include "TitleObjects.h"
#include "MapleCore.h"
#include "UIController.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineShader.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

Level_Title::Level_Title()
{
}

Level_Title::~Level_Title()
{
}

void Level_Title::Start()
{
	GameEngineFont::Load("����");

	SetName("TITLE");

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Common");
		NewDir.Move("CommonNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("CommonSprite");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RingPortal").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LevelUP").GetFullPath());
	}


	if (nullptr == GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StatDiceRoll").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DiceStand").GetFullPath());

		NewDir.Move("ChannelScroll");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Akenia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bera").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Broa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Demetos").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kastia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Khaini").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mardia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plana").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Skania").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stierce").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Yellond").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Zenis").GetFullPath());

		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ChannelCheck").GetFullPath());
		NewDir.MoveParent();
		NewDir.Move("TitleLight");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight5").GetFullPath());
	}


	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sound");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".mp3", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, 0.0f });
	
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);

	GameLogo = CreateActor<Logo>();
	//std::shared_ptr<TitleObjects> NewTitleObjects1 = CreateActor<TitleObjects>();

	MyMouse = CreateActor<Mouse>(static_cast<int>(RenderOrder::UI));
	MyMouse->SetCurMouse(MyMouse);

	if (GameEngineInput::IsKey("CameraUp") == false)
	{
		GameEngineInput::CreateKey("CameraUp", 'W');
	}

	if (GameEngineInput::IsKey("CameraDown") == false)
	{
		GameEngineInput::CreateKey("CameraDown", 'S');
	}

	if (GameEngineInput::IsKey("LevelChange1") == false)
	{
		GameEngineInput::CreateKey("LevelChange1", '1');
		GameEngineInput::CreateKey("LevelChange2", '2');
		GameEngineInput::CreateKey("LevelChange3", '3');
		GameEngineInput::CreateKey("LevelChange4", '4');
	}
}

void Level_Title::Update(float _DeltaTime)
{
	if (GameLogo != nullptr && GameLogo->GetIsCreateObject() == true)
	{
		MapleCore::BGMPlayer = GameEngineSound::Play("Title.mp3");
		MapleCore::BGMPlayer.SetLoop(-1);
		MapleCore::BGMPlayer.SetVolume(0.3f);

		NewTitleObjects = CreateActor<TitleObjects>();
		NewTitleObjects->SetLoginBtEvent([this]{isCamUp = true;});
		NewTitleObjects->SetChannelClickFunc([this] {isCamUp = true; });
		NewTitleObjects->SetCharCreateEvent([this] {isCamUp = true; });
		NewTitleObjects->SetCharCreateOKButtonEvent([this]
			{
				std::shared_ptr<ItemInfo> NewItem1 = std::make_shared<ItemInfo>();
				NewItem1->EquipType = static_cast<int>(EquipType::Coat);
				NewItem1->ItemName = NewTitleObjects->ClothesVec[static_cast<int>(EquipType::Coat)][NewTitleObjects->CoatIndex].second;
				NewItem1->Def = 3;

				std::shared_ptr<ItemInfo> NewItem2 = std::make_shared<ItemInfo>();
				NewItem2->EquipType = static_cast<int>(EquipType::Pants);
				NewItem2->ItemName = NewTitleObjects->ClothesVec[static_cast<int>(EquipType::Pants)][NewTitleObjects->PantsIndex].second;
				NewItem2->Def = 2;

				std::shared_ptr<ItemInfo> NewItem3 = std::make_shared<ItemInfo>();
				NewItem3->EquipType = static_cast<int>(EquipType::Weapon);
				NewItem3->ItemName = "Ganier";
				NewItem3->Class = static_cast<int>(PlayerClass::Log);
				NewItem3->Att = 10;

				std::shared_ptr<ItemInfo> NewItem4 = std::make_shared<ItemInfo>();
				NewItem4->EquipType = static_cast<int>(EquipType::Shoes);
				NewItem4->ItemName = NewTitleObjects->ClothesVec[static_cast<int>(EquipType::Shoes)][NewTitleObjects->ShoesIndex].second;
				NewItem4->Def = 1;

				UIController::GetUIController()->AddToEquipItemList(NewItem1, static_cast<int>(ItemType::Equip));
				UIController::GetUIController()->AddToEquipItemList(NewItem2, static_cast<int>(ItemType::Equip));
				UIController::GetUIController()->AddToEquipItemList(NewItem3, static_cast<int>(ItemType::Equip));
				UIController::GetUIController()->AddToEquipItemList(NewItem4, static_cast<int>(ItemType::Equip));

				Player::GetCurPlayer()->GetTransform()->SetLocalPosition({ -162, 1138, -1 });
				Player::GetCurPlayer()->SetMoveType("Walk");
				NewTitleObjects->ActivateToCharSelect();

				isCamDown = true;
			});

		GameLogo->Death();
		GameLogo = nullptr;
	}

	CameraMove(_DeltaTime);
}

void Level_Title::CameraMove(float _DeltaTime)
{
	if (GameLogo != nullptr)
	{
		return;
	}

	if (GameEngineInput::IsDown("CameraUp") == true)
	{
		if (CameraIndex >= 3 || isCamDown == true)
		{
			return;
		}

		isCamUp = true;
	}

	if (GameEngineInput::IsDown("CameraDown") == true)
	{
		if (CameraIndex <= 0 || isCamDown == true)
		{
			return;
		}

		isCamDown = true;
	}

	if (isCamUp == true)
	{
		if (isPlayerCamMoveSound == false)
		{
			GameEngineSound::Play("TitleCamMove.mp3");
			isPlayerCamMoveSound = true;
		}

		DestiPos = { 0,(CameraIndex + 1) * 600.0f };
		CamPos = GetMainCamera()->GetTransform()->GetLocalPosition();

		LerpRatio += _DeltaTime * LerpSpeed;
		GetMainCamera()->GetTransform()->SetLocalPosition(LerpCamPos.LerpClamp(CamPos, DestiPos, LerpRatio));

		if (LerpRatio >= 1.0f)
		{
			isCamUp = false;
			GetMainCamera()->GetTransform()->SetLocalPosition({ 0,(CameraIndex + 1) * 600.0f });
			CameraIndex++;
			LerpRatio = 0.0f;
			isPlayerCamMoveSound = false;
		}
	}

	if (isCamDown == true)
	{
		if (isPlayerCamMoveSound == false)
		{
			GameEngineSound::Play("TitleCamMove.mp3");
			isPlayerCamMoveSound = true;
		}

		DestiPos = { 0,(CameraIndex - 1) * 600.0f };
		CamPos = GetMainCamera()->GetTransform()->GetLocalPosition();

		LerpRatio += _DeltaTime * LerpSpeed;
		GetMainCamera()->GetTransform()->SetLocalPosition(LerpCamPos.LerpClamp(CamPos, DestiPos, LerpRatio));

		if (LerpRatio >= 1.0f)
		{
			isCamDown = false;
			GetMainCamera()->GetTransform()->SetLocalPosition({ 0,(CameraIndex - 1) * 600.0f });
			CameraIndex--;
			LerpRatio = 0.0f;
			isPlayerCamMoveSound = false;
		}
	}
}

void Level_Title::LevelChangeStart()
{
	if (nullptr == GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StatDiceRoll").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DiceStand").GetFullPath());

		NewDir.Move("ChannelScroll");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Akenia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bera").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Broa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Demetos").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kastia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Khaini").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mardia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plana").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Skania").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stierce").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Yellond").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Zenis").GetFullPath());

		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ChannelCheck").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Title");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight5").GetFullPath());
	}

	MyPlayer = CreateActor<Player>();
	MyPlayer->GetTransform()->SetLocalPosition({ -20, 1768, -1 });
	MyPlayer->SetRight();
}

void Level_Title::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

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

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::UnLoad("StatDiceRoll");
		GameEngineSprite::UnLoad("DiceStand");

		NewDir.Move("ChannelScroll");

		GameEngineSprite::UnLoad("Akenia");
		GameEngineSprite::UnLoad("Bera");
		GameEngineSprite::UnLoad("Broa");
		GameEngineSprite::UnLoad("Croa");
		GameEngineSprite::UnLoad("Demetos");
		GameEngineSprite::UnLoad("Kastia");
		GameEngineSprite::UnLoad("Khaini");
		GameEngineSprite::UnLoad("Mardia");
		GameEngineSprite::UnLoad("Plana");
		GameEngineSprite::UnLoad("Skania");
		GameEngineSprite::UnLoad("Stierce");
		GameEngineSprite::UnLoad("Yellond");
		GameEngineSprite::UnLoad("Zenis");

		NewDir.MoveParent();
		GameEngineSprite::UnLoad("ChannelCheck");

		NewDir.MoveParent();
		NewDir.Move("TitleLight");

		GameEngineSprite::UnLoad("TitleLight0");
		GameEngineSprite::UnLoad("TitleLight1");
		GameEngineSprite::UnLoad("TitleLight2");
		GameEngineSprite::UnLoad("TitleLight3");
		GameEngineSprite::UnLoad("TitleLight4");
		GameEngineSprite::UnLoad("TitleLight5");
	}
	
	PlayerValue::GetValue()->SetPrevLevelName("Level_Title");
	
	MyPlayer->Death();
	NewTitleObjects->Death();
	MyMouse->Death();
}