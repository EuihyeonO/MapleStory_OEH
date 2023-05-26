#include "PrecompileHeader.h"
#include "Level_BeginnersTown1.h"
#include "BeginnersTown1.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"

#include <GameEngineCore/GameEngineCamera.h>

Level_BeginnersTown1::Level_BeginnersTown1()
{

}

Level_BeginnersTown1::~Level_BeginnersTown1()
{
	
}

void Level_BeginnersTown1::LevelChangeStart()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->SetCurPlayer(MyPlayer);
	}
}

void Level_BeginnersTown1::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	Map = CreateActor<BeginnersTown1>();

	MyPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::Player));
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);


	CreateActor<BottomBar>(static_cast<int>(RenderOrder::UI));
	CreateActor<StatusWindow>(static_cast<int>(RenderOrder::UI));
	CreateActor<Mouse>(static_cast<int>(RenderOrder::UI));
}

void Level_BeginnersTown1::Update(float _DeltaTime)
{

}