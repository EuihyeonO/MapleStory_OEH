#pragma once
#include "ContentButton.h"

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

class GameEngineSpriteRenderer;
class SkillList : public GameEngineActor
{
	friend class SkillWindow;

public:

	class SkillIcon : public GameEngineActor
	{		
		friend SkillList;
		
	public:		
		static std::shared_ptr<GameEngineUIRenderer> IconCopy;
		static std::function<void(std::shared_ptr<class Player>)> FunctionCopy;

	private:

		std::shared_ptr<GameEngineUIRenderer> SkillBackGround = nullptr;

		std::shared_ptr<GameEngineUIRenderer> IconRender = nullptr;
		std::shared_ptr<class GameEngineCollision> IconCollision = nullptr;

		std::shared_ptr<GameEngineUIRenderer> SkillLevelUpRender = nullptr;
		std::shared_ptr<class GameEngineCollision> SkillLevelUpButton = nullptr;

		std::string SkillName = "";

		std::function<void(std::shared_ptr<class Player>)> SkillFunc = nullptr;

		std::shared_ptr<class ContentFontRenderer> SkillNameFont = nullptr;
		std::shared_ptr<class ContentFontRenderer> SkillLv = nullptr;

		std::shared_ptr<ContentButton> LvUpBt = nullptr;
		
		bool isPassive = false;
	};

public:

	void ClearList()
	{
		std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator Start = SkillVector.begin();
		std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator End = SkillVector.end();

		for (; Start != End; Start++)
		{
			for (int i = 0; i < Start->second.size(); i++)
			{
				Start->second[i]->LvUpBt->Death();
				Start->second[i]->Death();
				Start->second[i] = nullptr;
			}
		}

		if(SkillIcon::IconCopy != nullptr)
		{
			SkillIcon::IconCopy->Death();
			SkillIcon::IconCopy = nullptr;
		}
		
		if (SkillIcon::FunctionCopy != nullptr)
		{
			SkillIcon::FunctionCopy = nullptr;
		}
	}

	SkillList();
	~SkillList();

	SkillList(const SkillList& _Other) = delete;
	SkillList(SkillList&& _Other) noexcept = delete;
	SkillList& operator=(const SkillList& _Other) = delete;
	SkillList& operator=(SkillList&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ColPosUpdate();

	void InsertSkillToList(int _Index, const std::string_view& _SkillName, bool isPassive = false);
	void IndexSkillOn(int _Index);
	void IndexSkillOff(int _Index);
	void SortSkillList(int _Index, float4 _Pos = {0, 0});
	void SetSkillIcon(std::shared_ptr<SkillList::SkillIcon> _SkillIcon);

	int CurIndex = 0;

	std::shared_ptr<GameEngineCollision> CollisionCheck();
	std::shared_ptr<GameEngineCollision> CollisionCheckToQuickSlot();
	std::shared_ptr<SkillList::SkillIcon> FindParantOfCol(std::shared_ptr<GameEngineCollision> _Col);
	void SkillCopy(std::shared_ptr<SkillList::SkillIcon> _SkillIcon);
	void SkillCopy();

	std::map<int, std::vector<std::shared_ptr<SkillIcon>>> SkillVector;
};

