class ActionRestrainTargetCB : ActionContinuousBaseCB
{
	const float DEFAULT_RESTRAIN_TIME = 2;
	
	override void CreateActionComponent()
	{
		float time = DEFAULT_RESTRAIN_TIME;
		
		if( m_ActionData.m_MainItem.ConfigIsExisting("RestrainTime") )
		{
			time = m_ActionData.m_MainItem.ConfigGetFloat("RestrainTime");
		}
		
		if( m_ActionData.m_Player.IsQuickRestrain() )
		{
			time = DEBUG_QUICK_UNRESTRAIN_TIME;
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
};

class ActionRestrainTarget: ActionContinuousBase
{	
	void ActionRestrainTarget()
	{
		m_CallbackClass = ActionRestrainTargetCB;
		m_MessageStartFail = "Item is damaged.";
		m_MessageStart = "Player started restraining you.";
		m_MessageSuccess = "Player finished restraining you.";
		m_MessageFail = "Player moved and restraining was canceled.";
		m_MessageCancel = "You stopped restraining.";
		//m_Animation = "restrain";
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_SERVER )
		{
			PlayerBase other_player = PlayerBase.Cast(target.GetObject());
			return other_player.CanBeRestrained();
		}
		
		return true;
	}

	override bool ActionConditionContinue(ActionData action_data)
	{
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if( GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			if( target_player.IsSurrendered() || !target_player.CanBeRestrained() )
			{
				return false;
			}
		}
		if( GetGame().IsServer() )
		{
			return !GetGame().GetMission().IsPlayerDisconnecting(target_player);
			
		}
		return true;
	}
		
	
	override int GetType()
	{
		return AT_RESTRAIN_T;
	}
		
	override string GetText()
	{
		return "#restrain";
	}
	
	override void OnStartServer(ActionData action_data)
	{
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if( target_player.IsSurrendered() )
		{
			SurrenderDataRestrain sdr = new SurrenderDataRestrain;
			target_player.EndSurrenderRequest(sdr);
		}
		/*
		if( target_player.IsMapOpen() )
		{
			target_player.CloseMap();
		}
		*/
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		PlayerBase source_player = PlayerBase.Cast(action_data.m_Player);
	
		EntityAI item_in_hands_target = target_player.GetHumanInventory().GetEntityInHands();
		EntityAI item_in_hands_source = source_player.GetHumanInventory().GetEntityInHands();
		
		if( !item_in_hands_source )
		{
			Error("Restraining target failed, nothing in hands");
			return;
		}

		string new_item_name = MiscGameplayFunctions.ObtainRestrainItemTargetClassname(item_in_hands_source);
		if (item_in_hands_target)
		{
			Print("Restraining player with item in hands, drop first");
			target_player.ServerDropEntity(item_in_hands_target);				
		}

		Print("Restraining player with empty hands");
		RestrainTargetPlayerLambda lambda = new RestrainTargetPlayerLambda(item_in_hands_source, new_item_name, target_player);
		source_player.LocalReplaceItemInHandsWithNewElsewhere(lambda);
		
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
	
	override void OnFinishProgressClient( ActionData action_data )
	{
		super.OnFinishProgressClient( action_data );
		
		AnalyticsManager.OnActionRestrain();
	}
};

class RestrainTargetPlayerLambda : ReplaceItemWithNewLambdaBase
{
	PlayerBase m_TargetPlayer;

	void RestrainTargetPlayerLambda (EntityAI old_item, string new_item_type, PlayerBase player)
	{
		m_TargetPlayer = player;
		
		InventoryLocation targetHnd = new InventoryLocation;
		targetHnd.SetHands(m_TargetPlayer, null);
		OverrideNewLocation(targetHnd);
	}
	
	override void OnSuccess(EntityAI entity)
	{
		super.OnSuccess(new_item);

		m_TargetPlayer.SetRestrained(true);
	}
};

class SurrenderDataRestrain extends SurrenderData
{
	override void End()
	{
		
	}
}