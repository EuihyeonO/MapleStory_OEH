#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <ctime>


void Player::SetAllTexturePosVector()
{
	//Frame
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);

	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);

	AniFrameList["Swing0"].push_back(0.3f);
	AniFrameList["Swing0"].push_back(0.15f);
	AniFrameList["Swing0"].push_back(0.35f);

	AniFrameList["Swing1"].push_back(0.3f);
	AniFrameList["Swing1"].push_back(0.15f);
	AniFrameList["Swing1"].push_back(0.35f);

	AniFrameList["Swing2"].push_back(0.3f);
	AniFrameList["Swing2"].push_back(0.15f);
	AniFrameList["Swing2"].push_back(0.35f);

	AniFrameList["Jump"].push_back(0.0f);

	//Origin�� X���� Y�״��
	SetBodyTexturePosVector();
	//Coat
	SetCoatTexturePosVector();
	//Pants	
	SetPantsTexturePosVector();
	//Weapon
	SetWeaponTexturePosVector();
	//HairAndFace
	SetHairAndFaceTexturePosVector();
}

void Player::SetBodyTexturePosVector()
{
	//Body
	BodyOriginPos["Stand"].push_back({ -16, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Stand"].push_back({ -18, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -16, 32 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -21, 31 });
	BodyOriginPos["Swing0"].push_back({ -11, 27 });
	BodyOriginPos["Swing0"].push_back({ -11, 31 });
	BodyOriginPos["Swing0"].push_back({ -38, 27 });
	BodyOriginPos["Swing1"].push_back({ -18, 31 });
	BodyOriginPos["Swing1"].push_back({ -21, 31 });
	BodyOriginPos["Swing1"].push_back({ -30, 29 });
	BodyOriginPos["Swing2"].push_back({ -36, 27 });
	BodyOriginPos["Swing2"].push_back({ -28, 30 });
	BodyOriginPos["Swing2"].push_back({ -36, 27 });
	
	BodyOriginPos["Jump"].push_back({ -22, 30 });


	//x�� �״��, y�� ���� 
	BodyNavelPos["Stand"].push_back({ -8, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Stand"].push_back({ -6, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 18 });
	BodyNavelPos["Swing0"].push_back({ -1, 16 });
	BodyNavelPos["Swing0"].push_back({ -8, 20 });
	BodyNavelPos["Swing0"].push_back({ -29, 17 });
	BodyNavelPos["Swing1"].push_back({ -6, 20 });
	BodyNavelPos["Swing1"].push_back({ -8, 18 });
	BodyNavelPos["Swing1"].push_back({ -11, 16 });
	BodyNavelPos["Swing2"].push_back({ -8, 16 });
	BodyNavelPos["Swing2"].push_back({ -24, 17 });
	BodyNavelPos["Swing2"].push_back({ -30, 16 });
	BodyNavelPos["Jump"].push_back({ -5, 18 });
	//
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Swing0"].push_back({ -9, 26 });
	BodyNeckPos["Swing0"].push_back({ -10, 31 });
	BodyNeckPos["Swing0"].push_back({ -37, 25 });
	BodyNeckPos["Swing1"].push_back({ -4, 32 });
	BodyNeckPos["Swing1"].push_back({ -13, 30 });
	BodyNeckPos["Swing1"].push_back({ -17, 27 });
	BodyNeckPos["Swing2"].push_back({ -11, 27 });
	BodyNeckPos["Swing2"].push_back({ -31, 28 });
	BodyNeckPos["Swing2"].push_back({ -34, 26 });
	BodyNeckPos["Jump"].push_back({ -4, 30 });

	//Arm

	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -6, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 8 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -6, 7 });
	ArmOriginPos["Swing1"].push_back({ -11, 7 });
	ArmOriginPos["Swing1"].push_back({ -12, 6 });
	ArmOriginPos["Swing1"].push_back({ -10, 8 });
	ArmOriginPos["Swing2"].push_back({ -11, 7 });
	ArmOriginPos["Swing2"].push_back({ -12, 6 });
	ArmOriginPos["Swing2"].push_back({ -10, 8 });
	ArmOriginPos["Jump"].push_back({ -7,7 });

	//X ����, Y�״��
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 6, -1 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 13, 4 });
	ArmToNavelPos["Swing0"].push_back({ -5, 2 });
	ArmToNavelPos["Swing0"].push_back({ -5, 4 });
	ArmToNavelPos["Swing0"].push_back({ 8, 18 });
	ArmToNavelPos["Swing1"].push_back({ -11, 12 });
	ArmToNavelPos["Swing1"].push_back({ -13, 9 });
	ArmToNavelPos["Swing1"].push_back({ 14, 3 });

	ArmToNavelPos["Swing2"].push_back({ 14, 10 });
	ArmToNavelPos["Swing2"].push_back({ -11, 5 });
	ArmToNavelPos["Swing2"].push_back({ 2, 1 });

	ArmToNavelPos["Jump"].push_back({ 7, 5 });

	//Y�� ����
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });

	ArmHandPos["Walk"].push_back({ 1, -5 });
	ArmHandPos["Walk"].push_back({ -2, -5 });
	ArmHandPos["Walk"].push_back({ 1, -6 });
	ArmHandPos["Walk"].push_back({ 3, -5 });

	ArmHandPos["Swing0"].push_back({ 0, -2 });
	ArmHandPos["Swing0"].push_back({ -3, -5 });
	ArmHandPos["Swing0"].push_back({ 11, 1 });

	ArmHandPos["Swing1"].push_back({ -6, 4 });
	ArmHandPos["Swing1"].push_back({ -8, -8 });
	ArmHandPos["Swing1"].push_back({ 5, -4 });

	ArmHandPos["Swing2"].push_back({ 6, 3 });
	ArmHandPos["Swing2"].push_back({ -9, -2 });
	ArmHandPos["Swing2"].push_back({ -9, 0 });

	ArmHandPos["Jump"].push_back({ -3, 3 });
	
	//
	HeadOriginPos["Front"] = float4{ -19, 17 };

	HeadToNeckPos["Front"] = float4{ 0, 15 };
	//x,y �Ѵٹ���
	HeadBrowPos["Front"] = float4{ -4, 5 };
}

