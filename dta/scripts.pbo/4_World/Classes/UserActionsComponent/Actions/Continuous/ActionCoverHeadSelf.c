class ActionCoverHeadSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.COVER_HEAD);
	}
};

class ActionCoverHeadSelf: ActionContinuousBase
{	
	void ActionCoverHeadSelf()
	{
		m_CallbackClass = ActionCoverHeadSelfCB;
		m_MessageStartFail = "It's too torn.";
		m_MessageStart = "I have started putting sack on";
		m_MessageSuccess = "I have put sack on.";
		m_MessageFail = "I have moved and putting sack on was canceled.";
		m_MessageCancel = "I stopped putting sack on.";
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_COVERHEAD_SELF;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		//m_Animation = "INJECTEPIPENS";
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override int GetType()
	{
		return AT_COVER_HEAD_S;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#put_on_head";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( IsWearingHeadgear(player) ) 
			return false;

		return true;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		//setaperture will be called from here, or from statemachine
		//GetGame().GetWorld().SetAperture(10000);
		action_data.m_Player.GetInventory().CreateInInventory("BurlapSackCover");
		action_data.m_MainItem.TransferModifiers(action_data.m_Player);
		action_data.m_MainItem.Delete();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}


	bool IsWearingHeadgear( PlayerBase player )
	{
		if ( player.GetInventory().FindAttachment(InventorySlots.HEADGEAR) )
		{
			return true;
		}
		return false;		
	}
};