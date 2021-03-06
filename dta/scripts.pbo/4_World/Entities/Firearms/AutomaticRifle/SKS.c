enum SKSAnimState
{
	DEFAULT 			= 0, 	///< default weapon state, closed and discharged
	OPENED 				= 1,
	JAMMED 				= 2,
};

enum SKSStableStateID
{
	UNKNOWN			=  0,
	SKS_CLO_BU0		=  1,
	SKS_CLO_BU1		=  2,
	SKS_OPN_BU0		=  3,
	SKS_JAM_BU1 	=  4
}

class SKS_CLO_BU0 extends WeaponStableState
{
	override void OnEntry (WeaponEventBase e) { wpnPrint("[wpnfsm] { close nobull"); super.OnEntry(e); }
	override void OnExit (WeaponEventBase e) { super.OnExit(e); wpnPrint("[wpnfsm] } close nobull"); }
	override int GetCurrentStateID () { return SKSStableStateID.SKS_CLO_BU0; }
	override bool HasBullet () { return false; }
	override bool HasMagazine () { return false; }
	override bool IsJammed () { return false; }

};
class SKS_CLO_BU1 extends WeaponStableState
{
	override void OnEntry (WeaponEventBase e) { wpnPrint("[wpnfsm] { close bullet"); super.OnEntry(e); }
	override void OnExit (WeaponEventBase e) { super.OnExit(e); wpnPrint("[wpnfsm] } close bullet"); }
	override int GetCurrentStateID () { return SKSStableStateID.SKS_CLO_BU1; }
	override bool HasBullet () { return true; }
	override bool HasMagazine () { return false; }
	override bool IsJammed () { return false; }
};
class SKS_OPN_BU0 extends WeaponStableState
{
	override void OnEntry (WeaponEventBase e) { wpnPrint("[wpnfsm] { open nobull"); super.OnEntry(e); }
	override void OnExit (WeaponEventBase e) { super.OnExit(e); wpnPrint("[wpnfsm] } open nobull"); }
	override int GetCurrentStateID () { return SKSStableStateID.SKS_OPN_BU0; }
	override bool HasBullet () { return false; }
	override bool HasMagazine () { return true; }
	override bool IsJammed () { return false; }
	override bool IsBoltOpen () { return true; }
};
class SKS_JAM_BU1 extends WeaponStateJammed
{
	override void OnEntry (WeaponEventBase e) { wpnPrint("[wpnfsm] { jammed bullet"); super.OnEntry(e); }
	override void OnExit (WeaponEventBase e) { super.OnExit(e); wpnPrint("[wpnfsm] } jammed bullet"); }
	override int GetCurrentStateID () { return SKSStableStateID.SKS_JAM_BU1; }
	override bool HasBullet () { return true; }
	override bool HasMagazine () { return false; }
	override bool IsJammed () { return true; }
	override bool IsBoltOpen () { return true; }
};

/**@class		Rifle_Base
 * @brief		base for rifles
 * @NOTE		name copies config base class
 **/
class SKS_Base extends Rifle_Base
{
	ref WeaponStateBase C0;
	ref	WeaponStateBase C1;
	ref	WeaponStateBase L0;
	ref	WeaponStateBase J1;
	
	override RecoilBase SpawnRecoilObject()
	{
		return new SKSRecoil(this);
	}
	
