////////////////////////////////////////////////////////////////////
//DeRap: vehicles_wheeled\config.bin
//Produced from mikero's Dos Tools Dll version 7.16
//https://armaservices.maverick-applications.com/Products/MikerosDosTools/default
//'now' is Tue Apr 02 16:51:44 2019 : 'file' last modified on Mon Apr 01 08:59:43 2019
////////////////////////////////////////////////////////////////////

#define _ARMA_

//(8 Enums)
enum {
	destructengine = 2,
	destructdefault = 6,
	destructwreck = 7,
	destructtree = 3,
	destructtent = 4,
	destructno = 0,
	destructman = 5,
	destructbuilding = 1
};

class CfgPatches
{
	class DZ_Vehicles_Wheeled
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class CarWheel: Inventory_Base
	{
		InteractActions[] = {573};
		SingleUseActions[] = {577};
		simulation = "carwheel";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset = "hatchbackwheel_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class CarDoor: Inventory_Base
	{
		scope = 1;
		InteractActions[] = {1043,1042,573};
		SingleUseActions[] = {577};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
			class DamageZones
			{
				class Window
				{
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{""}}};
					};
					componentNames[] = {"dmgZone_window"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Doors
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{""}}};
					};
					componentNames[] = {"dmgZone_doors"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUp
				{
					soundSet = "hatchbackdoors_driver_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "hatchbackdoors_driver_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class Car;
	class CarScript: Car
	{
		InteractActions[] = {1047,1035};
		rotationFlags = 64;
		storageCategory = 4;
		insideSoundCoef = 0.9;
		fuelCapacity = 50;
		brakeFluidCapacity = 1;
		oilCapacity = 4;
		coolantCapacity = 6;
		brakeFluidLeakDebit[] = {0.0,0.0};
		oilLeakDebit[] = {0.0,0.0};
		coolantLeakDebit[] = {0.0,0.0};
		brakeFluidForceCoef[] = {0.0,1.0,1.0,1.0};
		damageFromOil[] = {0.0,0.0,1.0,0.0};
		damageFromCoolant[] = {0.0,0.0,1.0,0.0};
		engineBeltSlot = "EngineBelt";
		batterySlot = "CarBattery";
		electricPowerResName = "power";
		electricConsumptionIgnition = 3001;
		electricConsumptionEngine = 0.0;
		electricConsumptionLights = 0.0;
		electricOutputEngine = 5.0;
		selectionDashboard = "light_dashboard";
		selectionLightFrontL = "light_left";
		selectionLightFrontR = "light_right";
		selectionBrakeLights = "light_break";
		class Crew
		{
			class Driver
			{
				actionSel = "seat_driver";
				proxyPos = "crewDriver";
				getInPos = "pos_driver";
				getInDir = "pos_driver_dir";
				isDriver = 1;
			};
			class CoDriver
			{
				actionSel = "seat_coDriver";
				proxyPos = "crewCoDriver";
				getInPos = "pos_coDriver";
				getInDir = "pos_coDriver_dir";
			};
		};
		class SimulationModule
		{
			class Axles
			{
				class Front
				{
					class Wheels
					{
						class Left
						{
							inventorySlot = "";
							animTurn = "turnfrontleft";
							animRotation = "wheelfrontleft";
							animDamper = "damperfrontleft";
							wheelHub = "wheel_1_1_damper_land";
						};
						class Right
						{
							inventorySlot = "";
							animTurn = "turnfrontright";
							animRotation = "wheelfrontright";
							animDamper = "damperfrontright";
							wheelHub = "wheel_2_1_damper_land";
						};
					};
				};
				class Rear
				{
					class Wheels
					{
						class Left
						{
							inventorySlot = "";
							animTurn = "turnbackleft";
							animRotation = "wheelbackleft";
							animDamper = "damperbackleft";
							wheelHub = "wheel_1_2_damper_land";
						};
						class Right
						{
							inventorySlot = "";
							animTurn = "turnbacktright";
							animRotation = "wheelbackright";
							animDamper = "damperbackright";
							wheelHub = "wheel_2_2_damper_land";
						};
					};
				};
			};
		};
		attachments[] = {"CarBattery","LightBulb","SparkPlug","V3SWheel_1_1","V3SWheel_2_1"};
		engineVitalParts[] = {"SparkPlug","CarBattery"};
		electricalVitalParts[] = {"CarBattery","HeadlightH7"};
		hiddenSelections[] = {""};
		hiddenSelectionsTextures[] = {""};
		class ViewPilot
		{
			initFov = 0.769;
			minFov = 0.4143;
			maxFov = 1.192;
			initFovEXT = 0.73;
			minFovEXT = 0.4143;
			maxFovEXT = 0.95;
			initAngleX = 0;
			minAngleX = -85;
			maxAngleX = 85;
			initAngleY = 0;
			minAngleY = -150;
			maxAngleY = 150;
		};
		class AnimationSources
		{
			class DoorsDriver
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCoDriver: DoorsDriver{};
			class DoorsHood: DoorsDriver{};
			class DoorsTrunk: DoorsDriver{};
			class HideDestroyed_1_1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.001;
			};
			class HideDestroyed_1_2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.001;
			};
			class HideDestroyed_2_1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.001;
			};
			class HideDestroyed_2_2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.001;
			};
			class AnimHitWheel_1_1
			{
				source = "Hit";
				hitpoint = "HitWheel_1_1";
				raw = 1;
			};
			class AnimHitWheel_1_2: AnimHitWheel_1_1
			{
				hitpoint = "HitWheel_1_2";
			};
			class AnimHitWheel_2_1: AnimHitWheel_1_1
			{
				hitpoint = "HitWheel_2_1";
			};
			class AnimHitWheel_2_2: AnimHitWheel_1_1
			{
				hitpoint = "HitWheel_2_2";
			};
			class HitDoorsHood: AnimHitWheel_1_1
			{
				hitpoint = "HitDoorsHood";
			};
			class HitDoorsTrunk: AnimHitWheel_1_1
			{
				hitpoint = "HitDoorsTrunk";
			};
			class HitDoorsDrivers: AnimHitWheel_1_1
			{
				hitpoint = "HitDoorsDriver";
			};
			class HitDoorsCoDrivers: AnimHitWheel_1_1
			{
				hitpoint = "HitDoorsCoDriver";
			};
			class HitDoorsCargo: AnimHitWheel_1_1
			{
				hitpoint = "HitDoorsCargo";
			};
		};
		class Reflectors
		{
			class Left
			{
				color[] = {1.0,0.8,0.6,1.0};
				brightness = 30.0;
				radius = 70;
				angle = 120;
				angleInnerRatio = 0.25;
				dayLight = 1;
				flareAngleBias = 40.0;
				position = "light_left";
				direction = "light_left_dir";
				hitpoint = "dmgZone_lights";
				selection = "dmgZone_lights";
			};
			class Right: Left
			{
				position = "light_right";
				direction = "light_right_dir";
				hitpoint = "dmgZone_lights";
				selection = "dmgZone_light";
			};
		};
	};
	class V3SWheel: CarWheel
	{
		scope = 2;
		displayName = "$STR_V3SWheel0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel.p3d";
		weight = 30000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot[] = {"V3SWheel_1_1","V3SWheel_2_1","V3SWheel_Spare_1","V3SWheel_Spare_2"};
		rotationFlags = 12;
		physLayer = "item_large";
		radiusByDamage[] = {0,0.465,0.3,0.38,0.9998,0.35,0.9999,0.28};
		radius = 0.465;
		width = 0.2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"}},{0.7,{"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"}},{0.5,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"}},{0.3,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"}},{0.0,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_destruct.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_destruct.rvmat"}}};
				};
			};
		};
	};
	class V3SWheel_Ruined: CarWheel
	{
		scope = 2;
		displayName = "$STR_V3SWheel0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_new_burst.p3d";
		itemSize[] = {10,10};
		weight = 25000;
		itemBehaviour = 0;
		physLayer = "item_large";
		inventorySlot[] = {"V3SWheel_1_1","V3SWheel_2_1","V3SWheel_Spare_1","V3SWheel_Spare_2"};
		rotationFlags = 12;
		radius = 0.3;
		width = 0.2;
	};
	class V3SWheelDouble: V3SWheel
	{
		displayName = "$STR_V3SWheelDouble0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_double.p3d";
		itemBehaviour = 0;
		inventorySlot[] = {"V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_2","V3SWheel_2_3"};
		width = 0.4;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 400;
					healthLevels[] = {{1.0,{"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"}},{0.7,{"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"}},{0.5,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"}},{0.3,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"}},{0.0,{"DZ\vehicles\wheeled\V3S\data\v3s_tire_destruct.rvmat","DZ\vehicles\wheeled\V3S\data\v3s_rim_destruct.rvmat"}}};
				};
			};
		};
	};
	class V3SWheelDouble_Ruined: V3SWheel_Ruined
	{
		displayName = "$STR_V3SWheelDouble0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_burst_double.p3d";
		itemBehaviour = 0;
		inventorySlot[] = {"V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_2","V3SWheel_2_3"};
		width = 0.4;
	};
	class V3SDoors_Driver: CarDoor
	{
		scope = 2;
		displayName = "$STR_V3SDoors_Driver0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_doors_Driver.p3d";
		weight = 15000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot = "V3SDriverDoors";
		rotationFlags = 8;
		physLayer = "item_large";
		hiddenSelections[] = {"camo_Door"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
			class DamageZones
			{
				class Window
				{
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\V3S\data\v3s_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"}},{0.3,{}},{0.0,{""}}};
					};
					componentNames[] = {"dmgZone_window"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Doors
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\V3S\data\v3s_door.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\V3S\data\v3s_door_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\V3S\data\v3s_door_destruct.rvmat"}}};
					};
					componentNames[] = {"dmgZone_doors"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
	};
	class V3SDoors_CoDriver: V3SDoors_Driver
	{
		displayName = "$STR_V3SDoors_CoDriver0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_doors_coDriver.p3d";
		itemBehaviour = 0;
		inventorySlot = "V3SCoDriverDoors";
		rotationFlags = 4;
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_co.paa"};
	};
	class V3SDoors_Driver_Orange: V3SDoors_Driver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_co.paa"};
	};
	class V3SDoors_CoDriver_Orange: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_co.paa"};
	};
	class V3SDoors_Driver_Blue: V3SDoors_Driver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_co.paa"};
	};
	class V3SDoors_CoDriver_Blue: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_co.paa"};
	};
	class V3SDoors_Driver_Grey: V3SDoors_Driver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_co.paa"};
	};
	class V3SDoors_CoDriver_Grey: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_co.paa"};
	};
	class V3SHood: CarDoor
	{
		scope = 2;
		displayName = "$STR_V3SHood0";
		model = "\DZ\vehicles\wheeled\V3S\proxy\v3s_hood.p3d";
		weight = 15000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot = "V3SHood";
		rotationFlags = 2;
		physLayer = "item_large";
		hiddenSelections[] = {"camo_Door"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_green_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{"dz\vehicles\wheeled\V3S\data\v3s_hood_green.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\V3S\data\v3s_hood_green_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\V3S\data\v3s_hood_green_destruct.rvmat"}}};
				};
				componentNames[] = {"dmgZone_doors"};
			};
		};
	};
	class V3SHood_Orange: V3SHood
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_co.paa"};
	};
	class V3SHood_Blue: V3SHood
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_Blue_co.paa"};
	};
	class V3SHood_Grey: V3SHood
	{
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_Grey_co.paa"};
	};
	class V3S_Chassis: CarScript
	{
		scope = 2;
		displayName = "$STR_v3s_chassis0";
		model = "\dz\vehicles\wheeled\V3S\V3S_chassis.p3d";
		InteractActions[] = {1047,1035};
		attachments[] = {"TruckBattery","Reflector_1_1","Reflector_2_1","V3SDriverDoors","V3SCoDriverDoors","V3SHood","V3SWheel_1_1","V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_1","V3SWheel_2_2","V3SWheel_2_3","V3SWheel_Spare_1","V3SWheel_Spare_2"};
		extCameraPosition[] = {0,1.5,-8.5};
		dashboardMatOn = "dz\vehicles\wheeled\v3s\data\v3s_dashboard_light.rvmat";
		dashboardMatOff = "dz\vehicles\wheeled\v3s\data\v3s_dashboard.rvmat";
		frontReflectorMatOn = "dz\vehicles\wheeled\v3s\data\v3s_cab_lights.rvmat";
		frontReflectorMatOff = "dz\vehicles\wheeled\v3s\data\v3s_cab_chrome.rvmat";
		frontReflectorMatDamaged = "dz\vehicles\wheeled\v3s\data\v3s_cab_damage.rvmat";
		frontReflectorMatRuined = "dz\vehicles\wheeled\v3s\data\v3s_cab_destruct.rvmat";
		fuelCapacity = 120;
		fuelConsumption = 30;
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_642";
			airDragCoefficient = 0.51;
			class Steering
			{
				increaseSpeed[] = {0,25,50,15};
				decreaseSpeed[] = {0,50,50,40};
				centeringSpeed[] = {0,25,50.0,15};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 3.0;
				gentleCoef = 0.5;
			};
			class Engine
			{
				inertia = 1.5;
				powerMax = 72;
				powerRpm = 2100;
				torqueMax = 360;
				torqueRpm = 1400;
				rpmIdle = 600;
				rpmMin = 650;
				rpmClutch = 700;
				rpmRedline = 2600;
				rpmMax = 3000;
			};
			class Gearbox
			{
				reverse = 6.28;
				ratios[] = {6.19,3.13,1.75,1.0};
				timeToUncoupleClutch = 0.4;
				timeToCoupleClutch = 0.2;
				maxClutchTorque = 400;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 35;
					finalRatio = 6.84;
					brakeBias = 0.5;
					brakeForce = 8000;
					wheelHubMass = 25;
					wheelHubRadius = 0.3;
					wheelHubRatio = 2.14;
					class Suspension
					{
						stiffness = 550000;
						compression = 6000;
						damping = 11500;
						travelMaxUp = 0.14;
						travelMaxDown = 0.15;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "V3SWheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "V3SWheel_2_1";
						};
					};
				};
				class Middle: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 6.84;
					brakeBias = 0.25;
					brakeForce = 7500;
					wheelHubMass = 45;
					wheelHubRadius = 0.3;
					wheelHubRatio = 2.14;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 360000;
						compression = 7000;
						damping = 12000;
						travelMaxUp = 0.095;
						travelMaxDown = 0.125;
					};
					class Wheels: Wheels
					{
						class Left
						{
							inventorySlot = "V3SWheel_1_2";
							animTurn = "turnmiddleleft";
							animRotation = "wheelmiddleleft";
							animDamper = "damper_1_2";
							wheelHub = "wheel_1_2_damper_land";
						};
						class Right
						{
							inventorySlot = "V3SWheel_2_2";
							animTurn = "turnmiddletright";
							animRotation = "wheelmiddleright";
							animDamper = "damper_2_2";
							wheelHub = "wheel_2_2_damper_land";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 6.84;
					brakeBias = 0.25;
					brakeForce = 7500;
					wheelHubMass = 45;
					wheelHubRadius = 0.3;
					wheelHubRatio = 2.14;
					class Suspension
					{
						stiffness = 360000;
						compression = 7000;
						damping = 12000;
						travelMaxUp = 0.095;
						travelMaxDown = 0.125;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_3";
							inventorySlot = "V3SWheel_1_3";
							wheelHub = "wheel_1_3_damper_land";
						};
						class Right: Right
						{
							animDamper = "damper_2_3";
							inventorySlot = "V3SWheel_2_3";
							wheelHub = "wheel_2_3_damper_land";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {10,30};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class WheelSidePlate1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 1.3;
			};
			class WheelSidePlate2: WheelSidePlate1{};
			class Damper_1_1
			{
				source = "user";
				initPhase = 0.4828;
				animPeriod = 1;
			};
			class Damper_2_1: Damper_1_1{};
			class Damper_1_2
			{
				source = "user";
				initPhase = 0.4318;
				animPeriod = 1;
			};
			class Damper_2_2: Damper_1_2{};
			class Damper_1_3: Damper_1_2{};
			class Damper_2_3: Damper_1_2{};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					class Health
					{
						hitpoints = 3000;
						transferToGlobalCoef = 1;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Front
				{
					class Health
					{
						hitpoints = 2500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_1","Fender_2_1","Engine"};
					transferToZonesThreshold[] = {0.2,0.2,0.0};
					transferToZonesCoefs[] = {0.6,0.6,0.8};
					memoryPoints[] = {"dmgZone_front"};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"NivaHood"};
				};
				class Back
				{
					class Health
					{
						hitpoints = 3000;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\v3s\data\v3s_cargo.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_2","Fender_2_2","WindowLR","WindowRR"};
					transferToZonesCoefs[] = {0.3,0.3,0.2,0.2};
					memoryPoints[] = {"dmgZone_back"};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_roof"};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Fender_1_1
				{
					class Health
					{
						hitpoints = 800;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Front","Engine","Lights"};
					transferToZonesThreshold[] = {0.5,0.25,1.0};
					transferToZonesCoefs[] = {0.3,0.6,0.8};
					memoryPoints[] = {"dmgZone_fender_1_1"};
					componentNames[] = {"dmgZone_fender_1_1"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"V3SWheel_1_1"};
				};
				class Fender_2_1: Fender_1_1
				{
					memoryPoints[] = {"dmgZone_fender_2_1"};
					componentNames[] = {"dmgZone_fender_2_1"};
					inventorySlots[] = {"V3SWheel_2_1"};
				};
				class WindowFrontLeft
				{
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\V3S\data\V3S_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"}},{0.3,{}},{0.0,{""}}};
					};
					memoryPoints[] = {"dmgZone_windowFrontLeft"};
					componentNames[] = {"dmgZone_windowFrontLeft"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class WindowFrontRight: WindowFrontLeft
				{
					memoryPoints[] = {"dmgZone_windowFrontRight"};
					componentNames[] = {"dmgZone_windowFrontRight"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\v3s\data\v3s_chassis.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_engine"};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 0.001;
					inventorySlots[] = {};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 300;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\v3s\data\v3s_chassis.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"}}};
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Reflector_1_1
				{
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
					};
					transferToZonesNames[] = {"Front","Fender_1_1"};
					transferToZonesCoefs[] = {1.0,1.0};
					memoryPoints[] = {"dmgZone_lights_1_1"};
					componentNames[] = {"dmgZone_lights_1_1"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"Reflector_1_1"};
				};
				class Reflector_2_1: Reflector_1_1
				{
					transferToZonesNames[] = {"Front","Fender_2_1"};
					transferToZonesCoefs[] = {1.0,1.0};
					memoryPoints[] = {"dmgZone_lights_2_1"};
					componentNames[] = {"dmgZone_lights_2_1"};
					inventorySlots[] = {"Reflector_2_1"};
				};
			};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,1.5};
					};
					class Cyl2
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-1.5};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"TruckBattery","EngineBelt"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"LightBulb","V3SDriverDoors","V3SCoDriverDoors","V3SHood"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"V3SWheel_1_1","V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_1","V3SWheel_2_2","V3SWheel_2_3","V3SWheel_Spare_1","V3SWheel_Spare_2"};
			};
		};
	};
	class V3S_Chassis_Blue: V3S_Chassis
	{
		scope = 2;
		hiddenSelections[] = {"hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa"};
	};
	class V3S_Chassis_Orange: V3S_Chassis
	{
		scope = 2;
		hiddenSelections[] = {"spare_wheels","hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"","\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa"};
	};
	class V3S_Chassis_Grey: V3S_Chassis
	{
		scope = 2;
		hiddenSelections[] = {"hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa"};
	};
	class V3S_Cargo: V3S_Chassis
	{
		displayName = "$STR_v3s_cargo0";
		model = "\dz\vehicles\wheeled\V3S\V3S_cargo.p3d";
		class Cargo
		{
			itemsCargoSize[] = {10,60};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsTrunk
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
		};
	};
	class V3S_Cargo_Blue: V3S_Cargo
	{
		scope = 2;
		hiddenSelections[] = {"hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa"};
	};
	class V3S_Cargo_Orange: V3S_Cargo
	{
		scope = 2;
		hiddenSelections[] = {"hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa"};
	};
	class V3S_Cargo_Grey: V3S_Cargo
	{
		scope = 2;
		hiddenSelections[] = {"hood","cabin","doors_Driver","doors_coDriver"};
		hiddenSelectionsTextures[] = {"\dz\vehicles\wheeled\V3S\data\v3s_hood_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_cab_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa","\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa"};
	};
	class CivSedanWheel: CarWheel
	{
		scope = 2;
		displayName = "$STR_CivSedanWheel0";
		descriptionShort = "$STR_CivSedanWheel1";
		model = "\DZ\vehicles\wheeled\civiliansedan\proxy\sedanwheel.p3d";
		weight = 12000;
		itemSize[] = {6,6};
		inventorySlot[] = {"CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2"};
		rotationFlags = 4;
		physLayer = "item_large";
		repairableWithKits[] = {6};
		repairCosts[] = {20.0};
		radiusByDamage[] = {0,0.34,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.34;
		friction = 0.96;
		width = 0.16;
		tyreRollResistance = 0.015;
		tyreTread = 1.0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"DZ\vehicles\wheeled\OffroadHatchback\data\gaz_wheel.rvmat"}},{0.7,{"DZ\vehicles\wheeled\OffroadHatchback\data\gaz_wheel.rvmat"}},{0.5,{"DZ\vehicles\wheeled\OffroadHatchback\data\gaz_wheel_damage.rvmat"}},{0.3,{"DZ\vehicles\wheeled\OffroadHatchback\data\gaz_wheel_damage.rvmat"}},{0.0,{"DZ\vehicles\wheeled\OffroadHatchback\data\gaz_wheel_destruct.rvmat"}}};
				};
			};
		};
	};
	class CivSedanWheel_Ruined: CarWheel
	{
		scope = 2;
		displayName = "$STR_CivSedanWheel0";
		model = "\DZ\vehicles\wheeled\civiliansedan\proxy\sedanwheel_destroyed.p3d";
		weight = 12000;
		itemSize[] = {6,6};
		inventorySlot[] = {"CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2"};
		rotationFlags = 4;
		physLayer = "item_large";
		radius = 0.238;
		width = 0.2;
		tyreRollResistance = 1;
		tyreRollDrag = 75;
		tyreRoughness = 1.2;
		tyreTread = 0.5;
	};
	class CivSedanDoors_Driver: CarDoor
	{
		scope = 2;
		displayName = "$STR_CivSedanDoors_Driver0";
		descriptionShort = "$STR_CivSedanDoors_Driver1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_Driver.p3d";
		weight = 15000;
		itemSize[] = {10,8};
		inventorySlot = "CivSedanDriverDoors";
		rotationFlags = 8;
		physLayer = "item_large";
		class DamageSystem: DamageSystem
		{
			class GlobalHealth: GlobalHealth{};
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\glass.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\glass.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\glass_destruct.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i_destruct.rvmat"}},{0.0,"hidden"}};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_destruct.rvmat"}}};
					};
				};
			};
		};
	};
	class CivSedanDoors_CoDriver: CivSedanDoors_Driver
	{
		displayName = "$STR_CivSedanDoors_CoDriver0";
		descriptionShort = "$STR_CivSedanDoors_CoDriver1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_coDriver.p3d";
		inventorySlot = "CivSedanCoDriverDoors";
		rotationFlags = 4;
	};
	class CivSedanDoors_BackLeft: CivSedanDoors_Driver
	{
		displayName = "$STR_CivSedanDoors_BackLeft0";
		descriptionShort = "$STR_CivSedanDoors_BackLeft1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_cargo1.p3d";
		inventorySlot = "CivSedanCargo1Doors";
	};
	class CivSedanDoors_BackRight: CivSedanDoors_Driver
	{
		displayName = "$STR_CivSedanDoors_BackRight0";
		descriptionShort = "$STR_CivSedanDoors_BackRight1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_cargo2.p3d";
		inventorySlot = "CivSedanCargo2Doors";
		rotationFlags = 4;
	};
	class CivSedanHood: CarDoor
	{
		scope = 2;
		displayName = "$STR_CivSedanHood0";
		descriptionShort = "$STR_CivSedanHood1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanhood.p3d";
		weight = 15000;
		itemSize[] = {12,10};
		inventorySlot = "CivSedanHood";
		rotationFlags = 4;
		physLayer = "item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_destruct.rvmat"}}};
				};
			};
		};
	};
	class CivSedanTrunk: CarDoor
	{
		scope = 2;
		displayName = "$STR_CivSedanTrunk0";
		descriptionShort = "$STR_CivSedanTrunk1";
		model = "\DZ\vehicles\wheeled\civilianSedan\proxy\sedanTrunk.p3d";
		weight = 15000;
		itemSize[] = {12,10};
		inventorySlot = "CivSedanTrunk";
		rotationFlags = 4;
		physLayer = "item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_destruct.rvmat"}}};
				};
			};
		};
	};
	class CivilianSedan: CarScript
	{
		scope = 2;
		displayName = "$STR_CivilianSedan0";
		descriptionShort = "$STR_CivilianSedan1";
		model = "\DZ\vehicles\wheeled\civiliansedan\CivilianSedan.p3d";
		attachments[] = {"CarBattery","Reflector_1_1","Reflector_2_1","CarRadiator","SparkPlug","CivSedanDriverDoors","CivSedanCoDriverDoors","CivSedanCargo1Doors","CivSedanCargo2Doors","CivSedanHood","CivSedanTrunk","CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2"};
		dashboardMatOn = "dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2e_.rvmat";
		dashboardMatOff = "dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2e_off.rvmat";
		frontReflectorMatOn = "dz\vehicles\wheeled\civiliansedan\data\civiliansedan_lights.rvmat";
		frontReflectorMatOff = "dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat";
		fuelCapacity = 55;
		fuelConsumption = 13;
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
			class Cargo1
			{
				actionSel = "seat_cargo1";
				proxyPos = "crewCargo1";
				getInPos = "pos_cargo1";
				getInDir = "pos_cargo1_dir";
			};
			class Cargo2
			{
				actionSel = "seat_cargo2";
				proxyPos = "crewCargo2";
				getInPos = "pos_cargo2";
				getInDir = "pos_cargo2_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_RWD";
			airDragCoefficient = 0.928;
			class Steering
			{
				increaseSpeed[] = {0,45,30,30,60,20,120,5};
				decreaseSpeed[] = {0,45,60,20,120,8};
				centeringSpeed[] = {0,0,15,26,60,43,100,65};
			};
			class Throttle
			{
				reactionTime = 0.25;
				defaultThrust = 0.8;
				gentleThrust = 0.6;
				turboCoef = 5.0;
				gentleCoef = 0.7;
			};
			class Engine
			{
				inertia = 0.45;
				torqueMax = 187;
				torqueRpm = 2400;
				powerMax = 73.5;
				powerRpm = 4500;
				rpmIdle = 1000;
				rpmMin = 1050;
				rpmClutch = 1250;
				rpmRedline = 4700;
				rpmMax = 6800;
			};
			class Gearbox
			{
				reverse = 3.51;
				ratios[] = {3.5,2.26,1.45,1.0};
				timeToUncoupleClutch = 0.3;
				timeToCoupleClutch = 0.3;
				maxClutchTorque = 180;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 35;
					brakeBias = 0.7;
					brakeForce = 4500;
					wheelHubMass = 10;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 300;
						stiffness = 60000;
						compression = 2100;
						damping = 5500;
						travelMaxUp = 0.079;
						travelMaxDown = 0.06;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "CivSedanWheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "CivSedanWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					brakeBias = 0.3;
					brakeForce = 3500;
					finalRatio = 4.1;
					wheelHubMass = 10;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 275;
						stiffness = 34000;
						compression = 2000;
						damping = 5100;
						travelMaxUp = 0.086;
						travelMaxDown = 0.133;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "CivSedanWheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "CivSedanWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {10,40};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsCargo1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCargo2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class damper_1_1
			{
				source = "user";
				initPhase = 0.4857;
				animPeriod = 1;
			};
			class damper_2_1: damper_1_1{};
			class damper_1_2
			{
				source = "user";
				initPhase = 0.5936;
				animPeriod = 1;
			};
			class damper_2_2: damper_1_2{};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					class Health
					{
						hitpoints = 3000;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Front
				{
					class Health
					{
						hitpoints = 1500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat.rvmat"}},{0.7,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat.rvmat"}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_1","Fender_2_1","Engine","WindowFront"};
					transferToZonesThreshold[] = {0.5,0.5,0.5,0.1};
					transferToZonesCoefs[] = {0.7,0.7,0.5,0.05};
					memoryPoints[] = {"dmgZone_front"};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {0.3,0.3};
					inventorySlots[] = {"CivSedanHood","CarRadiator"};
				};
				class Reflector_1_1
				{
					class Health
					{
						hitpoints = 10;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\glass_i_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\glass_i_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Front","Fender_1_1","Engine"};
					transferToZonesCoefs[] = {0.1,0.15,0.05};
					memoryPoints[] = {"dmgZone_lights_1_1"};
					componentNames[] = {"dmgZone_lights_1_1"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {1.0};
					inventorySlots[] = {"Reflector_1_1"};
				};
				class Reflector_2_1: Reflector_1_1
				{
					transferToZonesNames[] = {"Front","Fender_2_1","Engine"};
					transferToZonesCoefs[] = {0.1,0.15,0.05};
					memoryPoints[] = {"dmgZone_lights_2_1"};
					componentNames[] = {"dmgZone_lights_2_1"};
					inventorySlotsCoefs[] = {1.0};
					inventorySlots[] = {"Reflector_2_1"};
				};
				class Back
				{
					class Health
					{
						hitpoints = 1500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat.rvmat"}},{0.7,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat.rvmat"}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_2","Fender_2_2","WindowBack"};
					transferToZonesCoefs[] = {0.3,0.3,0.2};
					memoryPoints[] = {"dmgZone_back"};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"CivSedanTrunk"};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 700;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.7,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_roof"};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Fender_1_1
				{
					class Health
					{
						hitpoints = 1200;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.7,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi.rvmat"}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_multi_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Front","Engine","Reflector_1_1","WindowFront"};
					transferToZonesThreshold[] = {0.2,0.5,0.9,0.5};
					transferToZonesCoefs[] = {0.3,0.6,0.6,0.4};
					memoryPoints[] = {"dmgZone_fender_1_1"};
					componentNames[] = {"dmgZone_fender_1_1"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {0.3,0.3,0.3};
					inventorySlots[] = {"CivSedanHood","CivSedanWheel_1_1","CivSedanDriverDoors"};
				};
				class Fender_1_2: Fender_1_1
				{
					transferToZonesNames[] = {"Back","FuelTank","WindowBack"};
					transferToZonesThreshold[] = {0.2,0.2,0.2};
					transferToZonesCoefs[] = {0.3,0.2,0.7};
					memoryPoints[] = {"dmgZone_fender_1_2"};
					componentNames[] = {"dmgZone_fender_1_2"};
					inventorySlotsCoefs[] = {0.3,0.1};
					inventorySlots[] = {"CivSedanTrunk","CivSedanWheel_1_2"};
				};
				class Fender_2_1: Fender_1_1
				{
					transferToZonesNames[] = {"Front","Engine","Reflector_2_1","WindowFront","Battery"};
					transferToZonesThreshold[] = {0.2,0.5,0.9,0.5,0.5};
					transferToZonesCoefs[] = {0.3,0.6,0.6,0.4,0.7};
					memoryPoints[] = {"dmgZone_fender_2_1"};
					componentNames[] = {"dmgZone_fender_2_1"};
					inventorySlotsCoefs[] = {0.3,0.2,31};
					inventorySlots[] = {"CivSedanHood","CivSedanWheel_2_1","CivSedanDriverDoors"};
				};
				class Fender_2_2: Fender_1_1
				{
					transferToZonesNames[] = {"Back","FuelTank","WindowBack"};
					transferToZonesThreshold[] = {0.2,0.2,0.2};
					transferToZonesCoefs[] = {0.3,0.2,0.7};
					memoryPoints[] = {"dmgZone_fender_2_2"};
					componentNames[] = {"dmgZone_fender_2_2"};
					inventorySlotsCoefs[] = {0.3,0.1};
					inventorySlots[] = {"CivSedanTrunk","CivSedanWheel_2_2"};
				};
				class WindowFront
				{
					class Health
					{
						hitpoints = 150;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\civiliansedan\data\glass.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\civiliansedan\data\glass.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\civiliansedan\data\glass_destruct.rvmat","dz\vehicles\wheeled\civiliansedan\data\glass_i_destruct.rvmat"}},{0.0,"hidden"}};
					};
					memoryPoints[] = {"dmgZone_windowFront"};
					componentNames[] = {"dmgZone_windowFront"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class WindowBack: WindowFront
				{
					componentNames[] = {"dmgZone_windowBack"};
					memoryPoints[] = {"dmgZone_windowBack"};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_engine"};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 0.001;
					inventorySlotsCoefs[] = {0.2,0.2,0.01,0.4};
					inventorySlots[] = {"CarBattery","SparkPlug","EngineBelt","CarRadiator"};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 600;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.8};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.8};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","CivSedanHood","CivSedanTrunk","CivSedanDriverDoors","CivSedanCoDriverDoors","CivSedanCargo1Doors","CivSedanCargo2Doors"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2","CivSedanWheel_Spare_1"};
			};
		};
	};
	class CivVanWheel: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVan_wheel.p3d";
		displayName = "$STR_CivVanWheel0";
		descriptionShort = "$STR_CivVanWheel1";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
		SingleUseActions[] = {548};
		simulation = "carwheel";
		radiusByDamage[] = {0,0.34,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.34;
		friction = 0.96;
		width = 0.16;
	};
	class CivVanWheel_Ruined: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVan_wheel_dam.p3d";
		displayName = "$STR_CivVanWheel_Ruined0";
		descriptionShort = "$STR_CivVanWheel_Ruined1";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
		simulation = "carwheel";
		radius = 0.15;
		friction = -1.0;
		width = 0.2;
	};
	class CivVanDoors_Driver: CarDoor
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Driver.p3d";
		displayName = "$STR_CivVanDoors_Driver0";
		descriptionShort = "$STR_CivVanDoors_Driver1";
		itemSize[] = {10,8};
		weight = 15000;
		physLayer = "item_large";
		inventorySlot = "CivVanDriverDoors";
		rotationFlags = 2;
	};
	class CivVanDoors_CoDriver: CivVanDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_CoDriver.p3d";
		displayName = "$STR_CivVanDoors_CoDriver0";
		inventorySlot = "CivVanCoDriverDoors";
		rotationFlags = 2;
	};
	class CivVanDoors_BackRight: CivVanDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo1.p3d";
		displayName = "$STR_CivVanDoors_BackRight0";
		inventorySlot = "CivVanCargo1Doors";
	};
	class CivVanDoors_TrunkDown: CivVanDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo2.p3d";
		displayName = "$STR_CivVanDoors_TrunkDown0";
		inventorySlot = "CivVanTrunkDown";
		rotationFlags = 2;
	};
	class CivVanDoors_TrunkUp: CivVanDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		displayName = "$STR_CivVanDoors_TrunkUp0";
		inventorySlot = "CivVanTrunkUp";
		rotationFlags = 2;
	};
	class CivVanTrunk: Inventory_Base
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		displayName = "$STR_CivVanTrunk0";
		descriptionShort = "$STR_CivVanTrunk1";
		itemSize[] = {12,10};
		weight = 15000;
		physLayer = "item_large";
		inventorySlot = "CivVanTrunk";
		rotationFlags = 4;
		class Damage
		{
			tex[] = {};
			mat[] = {"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan.rvmat","DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat","DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat"};
		};
	};
	class CivilianVan: CarScript
	{
		scope = 2;
		displayName = "$STR_CivilianVan0";
		model = "\dz\vehicles\wheeled\CivilianVan\CivilianVan.p3d";
		dashboardMatOn = "dz\vehicles\wheeled\CivilianVan\data\niva_dashboard_light.rvmat";
		dashboardMatOff = "dz\vehicles\wheeled\CivilianVan\data\niva_dashboard.rvmat";
		frontReflectorMatOn = "dz\vehicles\wheeled\CivilianVan\data\niva_lights.rvmat";
		frontReflectorMatOff = "dz\vehicles\wheeled\CivilianVan\data\niva.rvmat";
		frontReflectorMatDamaged = "dz\vehicles\wheeled\CivilianVan\data\niva_damage.rvmat";
		frontReflectorMatRuined = "dz\vehicles\wheeled\CivilianVan\data\niva_destruct.rvmat";
		fuelCapacity = 42;
		fuelConsumption = 11;
		attachments[] = {"CarBattery","Reflector_1_1","Reflector_2_1","CarRadiator","SparkPlug","CivVanDriverDoors","CivVanCoDriverDoors","CivVanCargo1Doors","CivVanTrunkDown","CivVanTrunkUp","CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
			class Cargo1
			{
				actionSel = "seat_cargo1";
				proxyPos = "crewCargo1";
				getInPos = "pos_driver";
				getInDir = "pos_driver_dir";
			};
			class Cargo2
			{
				actionSel = "seat_cargo2";
				proxyPos = "crewCargo2";
				getInPos = "pos_coDriver";
				getInDir = "pos_coDriver_dir";
			};
			class Cargo3
			{
				actionSel = "seat_cargo3";
				proxyPos = "crewCargo3";
				getInPos = "pos_coDriver";
				getInDir = "pos_coDriver_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_RWD";
			airDragCoefficient = 1.195;
			class Steering
			{
				increaseSpeed[] = {0,45,60,25,100,15};
				decreaseSpeed[] = {0,90,60,45,100,15};
				centeringSpeed[] = {0,0,15,28,60,45,100,60};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 2.5;
				gentleCoef = 0.75;
			};
			class Engine
			{
				inertia = 0.15;
				torqueMax = 114;
				torqueRpm = 3400;
				powerMax = 53.7;
				powerRpm = 5400;
				rpmIdle = 850;
				rpmMin = 900;
				rpmClutch = 1350;
				rpmRedline = 6000;
				rpmMax = 8000;
			};
			class Gearbox
			{
				reverse = 3.526;
				ratios[] = {3.667,2.1,1.361,1.0};
				timeToUncoupleClutch = 0.35;
				timeToCoupleClutch = 0.45;
				maxClutchTorque = 75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 30;
					finalRatio = 4.1;
					brakeBias = 0.5;
					brakeForce = 4500;
					wheelHubMass = 5;
					wheelHubRadius = 0.12;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 42000;
						compression = 2100;
						damping = 7500;
						travelMaxUp = 0.0882;
						travelMaxDown = 0.0833;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "CivVanwheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "CivVanwheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 4.1;
					brakeBias = 0.4;
					brakeForce = 3800;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1800;
						stiffness = 43000;
						compression = 2300;
						damping = 7900;
						travelMaxUp = 0.1587;
						travelMaxDown = 0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "CivVanWheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "CivVanWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {7,10};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
				};
			};
			class DamageZones
			{
				class Front
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Back
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LF
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_fenderLF"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderLR"};
				};
				class Fender_RF: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRF"};
				};
				class Fender_RR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRR"};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 400;
						transferToGlobalCoef = 1;
					};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Chassis
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
		class AnimationSources: AnimationSources
		{
			class DoorsCargo1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCargo2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCargo3
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
		};
		class Sounds
		{
			thrust = 0.6;
			thrustTurbo = 1;
			thrustGentle = 0.3;
			thrustSmoothCoef = 0.02;
			camposSmoothCoef = 0.03;
			soundSetsFilter[] = {"offroad_Engine_Offload_Ext_Rpm1_SoundSet","offroad_Engine_Offload_Ext_Rpm2_SoundSet","offroad_Engine_Offload_Ext_Rpm3_SoundSet","offroad_Engine_Offload_Ext_Rpm4_SoundSet","offroad_Engine_Offload_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Rpm0_SoundSet","offroad_Engine_Ext_Rpm1_SoundSet","offroad_Engine_Ext_Rpm2_SoundSet","offroad_Engine_Ext_Rpm3_SoundSet","offroad_Engine_Ext_Rpm4_SoundSet","offroad_Engine_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Broken_SoundSet","offroad_Tires_rock_slow_Ext_SoundSet","offroad_Tires_rock_fast_Ext_SoundSet","offroad_Tires_grass_slow_Ext_SoundSet","offroad_Tires_grass_fast_Ext_SoundSet","offroad_Tires_gravel_slow_Ext_SoundSet","offroad_Tires_gravel_fast_Ext_SoundSet","offroad_Tires_gravel_dust_fast_Ext_SoundSet","offroad_Tires_asphalt_slow_Ext_SoundSet","offroad_Tires_asphalt_fast_Ext_SoundSet","offroad_Tires_water_slow_Ext_SoundSet","offroad_Tires_water_fast_Ext_SoundSet","Offroad_skid_dirt_SoundSet","offroad_dirt_turn_SoundSet","offroad_Rain_Ext_SoundSet","offroad_damper_left_SoundSet","offroad_damper_right_SoundSet"};
			soundSetsInt[] = {"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet","Offroad_Wind_SoundSet"};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.7};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.7};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
				icon = "cat_vehicle_engine";
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","CivVanDriverDoors","CivVanCoDriverDoors","CivVanCargo1Doors","CivVanTrunkDown","CivVanTrunkUp"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
			};
		};
	};
	class HatchbackWheel: CarWheel
	{
		scope = 2;
		displayName = "$STR_HatchbackWheel0";
		descriptionShort = "$STR_hatchbackwheel1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
		weight = 15000;
		itemSize[] = {6,6};
		itemBehaviour = 0;
		inventorySlot[] = {"NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2","NivaWheel_Spare_1"};
		rotationFlags = 4;
		physLayer = "item_large";
		repairableWithKits[] = {6};
		repairCosts[] = {30.0};
		radiusByDamage[] = {0,0.362,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.35;
		width = 0.18;
		tyreRollResistance = 0.015;
		tyreTread = 0.8;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel.rvmat"}},{0.7,{"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel.rvmat"}},{0.5,{"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel_damage.rvmat"}},{0.3,{"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel_damage.rvmat"}},{0.0,{"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel_destruct.rvmat"}}};
				};
			};
		};
	};
	class HatchbackWheel_Ruined: CarWheel
	{
		scope = 2;
		displayName = "$STR_HatchbackWheel0";
		descriptionShort = "$STR_hatchbackwheel1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel_destroyed.p3d";
		weight = 10000;
		itemSize[] = {6,6};
		itemBehaviour = 0;
		inventorySlot[] = {"NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2","NivaWheel_Spare_1"};
		rotationFlags = 4;
		physLayer = "item_large";
		radius = 0.2;
		width = 0.17;
		tyreRollResistance = 1;
		tyreRollDrag = 70;
		tyreRoughness = 1;
		tyreTread = 0.5;
	};
	class HatchbackDoors_Driver: CarDoor
	{
		scope = 2;
		displayName = "$STR_HatchbackDoors_Driver0";
		descriptionShort = "$STR_HatchbackDoors_Driver1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Driver.p3d";
		weight = 15000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot = "NivaDriverDoors";
		rotationFlags = 8;
		physLayer = "item_large";
		class DamageSystem: DamageSystem
		{
			class GlobalHealth: GlobalHealth{};
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_destruct.rvmat"}},{0.0,"hidden"}};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_door.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_door_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_door_destruct.rvmat"}}};
					};
				};
			};
		};
	};
	class HatchbackDoors_CoDriver: HatchbackDoors_Driver
	{
		displayName = "$STR_HatchbackDoors_CoDriver0";
		descriptionShort = "$STR_HatchbackDoors_CoDriver1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_coDriver.p3d";
		itemBehaviour = 0;
		inventorySlot = "NivaCoDriverDoors";
		rotationFlags = 4;
	};
	class HatchbackHood: CarDoor
	{
		scope = 2;
		displayName = "$STR_HatchbackHood0";
		descriptionShort = "$STR_HatchbackHood1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Hood.p3d";
		weight = 15000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot = "NivaHood";
		rotationFlags = 2;
		physLayer = "item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_hood.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_hood_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_hood_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUp
				{
					soundSet = "hatchbackdoors_driver_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "hatchbackhood_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class HatchbackTrunk: CarDoor
	{
		scope = 2;
		displayName = "$STR_HatchbackTrunk0";
		descriptionShort = "$STR_HatchbackTrunk1";
		model = "\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Trunk.p3d";
		weight = 15000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		inventorySlot = "NivaTrunk";
		rotationFlags = 1;
		physLayer = "item_large";
		class DamageSystem: DamageSystem
		{
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_destruct.rvmat"}},{0.0,"hidden"}};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor_destruct.rvmat"}}};
					};
				};
			};
		};
	};
	class OffroadHatchback: CarScript
	{
		scope = 2;
		displayName = "$STR_OffroadHatchback0";
		descriptionShort = "$STR_OffroadHatchback1";
		model = "\dz\vehicles\wheeled\OffroadHatchback\OffroadHatchback.p3d";
		InteractActions[] = {1048,1035};
		attachments[] = {"CarBattery","Reflector_1_1","Reflector_2_1","CarRadiator","SparkPlug","NivaDriverDoors","NivaCoDriverDoors","NivaHood","NivaTrunk","NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2","NivaWheel_Spare_1"};
		dashboardMatOn = "dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard_light.rvmat";
		dashboardMatOff = "dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard.rvmat";
		frontReflectorMatOn = "dz\vehicles\wheeled\offroadhatchback\data\niva_lights.rvmat";
		frontReflectorMatOff = "dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat";
		fuelCapacity = 42;
		fuelConsumption = 11;
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
			class Cargo1
			{
				actionSel = "seat_cargo1";
				proxyPos = "crewCargo1";
				getInPos = "pos_driver";
				getInDir = "pos_driver_dir";
			};
			class Cargo2
			{
				actionSel = "seat_cargo2";
				proxyPos = "crewCargo2";
				getInPos = "pos_coDriver";
				getInDir = "pos_coDriver_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_AWD";
			airDragCoefficient = 0.995;
			class Steering
			{
				increaseSpeed[] = {0,45,60,23,100,12};
				decreaseSpeed[] = {0,80,60,40,90,20};
				centeringSpeed[] = {0,0,15,25,60,40,100,60};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 4.0;
				gentleCoef = 0.75;
			};
			class Engine
			{
				inertia = 0.15;
				torqueMax = 114;
				torqueRpm = 3400;
				powerMax = 53.7;
				powerRpm = 5400;
				rpmIdle = 850;
				rpmMin = 900;
				rpmClutch = 1350;
				rpmRedline = 6000;
				rpmMax = 8000;
			};
			class Gearbox
			{
				reverse = 3.526;
				ratios[] = {3.667,2.1,1.361,1.0};
				timeToUncoupleClutch = 0.3;
				timeToCoupleClutch = 0.45;
				maxClutchTorque = 260;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 30;
					finalRatio = 4.1;
					brakeBias = 0.6;
					brakeForce = 4000;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 40000;
						compression = 2100;
						damping = 7500;
						travelMaxUp = 0.0882;
						travelMaxDown = 0.0833;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "NivaWheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "NivaWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 4.1;
					brakeBias = 0.4;
					brakeForce = 3800;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1800;
						stiffness = 40000;
						compression = 2200;
						damping = 7600;
						travelMaxUp = 0.1587;
						travelMaxDown = 0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "NivaWheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "NivaWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {10,30};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class SeatDriver
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.8;
			};
			class SeatCoDriver
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.8;
			};
			class damper_1_1
			{
				source = "user";
				initPhase = 0.4857;
				animPeriod = 1;
			};
			class damper_2_1: damper_1_1{};
			class damper_1_2
			{
				source = "user";
				initPhase = 0.4002;
				animPeriod = 1;
			};
			class damper_2_2: damper_1_2{};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					class Health
					{
						hitpoints = 3000;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Front
				{
					class Health
					{
						hitpoints = 1500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_1","Fender_2_1","Engine","WindowFront"};
					transferToZonesThreshold[] = {0.5,0.5,0.5,0.1};
					transferToZonesCoefs[] = {0.7,0.7,0.5,0.05};
					memoryPoints[] = {"dmgZone_front"};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {0.3,0.3};
					inventorySlots[] = {"NivaHood","CarRadiator"};
				};
				class Reflector_1_1
				{
					class Health
					{
						hitpoints = 10;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\glass_i_damage.rvmat"}},{0.3,{}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\glass_i_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Front","Fender_1_1","Engine"};
					transferToZonesCoefs[] = {0.1,0.15,0.05};
					memoryPoints[] = {"dmgZone_lights_1_1"};
					componentNames[] = {"dmgZone_lights_1_1"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {1.0};
					inventorySlots[] = {"Reflector_1_1"};
				};
				class Reflector_2_1: Reflector_1_1
				{
					transferToZonesNames[] = {"Front","Fender_2_1","Engine"};
					transferToZonesCoefs[] = {0.1,0.15,0.05};
					memoryPoints[] = {"dmgZone_lights_2_1"};
					componentNames[] = {"dmgZone_lights_2_1"};
					inventorySlotsCoefs[] = {1.0};
					inventorySlots[] = {"Reflector_2_1"};
				};
				class Back
				{
					class Health
					{
						hitpoints = 1500;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Fender_1_2","Fender_2_2","WindowLR","WindowRR"};
					transferToZonesCoefs[] = {0.3,0.3,0.2,0.2};
					memoryPoints[] = {"dmgZone_back"};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"NivaTrunk"};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 700;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_roof"};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class Fender_1_1
				{
					class Health
					{
						hitpoints = 1200;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"}}};
					};
					transferToZonesNames[] = {"Front","Engine","Reflector_1_1","WindowFront"};
					transferToZonesThreshold[] = {0.2,0.5,0.9,0.5};
					transferToZonesCoefs[] = {0.3,0.6,0.6,0.4};
					memoryPoints[] = {"dmgZone_fender_1_1"};
					componentNames[] = {"dmgZone_fender_1_1"};
					fatalInjuryCoef = -1;
					inventorySlotsCoefs[] = {0.3,0.3,0.3};
					inventorySlots[] = {"NivaHood","NivaWheel_1_1","NivaDriverDoors"};
				};
				class Fender_1_2: Fender_1_1
				{
					transferToZonesNames[] = {"Back","FuelTank","WindowLR"};
					transferToZonesThreshold[] = {0.2,0.2,0.2};
					transferToZonesCoefs[] = {0.3,0.2,0.7};
					memoryPoints[] = {"dmgZone_fender_1_2"};
					componentNames[] = {"dmgZone_fender_1_2"};
					inventorySlotsCoefs[] = {0.3,0.1};
					inventorySlots[] = {"NivaTrunk","NivaWheel_1_2"};
				};
				class Fender_2_1: Fender_1_1
				{
					transferToZonesNames[] = {"Front","Engine","Reflector_2_1","WindowFront","Battery"};
					transferToZonesThreshold[] = {0.2,0.5,0.9,0.5,0.5};
					transferToZonesCoefs[] = {0.3,0.6,0.6,0.4,0.7};
					memoryPoints[] = {"dmgZone_fender_2_1"};
					componentNames[] = {"dmgZone_fender_2_1"};
					inventorySlotsCoefs[] = {0.3,0.2,31};
					inventorySlots[] = {"NivaHood","NivaWheel_2_1","NivaDriverDoors"};
				};
				class Fender_2_2: Fender_1_1
				{
					transferToZonesNames[] = {"Back","FuelTank","WindowRR"};
					transferToZonesThreshold[] = {0.2,0.2,0.2};
					transferToZonesCoefs[] = {0.3,0.2,0.7};
					memoryPoints[] = {"dmgZone_fender_2_2"};
					componentNames[] = {"dmgZone_fender_2_2"};
					inventorySlotsCoefs[] = {0.3,0.1};
					inventorySlots[] = {"NivaTrunk","NivaWheel_2_2"};
				};
				class WindowFront
				{
					class Health
					{
						hitpoints = 150;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_destruct.rvmat"}},{0.0,"hidden"}};
					};
					memoryPoints[] = {"dmgZone_windowFront"};
					componentNames[] = {"dmgZone_windowFront"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class WindowLR
				{
					class Health
					{
						hitpoints = 150;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"}},{0.7,{}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\niva_glass_destruct.rvmat"}},{0.0,"hidden"}};
					};
					memoryPoints[] = {"dmgZone_windowLeft"};
					componentNames[] = {"dmgZone_windowLeft"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class WindowRR: WindowLR
				{
					memoryPoints[] = {"dmgZone_windowRight"};
					componentNames[] = {"dmgZone_windowRight"};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva.rvmat"}},{0.7,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva.rvmat"}},{0.5,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_damage.rvmat"}},{0.3,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_damage.rvmat"}},{0.0,{"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_destruct.rvmat"}}};
					};
					memoryPoints[] = {"dmgZone_engine"};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 0.001;
					inventorySlotsCoefs[] = {0.2,0.2,0.01,0.4};
					inventorySlots[] = {"CarBattery","SparkPlug","EngineBelt","CarRadiator"};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 600;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.7};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.7};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","NivaHood","NivaTrunk","NivaDriverDoors","NivaCoDriverDoors","NivaWheel_Spare_1"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2"};
			};
		};
	};
	class CivHatchbackWheel: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Wheel.p3d";
		displayName = "Civilian Hatchback Wheel";
		descriptionShort = "Wheel";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
		SingleUseActions[] = {548};
		simulation = "carwheel";
		radiusByDamage[] = {0,0.34,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.34;
		friction = 0.96;
		width = 0.16;
	};
	class CivHatchbackWheel_Ruined: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivHatchback_wheel_dam.p3d";
		displayName = "Civilian Hatchback Wheel";
		descriptionShort = "Wheel";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
		simulation = "carwheel";
		radius = 0.15;
		friction = -1.0;
		width = 0.2;
	};
	class CivHatchbackDoors_Driver: CarDoor
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_FL.p3d";
		displayName = "Civilian Hatchback Right Doors";
		descriptionShort = "Car Doors";
		itemSize[] = {10,8};
		weight = 15000;
		physLayer = "item_large";
		inventorySlot = "CivHatchbackDriverDoors";
		rotationFlags = 2;
	};
	class CivHatchbackDoors_CoDriver: CivHatchbackDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_FR.p3d";
		displayName = "Civilian Hatchback Left Doors";
		descriptionShort = "Car Doors";
		inventorySlot = "CivHatchbackCoDriverDoors";
		rotationFlags = 2;
	};
	class CivHatchbackDoors_Cargo01: CivHatchbackDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_BL.p3d";
		displayName = "Civilian Hatchback Back Left Doors";
		descriptionShort = "Car Doors";
		inventorySlot = "CivHatchbackCargo1Doors";
		rotationFlags = 2;
	};
	class CivHatchbackDoors_Cargo02: CivHatchbackDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_BR.p3d";
		displayName = "Civilian Hatchback Back Right Doors";
		descriptionShort = "Car Doors";
		inventorySlot = "CivHatchbackCargo2Doors";
		rotationFlags = 2;
	};
	class CivHatchbackDoors_Hood: CivHatchbackDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Hood.p3d";
		displayName = "Civilian Hatchback Hood";
		descriptionShort = "Car Hood";
		inventorySlot = "CivHatchbackHood";
		rotationFlags = 2;
	};
	class CivHatchbackDoors_Trunk: CivHatchbackDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Trunk.p3d";
		displayName = "Civilian Hatchback Trunk";
		descriptionShort = "Car Trunk";
		inventorySlot = "CivHatchbackTrunk";
		rotationFlags = 2;
	};
	class CivilianHatchback: CarScript
	{
		scope = 2;
		displayName = "Civilian Hatchback";
		descriptionShort = "Civ Hatchback";
		model = "\dz\vehicles\wheeled\CivilianHatchback\CivilianHatchback.p3d";
		dashboardMatOn = "";
		dashboardMatOff = "";
		frontReflectorMatOn = "";
		frontReflectorMatOff = "";
		frontReflectorMatDamaged = "";
		frontReflectorMatRuined = "";
		fuelCapacity = 42;
		fuelConsumption = 11;
		attachments[] = {"CarBattery","Reflector_1_1","Reflector_2_1","CarRadiator","SparkPlug","CivHatchbackDriverDoors","CivHatchbackCoDriverDoors","CivHatchbackCargo1Doors","CivHatchbackCargo2Doors","CivHatchbackTrunk","CivHatchbackHood","CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
			class Cargo1
			{
				actionSel = "seat_cargo1";
				proxyPos = "crewCargo1";
				getInPos = "pos_driver";
				getInDir = "pos_driver_dir";
			};
			class Cargo2
			{
				actionSel = "seat_cargo2";
				proxyPos = "crewCargo2";
				getInPos = "pos_coDriver";
				getInDir = "pos_coDriver_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_RWD";
			airDragCoefficient = 1.195;
			class Steering
			{
				increaseSpeed[] = {0,45,60,25,100,15};
				decreaseSpeed[] = {0,90,60,45,100,15};
				centeringSpeed[] = {0,0,15,28,60,45,100,60};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 2.5;
				gentleCoef = 0.75;
			};
			class Engine
			{
				inertia = 0.15;
				torqueMax = 114;
				torqueRpm = 3400;
				powerMax = 53.7;
				powerRpm = 5400;
				rpmIdle = 850;
				rpmMin = 900;
				rpmClutch = 1350;
				rpmRedline = 6000;
				rpmMax = 8000;
			};
			class Gearbox
			{
				reverse = 3.526;
				ratios[] = {3.667,2.1,1.361,1.0};
				timeToUncoupleClutch = 0.35;
				timeToCoupleClutch = 0.45;
				maxClutchTorque = 75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 30;
					finalRatio = 4.1;
					brakeBias = 0.5;
					brakeForce = 4500;
					wheelHubMass = 5;
					wheelHubRadius = 0.12;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 42000;
						compression = 2100;
						damping = 7500;
						travelMaxUp = 0.0882;
						travelMaxDown = 0.0833;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "CivHatchbackWheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "CivHatchbackWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 4.1;
					brakeBias = 0.4;
					brakeForce = 3800;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1800;
						stiffness = 43000;
						compression = 2300;
						damping = 7900;
						travelMaxUp = 0.1587;
						travelMaxDown = 0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "CivHatchbackWheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "CivHatchbackWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {7,10};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsCargo1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCargo2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
				};
			};
			class DamageZones
			{
				class Front
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Back
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LF
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_fenderLF"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderLR"};
				};
				class Fender_RF: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRF"};
				};
				class Fender_RR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRR"};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 400;
						transferToGlobalCoef = 1;
					};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {"hull"};
				};
				class Chassis
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"hull"};
				};
			};
		};
		class Sounds
		{
			thrust = 0.6;
			thrustTurbo = 1;
			thrustGentle = 0.3;
			thrustSmoothCoef = 0.02;
			camposSmoothCoef = 0.03;
			soundSetsFilter[] = {"offroad_Engine_Offload_Ext_Rpm1_SoundSet","offroad_Engine_Offload_Ext_Rpm2_SoundSet","offroad_Engine_Offload_Ext_Rpm3_SoundSet","offroad_Engine_Offload_Ext_Rpm4_SoundSet","offroad_Engine_Offload_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Rpm0_SoundSet","offroad_Engine_Ext_Rpm1_SoundSet","offroad_Engine_Ext_Rpm2_SoundSet","offroad_Engine_Ext_Rpm3_SoundSet","offroad_Engine_Ext_Rpm4_SoundSet","offroad_Engine_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Broken_SoundSet","offroad_Tires_rock_slow_Ext_SoundSet","offroad_Tires_rock_fast_Ext_SoundSet","offroad_Tires_grass_slow_Ext_SoundSet","offroad_Tires_grass_fast_Ext_SoundSet","offroad_Tires_gravel_slow_Ext_SoundSet","offroad_Tires_gravel_fast_Ext_SoundSet","offroad_Tires_gravel_dust_fast_Ext_SoundSet","offroad_Tires_asphalt_slow_Ext_SoundSet","offroad_Tires_asphalt_fast_Ext_SoundSet","offroad_Tires_water_slow_Ext_SoundSet","offroad_Tires_water_fast_Ext_SoundSet","Offroad_skid_dirt_SoundSet","offroad_dirt_turn_SoundSet","offroad_Rain_Ext_SoundSet","offroad_damper_left_SoundSet","offroad_damper_right_SoundSet"};
			soundSetsInt[] = {"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet","Offroad_Wind_SoundSet"};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.7};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.7};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","CivHatchbackDriverDoors","CivHatchbackCoDriverDoors","CivHatchbackCargo1Doors","CivHatchbackCargo2Doors","CivHatchbackHood","CivHatchbackTrunk"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
			};
		};
	};
	class UtilityVehicleWheel: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_Wheel.p3d";
		displayName = "Utility Vehicle Wheel";
		descriptionShort = "Wheel";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
		SingleUseActions[] = {548};
		simulation = "carwheel";
		radiusByDamage[] = {0,0.34,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.34;
		friction = 0.96;
		width = 0.16;
	};
	class UtilityVehicleWheel_Ruined: CarWheel
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\UtilityVehicle\proxy\CivHatchback_wheel_destroyed.p3d";
		displayName = "Utility Vehicle Wheel";
		descriptionShort = "Wheel";
		itemSize[] = {6,6};
		weight = 12000;
		physLayer = "item_large";
		rotationFlags = 4;
		inventorySlot[] = {"UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
		simulation = "carwheel";
		radius = 0.15;
		friction = -1.0;
		width = 0.2;
	};
	class UtilityVehicleDoors_Driver: CarDoor
	{
		scope = 2;
		model = "\DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_DoorL.p3d";
		displayName = "Utility Vehicle Left Doors";
		descriptionShort = "Doors";
		itemSize[] = {10,8};
		weight = 15000;
		physLayer = "item_large";
		inventorySlot = "UtilityVehicleDriverDoors";
		rotationFlags = 2;
	};
	class UtilityVehicleDoors_CoDriver: UtilityVehicleDoors_Driver
	{
		model = "\DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_DoorR.p3d";
		displayName = "Utility Vehicle Right Doors";
		descriptionShort = "Doors";
		inventorySlot = "UtilityVehicleCoDriverDoors";
		rotationFlags = 2;
	};
	class UtilityVehicle: CarScript
	{
		scope = 2;
		displayName = "Utility Vehicle";
		descriptionShort = "Utility Vehicle";
		model = "\dz\vehicles\wheeled\UtilityVehicle\UtilityVehicle.p3d";
		dashboardMatOn = "";
		dashboardMatOff = "";
		frontReflectorMatOn = "";
		frontReflectorMatOff = "";
		frontReflectorMatDamaged = "";
		frontReflectorMatRuined = "";
		fuelCapacity = 42;
		fuelConsumption = 11;
		attachments[] = {"CarBattery","LightBulb","CarRadiator","SparkPlug","UtilityVehicleDriverDoors","UtilityVehicleCoDriverDoors","UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_RWD";
			airDragCoefficient = 1.195;
			class Steering
			{
				increaseSpeed[] = {0,45,60,25,100,15};
				decreaseSpeed[] = {0,90,60,45,100,15};
				centeringSpeed[] = {0,0,15,28,60,45,100,60};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 2.5;
				gentleCoef = 0.75;
			};
			class Engine
			{
				inertia = 0.15;
				torqueMax = 114;
				torqueRpm = 3400;
				powerMax = 53.7;
				powerRpm = 5400;
				rpmIdle = 850;
				rpmMin = 900;
				rpmClutch = 1350;
				rpmRedline = 6000;
				rpmMax = 8000;
			};
			class Gearbox
			{
				reverse = 3.526;
				ratios[] = {3.667,2.1,1.361,1.0};
				timeToUncoupleClutch = 0.35;
				timeToCoupleClutch = 0.45;
				maxClutchTorque = 75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 30;
					finalRatio = 4.1;
					brakeBias = 0.5;
					brakeForce = 4500;
					wheelHubMass = 5;
					wheelHubRadius = 0.12;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 42000;
						compression = 2100;
						damping = 7500;
						travelMaxUp = 0.0882;
						travelMaxDown = 0.0833;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "UtilityVehicleWheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "UtilityVehicleWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 4.1;
					brakeBias = 0.4;
					brakeForce = 3800;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1800;
						stiffness = 43000;
						compression = 2300;
						damping = 7900;
						travelMaxUp = 0.1587;
						travelMaxDown = 0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "UtilityVehicleWheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "UtilityVehicleWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {7,10};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
				};
			};
			class DamageZones
			{
				class Front
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_front"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Back
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_back"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Roof
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_roof"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LF
				{
					class Health
					{
						hitpoints = 500;
						transferToGlobalCoef = 0;
					};
					componentNames[] = {"dmgZone_fenderLF"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Fender_LR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderLR"};
				};
				class Fender_RF: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRF"};
				};
				class Fender_RR: Fender_LF
				{
					componentNames[] = {"dmgZone_fenderRR"};
				};
				class Engine
				{
					class Health
					{
						hitpoints = 400;
						transferToGlobalCoef = 1;
					};
					componentNames[] = {"dmgZone_engine"};
					fatalInjuryCoef = 1;
					inventorySlots[] = {};
				};
				class Chassis
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_chassis"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints = 1000;
						transferToGlobalCoef = -1;
					};
					componentNames[] = {"dmgZone_fuelTank"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {};
				};
			};
		};
		class Sounds
		{
			thrust = 0.6;
			thrustTurbo = 1;
			thrustGentle = 0.3;
			thrustSmoothCoef = 0.02;
			camposSmoothCoef = 0.03;
			soundSetsFilter[] = {"offroad_Engine_Offload_Ext_Rpm1_SoundSet","offroad_Engine_Offload_Ext_Rpm2_SoundSet","offroad_Engine_Offload_Ext_Rpm3_SoundSet","offroad_Engine_Offload_Ext_Rpm4_SoundSet","offroad_Engine_Offload_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Rpm0_SoundSet","offroad_Engine_Ext_Rpm1_SoundSet","offroad_Engine_Ext_Rpm2_SoundSet","offroad_Engine_Ext_Rpm3_SoundSet","offroad_Engine_Ext_Rpm4_SoundSet","offroad_Engine_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Broken_SoundSet","offroad_Tires_rock_slow_Ext_SoundSet","offroad_Tires_rock_fast_Ext_SoundSet","offroad_Tires_grass_slow_Ext_SoundSet","offroad_Tires_grass_fast_Ext_SoundSet","offroad_Tires_gravel_slow_Ext_SoundSet","offroad_Tires_gravel_fast_Ext_SoundSet","offroad_Tires_gravel_dust_fast_Ext_SoundSet","offroad_Tires_asphalt_slow_Ext_SoundSet","offroad_Tires_asphalt_fast_Ext_SoundSet","offroad_Tires_water_slow_Ext_SoundSet","offroad_Tires_water_fast_Ext_SoundSet","Offroad_skid_dirt_SoundSet","offroad_dirt_turn_SoundSet","offroad_Rain_Ext_SoundSet","offroad_damper_left_SoundSet","offroad_damper_right_SoundSet"};
			soundSetsInt[] = {"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet","Offroad_Wind_SoundSet"};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.7};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.7};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","UtilityVehicleDriverDoors","UtilityVehicleCoDriverDoors"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
			};
		};
	};
	class S120Wheel: CarWheel
	{
		scope = 2;
		displayName = "s120 Wheel";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_wheel.p3d";
		weight = 12000;
		itemSize[] = {6,6};
		inventorySlot[] = {"S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
		rotationFlags = 4;
		physLayer = "item_large";
		radiusByDamage[] = {0,0.34,0.3,0.3,0.9998,0.25,0.9999,0.2};
		radius = 0.34;
		friction = 0.96;
		width = 0.16;
	};
	class S120Wheel_Ruined: CarWheel
	{
		scope = 2;
		displayName = "s120 wheel";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_wheel_damaged.p3d";
		weight = 12000;
		itemSize[] = {6,6};
		inventorySlot[] = {"S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
		rotationFlags = 4;
		physLayer = "item_large";
		radius = 0.15;
		friction = -1.0;
		width = 0.2;
	};
	class S120Doors_Driver: CarDoor
	{
		scope = 2;
		displayName = "s120 Left Doors";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_doors_driver.p3d";
		weight = 15000;
		itemSize[] = {10,8};
		inventorySlot = "S120DriverDoors";
		rotationFlags = 8;
		physLayer = "item_large";
	};
	class S120Doors_CoDriver: S120Doors_Driver
	{
		displayName = "s120 Right Doors";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_doors_coDriver.p3d";
		inventorySlot = "S120CoDriverDoors";
		rotationFlags = 4;
	};
	class S120Doors_BackLeft: S120Doors_Driver
	{
		displayName = "s120 Back Left Doors";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_doors_cargo1.p3d";
		inventorySlot = "S120Cargo1Doors";
	};
	class S120Doors_BackRight: S120Doors_Driver
	{
		displayName = "s120 Back Right Doors";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_doors_cargo2.p3d";
		inventorySlot = "S120Cargo2Doors";
		rotationFlags = 4;
	};
	class S120Hood: CarDoor
	{
		scope = 2;
		displayName = "s120 Hood";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_hood.p3d";
		weight = 15000;
		itemSize[] = {12,10};
		inventorySlot = "S120Hood";
		rotationFlags = 4;
		physLayer = "item_large";
		class Damage
		{
			tex[] = {};
			mat[] = {"DZ\vehicles\wheeled\s120\data\s120.rvmat","DZ\vehicles\wheeled\s120\data\s120_damage.rvmat","DZ\vehicles\wheeled\s120\data\s120_destruct.rvmat"};
		};
	};
	class S120Trunk: CarDoor
	{
		scope = 2;
		displayName = "s120 Trunk";
		model = "\DZ\vehicles\wheeled\s120\proxy\s120_boot.p3d";
		weight = 15000;
		itemSize[] = {12,10};
		inventorySlot = "S120Trunk";
		rotationFlags = 4;
		physLayer = "item_large";
		class Damage
		{
			tex[] = {};
			mat[] = {"DZ\vehicles\wheeled\s120\data\s120.rvmat","DZ\vehicles\wheeled\s120\data\s120_damage.rvmat","DZ\vehicles\wheeled\s120\data\s120_destruct.rvmat"};
		};
	};
	class S120: CarScript
	{
		scope = 2;
		displayName = "s120";
		model = "\DZ\vehicles\wheeled\s120\s120.p3d";
		attachments[] = {"CarBattery","CarRadiator","LightBulb","EngineBelt","SparkPlug","S120Hood","S120Trunk","S120DriverDoors","S120CoDriverDoors","S120Cargo1Doors","S120Cargo2Doors","S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
		dashboardMatOn = "dz\vehicles\wheeled\s120\data\s120_int2e_.rvmat";
		dashboardMatOff = "dz\vehicles\wheeled\s120\data\s120_int2e_off.rvmat";
		frontReflectorMatOn = "dz\vehicles\wheeled\s120\data\s120_lights.rvmat";
		frontReflectorMatOff = "dz\vehicles\wheeled\s120\data\s120_cr.rvmat";
		frontReflectorMatDamaged = "dz\vehicles\wheeled\s120\data\s120_damage.rvmat";
		frontReflectorMatRuined = "dz\vehicles\wheeled\s120\data\s120_destruct.rvmat";
		fuelCapacity = 55;
		fuelConsumption = 15;
		airDragCoefficient = 0.75;
		class Crew: Crew
		{
			class Driver: Driver{};
			class CoDriver: CoDriver{};
			class Cargo1
			{
				actionSel = "seat_cargo1";
				proxyPos = "crewCargo1";
				getInPos = "pos_cargo1";
				getInDir = "pos_cargo1_dir";
			};
			class Cargo2
			{
				actionSel = "seat_cargo2";
				proxyPos = "crewCargo2";
				getInPos = "pos_cargo2";
				getInDir = "pos_cargo2_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive = "DRIVE_RWD";
			airDragCoefficient = 1.195;
			class Steering
			{
				increaseSpeed[] = {0,45,60,25,100,15};
				decreaseSpeed[] = {0,90,60,45,100,15};
				centeringSpeed[] = {0,0,15,28,60,45,100,60};
			};
			class Throttle
			{
				reactionTime = 1.0;
				defaultThrust = 0.85;
				gentleThrust = 0.7;
				turboCoef = 2.5;
				gentleCoef = 0.75;
			};
			class Engine
			{
				inertia = 0.15;
				torqueMax = 114;
				torqueRpm = 3400;
				powerMax = 53.7;
				powerRpm = 5400;
				rpmIdle = 850;
				rpmMin = 900;
				rpmClutch = 1350;
				rpmRedline = 6000;
				rpmMax = 8000;
			};
			class Gearbox
			{
				reverse = 3.54;
				ratios[] = {3.5,2.26,1.45,1.0};
				timeToUncoupleClutch = 0.2;
				timeToCoupleClutch = 0.1;
				maxClutchTorque = 75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle = 30;
					finalRatio = 4.1;
					brakeBias = 0.5;
					brakeForce = 4500;
					wheelHubMass = 5;
					wheelHubRadius = 0.12;
					class Suspension
					{
						swayBar = 1700;
						stiffness = 42000;
						compression = 2100;
						damping = 7500;
						travelMaxUp = 0.0882;
						travelMaxDown = 0.0833;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_1";
							inventorySlot = "S120Wheel_1_1";
						};
						class Right: Right
						{
							animDamper = "damper_2_1";
							inventorySlot = "S120Wheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle = 0;
					finalRatio = 4.1;
					brakeBias = 0.4;
					brakeForce = 3800;
					wheelHubMass = 5;
					wheelHubRadius = 0.15;
					class Suspension
					{
						swayBar = 1800;
						stiffness = 43000;
						compression = 2300;
						damping = 7900;
						travelMaxUp = 0.1587;
						travelMaxDown = 0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper = "damper_1_2";
							inventorySlot = "S120Wheel_1_2";
						};
						class Right: Right
						{
							animDamper = "damper_2_2";
							inventorySlot = "S120Wheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {7,12};
			allowOwnedCargoManipulation = 1;
			openable = 0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsCargo1
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
			class DoorsCargo2
			{
				source = "user";
				initPhase = 0;
				animPeriod = 0.5;
			};
		};
		class Sounds
		{
			thrust = 0.6;
			thrustTurbo = 1;
			thrustGentle = 0.3;
			thrustSmoothCoef = 0.02;
			camposSmoothCoef = 0.03;
			soundSetsFilter[] = {"offroad_Engine_Offload_Ext_Rpm1_SoundSet","offroad_Engine_Offload_Ext_Rpm2_SoundSet","offroad_Engine_Offload_Ext_Rpm3_SoundSet","offroad_Engine_Offload_Ext_Rpm4_SoundSet","offroad_Engine_Offload_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Rpm0_SoundSet","offroad_Engine_Ext_Rpm1_SoundSet","offroad_Engine_Ext_Rpm2_SoundSet","offroad_Engine_Ext_Rpm3_SoundSet","offroad_Engine_Ext_Rpm4_SoundSet","offroad_Engine_Ext_Rpm5_SoundSet","offroad_Engine_Ext_Broken_SoundSet","offroad_Tires_rock_slow_Ext_SoundSet","offroad_Tires_rock_fast_Ext_SoundSet","offroad_Tires_grass_slow_Ext_SoundSet","offroad_Tires_grass_fast_Ext_SoundSet","offroad_Tires_gravel_slow_Ext_SoundSet","offroad_Tires_gravel_fast_Ext_SoundSet","offroad_Tires_gravel_dust_fast_Ext_SoundSet","offroad_Tires_asphalt_slow_Ext_SoundSet","offroad_Tires_asphalt_fast_Ext_SoundSet","offroad_Tires_water_slow_Ext_SoundSet","offroad_Tires_water_fast_Ext_SoundSet","Offroad_skid_dirt_SoundSet","offroad_dirt_turn_SoundSet","offroad_Rain_Ext_SoundSet","offroad_damper_left_SoundSet","offroad_damper_right_SoundSet"};
			soundSetsInt[] = {"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet","Offroad_Wind_SoundSet"};
		};
		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5.0;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,0.8};
					};
					class Cyl3
					{
						radius = 1.0;
						height = 1.5;
						center[] = {0,0,-0.8};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery","CarRadiator","SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1","Reflector_2_1","S120DriverDoors","S120DriverDoors","S120Cargo1Doors","S120Cargo2Doors","S120Hood","S120Trunk"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
			};
		};
	};
};
class CfgDestroy
{
	class EngineHit
	{
		sound[] = {};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyVehiclePart: ProxyAttachment
	{
		scope = 2;
		simulation = "ProxyInventory";
		autocenter = 0;
		animated = 0;
		shadow = 1;
		reversed = 0;
	};
	class Proxyv3s_wheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_wheel.p3d";
		inventorySlot[] = {"V3SWheel_1_1","V3SWheel_2_1","V3SWheel_Spare_1","V3SWheel_Spare_2"};
	};
	class Proxyv3s_wheel_new_burst: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_new_burst.p3d";
		inventorySlot[] = {"V3SWheel_1_1","V3SWheel_2_1","V3SWheel_Spare_1","V3SWheel_Spare_2"};
	};
	class Proxyv3s_wheel_double: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_double.p3d";
		inventorySlot[] = {"V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_2","V3SWheel_2_3"};
	};
	class Proxyv3s_wheel_burst_double: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_burst_double.p3d";
		inventorySlot[] = {"V3SWheel_1_2","V3SWheel_1_3","V3SWheel_2_2","V3SWheel_2_3"};
	};
	class Proxyv3s_doors_Driver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_doors_Driver.p3d";
		inventorySlot = "V3SDriverDoors";
	};
	class Proxyv3s_doors_coDriver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_doors_coDriver.p3d";
		inventorySlot = "V3SCoDriverDoors";
	};
	class Proxyv3s_hood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\V3S\proxy\v3s_hood.p3d";
		inventorySlot = "V3Shood";
	};
	class ProxySedanWheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\civiliansedan\proxy\sedanWheel.p3d";
		inventorySlot[] = {"CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2"};
	};
	class ProxySedanWheel_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\civiliansedan\proxy\sedanWheel_destroyed.p3d";
		inventorySlot[] = {"CivSedanWheel_1_1","CivSedanWheel_1_2","CivSedanWheel_2_1","CivSedanWheel_2_2"};
	};
	class ProxySedanHood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanhood.p3d";
		inventorySlot = "CivSedanHood";
	};
	class ProxySedanTrunk: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanTrunk.p3d";
		inventorySlot = "CivSedanTrunk";
	};
	class ProxysedanDoors_Driver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_Driver.p3d";
		inventorySlot = "CivSedanDriverDoors";
	};
	class ProxysedanDoors_coDriver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_coDriver.p3d";
		inventorySlot = "CivSedanCoDriverDoors";
	};
	class ProxysedanDoors_cargo1: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_cargo1.p3d";
		inventorySlot = "CivSedanCargo1Doors";
	};
	class ProxysedanDoors_cargo2: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_cargo2.p3d";
		inventorySlot = "CivSedanCargo2Doors";
	};
	class ProxyNivaWheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
		inventorySlot[] = {"NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2","NivaWheel_Spare_1"};
	};
	class ProxyNivaWheel_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel_destroyed.p3d";
		inventorySlot[] = {"NivaWheel_1_1","NivaWheel_1_2","NivaWheel_2_1","NivaWheel_2_2","NivaWheel_Spare_1"};
	};
	class ProxyNivaDoors_Hood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Hood.p3d";
		inventorySlot = "NivaHood";
	};
	class ProxyNivaDoors_Trunk: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Trunk.p3d";
		inventorySlot = "NivaTrunk";
	};
	class ProxynivaDoors_Driver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Driver.p3d";
		inventorySlot = "NivaDriverDoors";
	};
	class ProxynivaDoors_coDriver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_coDriver.p3d";
		inventorySlot = "NivaCoDriverDoors";
	};
	class ProxyIkarusWheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\IkarusWheel.p3d";
		inventorySlot[] = {"BusWheel_1_1","BusWheel_2_1"};
	};
	class ProxyIkarusWheel_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_destroyed.p3d";
		inventorySlot[] = {"BusWheel_1_1","BusWheel_2_1"};
	};
	class ProxyIkarusWheel_rear: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear.p3d";
		inventorySlot[] = {"BusWheel_1_2","BusWheel_2_2"};
	};
	class ProxyIkarusWheel_rear_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear_destroyed.p3d";
		inventorySlot[] = {"BusWheel_1_2","BusWheel_2_2"};
	};
	class ProxyikarusHood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\ikarusHood.p3d";
		inventorySlot = "BusHood";
	};
	class ProxyIkarusDoors_Left: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Left.p3d";
		inventorySlot[] = {"BusLeftDoors_1","BusLeftDoors_2","BusLeftDoors_3"};
	};
	class ProxyIkarusDoors_Right: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Right.p3d";
		inventorySlot[] = {"BusRightDoors_1","BusRightDoors_2","BusRightDoors_3"};
	};
	class ProxyCivilianVan_wheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVan_wheel.p3d";
		inventorySlot[] = {"CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
	};
	class ProxyCivilianVan_wheel_dam: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVan_wheel_dam.p3d";
		inventorySlot[] = {"CivVanWheel_1_1","CivVanWheel_1_2","CivVanWheel_2_1","CivVanWheel_2_2"};
	};
	class ProxyCivilianVanDoors_Driver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Driver.p3d";
		inventorySlot = "CivVanDriverDoors";
	};
	class ProxyCivilianVanDoors_CoDriver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_CoDriver.p3d";
		inventorySlot = "CivVanCoDriverDoors";
	};
	class ProxyCivilianVanDoors_Cargo1: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo1.p3d";
		inventorySlot = "CivVanCargo1Doors";
	};
	class ProxyCivilianVanDoors_Cargo2: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo2.p3d";
		inventorySlot = "CivVanTrunkDown";
	};
	class ProxyCivilianVanDoors_Cargo3: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		inventorySlot = "CivVanTrunkUp";
	};
	class ProxyCivilianHatchback_Wheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Wheel.p3d";
		inventorySlot[] = {"CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
	};
	class ProxyCivilianHatchback_Wheel_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\sedanWheel_destroyed.p3d";
		inventorySlot[] = {"CivHatchbackWheel_1_1","CivHatchbackWheel_1_2","CivHatchbackWheel_2_1","CivHatchbackWheel_2_2"};
	};
	class ProxyCivilianHatchback_Hood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Hood.p3d";
		inventorySlot = "CivHatchbackHood";
	};
	class ProxyCivilianHatchback_Trunk: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Trunk.p3d";
		inventorySlot = "CivHatchbackTrunk";
	};
	class ProxyCivilianHatchback_Door_FL: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_FL.p3d";
		inventorySlot = "CivHatchbackDriverDoors";
	};
	class ProxyCivilianHatchback_Door_FR: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_FR.p3d";
		inventorySlot = "CivHatchbackCoDriverDoors";
	};
	class ProxyCivilianHatchback_Door_BL: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_BL.p3d";
		inventorySlot = "CivHatchbackCargo1Doors";
	};
	class ProxyCivilianHatchback_Door_BR: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\CivilianHatchback\proxy\CivilianHatchback_Door_BR.p3d";
		inventorySlot = "CivHatchbackCargo2Doors";
	};
	class ProxyUtilityVehicle_Wheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_Wheel.p3d";
		inventorySlot[] = {"UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
	};
	class ProxyUtilityVehicle_Wheel_destroyed: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_Wheel_destroyed.p3d";
		inventorySlot[] = {"UtilityVehicleWheel_1_1","UtilityVehicleWheel_1_2","UtilityVehicleWheel_2_1","UtilityVehicleWheel_2_2"};
	};
	class ProxyUtilityVehicle_DoorL: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_DoorL.p3d";
		inventorySlot = "UtilityVehicleDriverDoors";
	};
	class ProxyUtilityVehicle_DoorR: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\UtilityVehicle\proxy\UtilityVehicle_DoorR.p3d";
		inventorySlot = "UtilityVehicleCoDriverDoors";
	};
	class Proxys120_wheel: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_wheel.p3d";
		inventorySlot[] = {"S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
	};
	class Proxys120_wheel_damaged: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_wheel_damaged.p3d";
		inventorySlot[] = {"S120Wheel_1_1","S120Wheel_1_2","S120Wheel_2_1","S120Wheel_2_2"};
	};
	class Proxys120_doors_driver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_doors_driver.p3d";
		inventorySlot = "S120DriverDoors";
	};
	class Proxys120_doors_coDriver: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_doors_coDriver.p3d";
		inventorySlot = "S120CoDriverDoors";
	};
	class Proxys120_doors_cargo1: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_doors_cargo1.p3d";
		inventorySlot = "S120Cargo1Doors";
	};
	class Proxys120_doors_cargo2: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_doors_cargo2.p3d";
		inventorySlot = "S120Cargo2Doors";
	};
	class Proxys120_hood: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_hood.p3d";
		inventorySlot = "S120Hood";
	};
	class Proxys120_boot: ProxyVehiclePart
	{
		model = "DZ\vehicles\wheeled\s120\proxy\s120_boot.p3d";
		inventorySlot = "S120Trunk";
	};
};