void Player::SetCoatTexturePosVector()
{
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });

	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -11, 9 });
	
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Jump"]["WhiteTshirt"].push_back({ -10, 10 });

	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 8, 1 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 6, 2 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 5, 1 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 6, 2 });

	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 4 });

	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 5, 2 });
	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 7, 1 });
	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 6, 1 });

	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 5, 1 });
	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 4, 3 });
	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 4, 3 });

	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 0, 1 });
	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 9, 2 });

	CoatToNavelPos["Jump"]["WhiteTshirt"].push_back({ 4, 2 });

	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });

	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 2 });

	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -3, 5 });
	
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -3, 5 });

	CoatArmOriginPos["Jump"]["WhiteTshirt"].push_back({ -4, 4 });

	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 12, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });

	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 9, 3 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 9 });

	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ -5, 4 });
	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ -1, 6 });
	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 5, 8 });
	
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ -2, 6 });
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ -6, 5 });
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 7, 6 });
	
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 7, 6 });
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ -4, 6 });
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ -1, 4 });

	CoatArmToNavelPos["Jump"]["WhiteTshirt"].push_back({ 13, 5 });

}

void Player::SetPantsTexturePosVector()
{
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Swing0"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Swing0"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing0"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Swing1"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Swing1"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing1"]["BluePants"].push_back({ -9, 6 });
	
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Jump"]["BluePants"].push_back({ -10, 5 });

	//X�� ����
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 5, -6 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 4, -5 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 3, -6 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 4, -5 });

	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 3, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -5 });

	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 2, -3 });
	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 8, -3 });
	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 2, -3 });

	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 4, -4 });
	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 2, -3 });
	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 2, -3 });

	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 3, -4 });
	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 8, -2 });
	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 6, -3 });

	PantsToNavelPos["Jump"]["BluePants"].push_back({ 2, -5 });

}

void Player::SetWeaponTexturePosVector()
{
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Jump"]["BasicSword"].push_back({ -13, 5 });

	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });

	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });

	//X�� ����
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -2 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -6, 6 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -2 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -1 });

	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, 0 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -1 });

	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7,  6 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -2 });

	//
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ 4, 1 });
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ -4, -2 });
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ 23, 41 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ -11, 34 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ -14, 35 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ 26, 1 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ 26, 33 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ -39, 2 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ 5, 1 });

	WeaponToNavelPos["Jump"]["BasicSword"].push_back({ 11, 27 });

}

void Player::SetHairAndFaceTexturePosVector()
{
	HairOriginPos["Toven"]["Front"] = float4{ -24, 15 };
	//x,y �Ѵٹ���
	HairToBrowPos["Toven"]["Front"] = float4{ 9, -1 };

	//Face

	FaceOriginPos["Face1"]["Default"] = float4{ -13, 8 };
	//x,y �Ѵٹ���
	FaceToBrowPos["Face1"]["Default"] = float4{ 1, -12 };
}

void Player::TextureUpdate()
{
	std::string BodyTexture = SkinType + "Body" + MoveType + std::to_string(AniIndex) + ".png";
	std::string ArmTexture = SkinType + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
	std::string HeadTexture = SkinType + "Head" + "Front" + ".png";
	std::string HairTexture = HairName + FrontBackDir + HairStatus + ".png";
	std::string FaceTexture = FaceName + Expression + ".png";

	std::string CoatTexture = CoatName + MoveType + std::to_string(AniIndex) + ".png";
	std::string CoatArmTexture = CoatName + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
	std::string PantsTexture = PantsName + MoveType + std::to_string(AniIndex) + ".png";

	std::string WeaponTexture = WeaponName + MoveType + std::to_string(AniIndex) + ".png";

	Body->SetScaleToTexture(BodyTexture);
	Arm->SetScaleToTexture(ArmTexture);
	Head->SetScaleToTexture(HeadTexture);
	Hair->SetScaleToTexture(HairTexture);
	Face->SetScaleToTexture(FaceTexture);
	Coat->SetScaleToTexture(CoatTexture);
	CoatArm->SetScaleToTexture(CoatArmTexture);
	Pants->SetScaleToTexture(PantsTexture);
	Weapon->SetScaleToTexture(WeaponTexture);
}