	override void InitStateMachine()
	{
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED_KEEP));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_OPENED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE));
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED)));//????
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_END)));
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_LAST)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY)));
		
		//m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_UNCOCKED));

		// setup state machine
		// basic weapon states
		// close-locked-jammed | nobullet-bullet | nomag-mag
		// regexp: [CLJ][01][01]
		C0 = new SKS_CLO_BU0(this, NULL, SKSAnimState.DEFAULT);
		C1 = new SKS_CLO_BU1(this, NULL, SKSAnimState.DEFAULT);
		L0 = new SKS_OPN_BU0(this, NULL, SKSAnimState.OPENED);
		J1 = new SKS_JAM_BU1(this, NULL, SKSAnimState.JAMMED);

		// unstable (intermediate) states
		WeaponChargingInnerMag Mech_C0 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		WeaponChargingInnerMag Mech_L0 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED));
		WeaponChargingInnerMag Mech_C1 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		
		//Fire
		WeaponStateBase Trigger_C0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY)); // cock without clip
		WeaponFireAndChamberFromInnerMagazine Trigger_C1 = new WeaponFireAndChamberFromInnerMagazine(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL), GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM));
		WeaponStateBase Trigger_C1L = new WeaponFireLast(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_LAST), GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM));
		WeaponStateBase Trigger_L0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_J1 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
	
		//Unjam
		WeaponStateBase Unjam_J1 = new WeaponUnjamming(this, NULL, WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START));

		//Chambering
		LoopedChambering 	Chamber_C0 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChambering 	Chamber_C1 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED_KEEP, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChambering 	Chamber_L0 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_OPENED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		
		//WeaponStateBase chmMag = new WeaponChamberFromAttMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);

		// events
		WeaponEventBase __M__ = new WeaponEventMechanism;
		WeaponEventBase __T__ = new WeaponEventTrigger;
		WeaponEventBase __U__ = new WeaponEventUnjam;
		WeaponEventBase __L__ = new WeaponEventLoad1Bullet;
		WeaponEventBase _fin_ = new WeaponEventHumanCommandActionFinished;
		WeaponEventBase _abt_ = new WeaponEventHumanCommandActionAborted;
		WeaponEventBase _rto_ = new WeaponEventReloadTimeout;
		WeaponEventBase _dto_ = new WeaponEventDryFireTimeout;

		m_fsm = new WeaponFSM();

		// order: Discharged-Charged | nobullet-bullet | nomag-mag
		// charging
		m_fsm.AddTransition(new WeaponTransition( C0,		__M__,	Mech_C1)); // charge from dischg nobullet nomag

		m_fsm.AddTransition(new WeaponTransition( C1,		__M__,	Mech_C1)); // charge from bullet nomag
		m_fsm.AddTransition(new WeaponTransition( Mech_C1,	_fin_,	C0, NULL, new WeaponGuardChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition( Mech_C1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Mech_C1,	_abt_,	C0, NULL, new WeaponGuardChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition( Mech_C1,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( L0, 		__M__,	Mech_L0)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition( Mech_L0,	_fin_,	C0));
			Mech_L0.AddTransition(new WeaponTransition( Mech_L0.m_start,	_abt_,	L0));
			Mech_L0.AddTransition(new WeaponTransition( Mech_L0.m_onCK,		_abt_,	C0));

		// fire
		m_fsm.AddTransition(new WeaponTransition( C0, 			__T__,	Trigger_C0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C0,	_fin_,	C0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C0,	_dto_,	C0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C0,	_abt_,	C0));
		
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__T__,	Trigger_C1, NULL, new WeaponGuardHasAmmoInnerMagazine(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_fin_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_rto_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_abt_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_rto_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__T__,	Trigger_C1L));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_fin_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_rto_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_abt_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_fin_,	L0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_rto_,	L0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_C1L,	_abt_,	L0));
	
		m_fsm.AddTransition(new WeaponTransition( L0,			__T__,	Trigger_L0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_L0,	_fin_,	L0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_L0,	_dto_,	L0));
		m_fsm.AddTransition(new WeaponTransition( Trigger_L0,	_abt_,	L0));
		
		m_fsm.AddTransition(new WeaponTransition( J1,			__T__,	Trigger_J1)); // opened fire.uncocked w mag
		m_fsm.AddTransition(new WeaponTransition( Trigger_J1,	_fin_,	J1));
		m_fsm.AddTransition(new WeaponTransition( Trigger_J1,	_dto_,	J1));
		m_fsm.AddTransition(new WeaponTransition( Trigger_J1,	_abt_,	J1));


		// load cartridge
		m_fsm.AddTransition(new WeaponTransition( C0,			__L__,	Chamber_C0));
		m_fsm.AddTransition(new WeaponTransition( Chamber_C0,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Chamber_C0,	_abt_,	C0, NULL, new WeaponGuardChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition( Chamber_C0,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__L__,	Chamber_C1, NULL, new GuardNot(new WeaponGuardInnerMagazineFullShareChamber(this))));
		m_fsm.AddTransition(new WeaponTransition( Chamber_C1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Chamber_C1,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( L0,			__L__,	Chamber_L0));
		m_fsm.AddTransition(new WeaponTransition( Chamber_L0,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Chamber_L0,	_abt_,	L0, NULL, new WeaponGuardChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition( Chamber_L0,	_abt_,	C1));

		
		// unjam
		m_fsm.AddTransition(new WeaponTransition( J1,		__U__,	Unjam_J1)); // unjam nomag
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_fin_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_fin_,	C0, NULL, new WeaponGuardChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_abt_,	J1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_abt_,	C0, NULL, new WeaponGuardChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition( Unjam_J1,	_abt_,	C1));

		m_fsm.SetInitialState(C0);

		SelectionBulletHide();
		SelectionMagazineHide();

		m_fsm.Start();
	}
	
	override bool CanEnterIronsights()
	{
		ItemOptics optic = GetAttachedOptics();
		if (optic && PUScopeOptic.Cast(optic))
			return true;
		return super.CanEnterIronsights();
	}
};