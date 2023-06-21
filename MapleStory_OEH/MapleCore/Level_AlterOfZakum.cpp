#include "PrecompileHeader.h"
#include "Level_AlterOfZakum.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "SkillWindow.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "PlayerValue.h"
#include "GlobalFunction.h"
#include "AlterOfZakum.h"

Level_AlterOfZakum::Level_AlterOfZakum()
{
}

Level_AlterOfZakum::~Level_AlterOfZakum()
{
}

void Level_AlterOfZakum::Start()
{
	SetName("ALTEROFZAKUM");

	CreateSprite();

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);

	Map = CreateActor<AlterOfZakum>();

	MyPlayer = CreateActor<Player>();
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<QuickSlot>();
	CreateActor<BottomBar>();
	MyUIWindowManager = CreateActor<UIWindowManager>();
	MyMouse = CreateActor<Mouse>();
	MyMouse->SetCurMouse(MyMouse);
}

void Level_AlterOfZakum::Update(float _DeltaTime)
{
}

void Level_AlterOfZakum::LevelChangeStart()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse != nullptr)
	{
		MyMouse->SetCurMouse(MyMouse);
	}

	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_BeginnersTown2")
	{
		//MyPlayer->SetLeft();
		//MyPlayer->SetMoveType("Jump");
		//MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}

	if (Map != nullptr)
	{
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);

		GlobalFunction::GetValue()->SetColMap(ColMap);
	}
}

void Level_AlterOfZakum::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_AlterOfZakum");
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
	}
}

void Level_AlterOfZakum::CreateSprite()
{
	if (nullptr == GameEngineSprite::Find("Poison"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("StatusEffect");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Poison").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SkillLock").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MoreMiss").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DamagedDouble").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CannotJump").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("BoogieMove"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Boogie");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieStand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieDeath").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum0Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum1Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum2Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Skill").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_3Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_4Skill").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Hit").GetFullPath());		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1AtObj").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj5").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_1SkEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_2SkEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_1AtEffect").GetFullPath());		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_2AtEffect").GetFullPath());
	}
}