void Player::TextureAnimationUpdate()
{
	if (MoveType == "Jump")
	{
		AniIndex = 0;
		return;
	}

	AnimationCount += TimeCount;

	if (AnimationCount >= AniFrameList[MoveType][AniIndex])
	{
		AniIndex++;

		if (isSwing == true && AniIndex == 3)
		{
			isSwing = false;
			MoveType = "Stand";
			AniIndex = 0;
			AnimationCount = 0.0f;
			return;
		}

		if (AniIndex >= AniFrameList[MoveType].size())
		{
			AniIndex = 0;
		}		

		AnimationCount = 0.0f;
	}
}

void Player::TexturePosUpdate()
{

	float4 BodyScale = Body->GetTransform()->GetLocalScale();
	Body->GetTransform()->SetLocalPosition({ BodyScale.hx(), -BodyScale.hy() });
	//Origin
	Body->GetTransform()->AddLocalPosition(BodyOriginPos[MoveType][AniIndex]);

	float4 ArmScale = Arm->GetTransform()->GetLocalScale();
	Arm->GetTransform()->SetLocalPosition({ ArmScale.hx(), -ArmScale.hy() });
	Arm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + ArmToNavelPos[MoveType][AniIndex] + ArmOriginPos[MoveType][AniIndex]);

	float4 HeadScale = Head->GetTransform()->GetLocalScale();
	Head->GetTransform()->SetLocalPosition({ HeadScale.hx(), -HeadScale.hy() });
	Head->GetTransform()->AddLocalPosition(BodyNeckPos[MoveType][AniIndex] + HeadToNeckPos[FrontBackDir] + HeadOriginPos[FrontBackDir]);

	float4 HeadPos = Head->GetTransform()->GetLocalPosition();
	float4 BrowPos = HeadPos + HeadBrowPos[FrontBackDir];

	float4 HairScale = Hair->GetTransform()->GetLocalScale();
	Hair->GetTransform()->SetLocalPosition({ HairScale.hx(), -HairScale.hy() });
	Hair->GetTransform()->AddLocalPosition(BrowPos + HairToBrowPos[HairName][FrontBackDir] + HairOriginPos[HairName][FrontBackDir]);

	float4 FaceScale = Face->GetTransform()->GetLocalScale();
	Face->GetTransform()->SetLocalPosition({ FaceScale.hx(), -FaceScale.hy() });
	Face->GetTransform()->AddLocalPosition(BrowPos + FaceToBrowPos[FaceName][Expression] + FaceOriginPos[FaceName][Expression]);

	float4 CoatScale = Coat->GetTransform()->GetLocalScale();
	Coat->GetTransform()->SetLocalPosition({ CoatScale.hx(), -CoatScale.hy() });
	Coat->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatToNavelPos[MoveType][CoatName][AniIndex] + CoatOriginPos[MoveType][CoatName][AniIndex]);

	float4 CoatArmScale = CoatArm->GetTransform()->GetLocalScale();
	CoatArm->GetTransform()->SetLocalPosition({ CoatArmScale.hx(), -CoatArmScale.hy() });
	CoatArm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatArmToNavelPos[MoveType][CoatName][AniIndex] + CoatArmOriginPos[MoveType][CoatName][AniIndex]);

	float4 PantsScale = Pants->GetTransform()->GetLocalScale();
	Pants->GetTransform()->SetLocalPosition({ PantsScale.hx(), -PantsScale.hy() });
	Pants->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + PantsToNavelPos[MoveType][PantsName][AniIndex] + PantsOriginPos[MoveType][PantsName][AniIndex]);

	float4 HandPos = ArmHandPos[MoveType][AniIndex] + Arm->GetTransform()->GetLocalPosition();

	if (MoveType == "Jump" || MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{		
		float4 WeaponScale = Weapon->GetTransform()->GetLocalScale();
		Weapon->GetTransform()->SetLocalPosition({ WeaponScale.hx(), -WeaponScale.hy() });
		Weapon->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + WeaponToNavelPos[MoveType][WeaponName][AniIndex] + WeaponOriginPos[MoveType][WeaponName][AniIndex]);
	}
	else
	{
		float4 WeaponScale = Weapon->GetTransform()->GetLocalScale();
		Weapon->GetTransform()->SetLocalPosition({ WeaponScale.hx(), -WeaponScale.hy() });
		Weapon->GetTransform()->AddLocalPosition(HandPos + WeaponToHandPos[MoveType][WeaponName][AniIndex] + WeaponOriginPos[MoveType][WeaponName][AniIndex]);
	}
}