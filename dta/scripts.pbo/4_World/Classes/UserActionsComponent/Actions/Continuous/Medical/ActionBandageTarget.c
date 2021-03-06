class ActionBandageTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.BANDAGE);
	}
};

class ActionBandageTarget: ActionContinuousBase
{
	void ActionBandageTarget()
	{
		m_CallbackClass = ActionBandageTargetCB;
		m_MessageStartFail = "There's no bandage left.";
		m_MessageStart = "Player started bandaging you.";
		m_MessageSuccess = "Player finished bandaging you.";
		m_MessageFail = "Player moved and bandaging was canceled.";
		m_MessageCancel = "You stopped bandaging.";
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override int GetType()
	{
		return AT_BANDAGE_T;
	}
		
	override string GetText()
	{
		return "#treat_persons_wound";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase other_player = PlayerBase.Cast(target.GetObject());
		return other_player.IsBleeding();
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (ntarget.GetBleedingManagerServer() )
		{
			ntarget.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
		}
		
		if (action_data.m_MainItem.GetQuantity() > 0)
		{
			action_data.m_MainItem.AddQuantity(-1,true);
		}

		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
	
	override void OnFinishProgressClient( ActionData action_data )
	{
		AnalyticsManager.OnActionBandageTarget();
	}
};
