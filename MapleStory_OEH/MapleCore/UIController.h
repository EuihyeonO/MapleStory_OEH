#pragma once
#include "QuickSlot.h"
#include "PlayerValue.h"

#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <functional>

class UIController
{

public:

	UIController(const UIController& _Other) = delete;
	UIController(UIController&& _Other) noexcept = delete;
	UIController& operator=(const UIController& _Other) = delete;
	UIController& operator=(UIController&& _Other) noexcept = delete;

	static UIController* GetUIController()
	{
		return &Value;
	}

	void AddQuickSlotToList(std::shared_ptr<class QuickSlot> _QuickSlot)
	{
		QuickSlotList.push_back(_QuickSlot);
	}

	void SetShiftSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		ShiftSkillTexName = _TexName.data();
		ShiftSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetShiftSlotTexture(ShiftSkillTexName);
		}

		PlayerValue::GetValue()->SetShiftSkillAllPlayer(_SkillFunc);
	}
	void SetInsSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		InsSkillTexName = _TexName.data();
		InsSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetInsSlotTexture(InsSkillTexName);
		}

		PlayerValue::GetValue()->SetInsSkillAllPlayer(_SkillFunc);
	}
	void SetHomeSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		HomeSkillTexName = _TexName.data();
		HomeSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetHomeSlotTexture(HomeSkillTexName);
		}

		PlayerValue::GetValue()->SetHomeSkillAllPlayer(_SkillFunc);
	}
	void SetPgUpSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		PgUpSkillTexName = _TexName.data();
		PgUpSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetPgUpSlotTexture(PgUpSkillTexName);
		}

		PlayerValue::GetValue()->SetPgUpSkillAllPlayer(_SkillFunc);
	}
	void SetCtrlSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		CtrlSkillTexName = _TexName.data();
		CtrlSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetCtrlSlotTexture(CtrlSkillTexName);
		}

		PlayerValue::GetValue()->SetCtrlSkillAllPlayer(_SkillFunc);
	}
	void SetDelSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		DelSkillTexName = _TexName.data();
		DelSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetDelSlotTexture(DelSkillTexName);
		}

		PlayerValue::GetValue()->SetDelSkillAllPlayer(_SkillFunc);
	}
	void SetEndSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		EndSkillTexName = _TexName.data();
		EndSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetEndSlotTexture(EndSkillTexName);
		}

		PlayerValue::GetValue()->SetEndSkillAllPlayer(_SkillFunc);
	}
	void SetPgDNSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		PgDNSkillTexName = _TexName.data();
		PgDNSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetPgDnSlotTexture(PgDNSkillTexName);
		}

		PlayerValue::GetValue()->SetPgDnSkillAllPlayer(_SkillFunc);
	}

	void SetSkillAllQuickSlot();
protected:

private:
	UIController();
	~UIController();

	static UIController Value;

	std::vector<std::shared_ptr<class QuickSlot>> QuickSlotList;

	//QuickSlot
	std::string ShiftSkillTexName = "";
	std::string InsSkillTexName = "";
	std::string HomeSkillTexName = "";
	std::string PgUpSkillTexName = "";
	std::string CtrlSkillTexName = "";
	std::string DelSkillTexName = "";
	std::string EndSkillTexName = "";
	std::string PgDNSkillTexName = "";

	std::function<void(std::shared_ptr<class Player>)> ShiftSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> InsSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> HomeSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> PgUpSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> CtrlSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> DelSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> EndSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> PgDNSkill = nullptr;
};
