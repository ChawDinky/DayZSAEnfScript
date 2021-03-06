/*
Please remember that:
-Lights work only on client side!
-Lights with Brightness or Radius of 0 (or less) are automatically deleted
-Lights are very performance heavy. Especially if they cast shadows. Use them carefully!

Script author: Boris Vacula
*/

class ScriptedLightBase extends EntityLightSource
{
	private float m_LifetimeStart;
	private float m_LifetimeEnd = -1; // -1 makes this light permanent
	private float m_FadeOutTime = -1;
	private float m_FadeInTime = -1;
	private float m_Radius;
	private float m_RadiusTarget;
	private float m_Brightness;
	private float m_BrightnessTarget;
	private float m_BrightnessSpeedOfChange = 1;
	private float m_RadiusSpeedOfChange = 1;
	private float m_OptimizeShadowsRadius = 0; // Within this range between the light source and camera the shadows will be automatically disabled for performance reasons.
	
	private Object m_Parent; // Attachment parent
	private vector m_LocalPos; // Local position to my attachment parent
	private vector m_LocalOri; // Local orientation to my attachment parent
	
	//! Constructor. Everything here is executed before the constructor of all children.
	void ScriptedLightBase()
	{
		m_LifetimeStart = GetGame().GetTime();
		SetEnabled(true);
		SetEventMask(EntityEvent.FRAME);
	}
	
	//! Attaches this light on the parent entity, with optional position and orientation offset.
	void AttachOnObject(Object parent, vector local_pos = "0 0 0", vector local_ori = "0 0 0")
	{
		if (!parent)
		{
			if (m_Parent)
			{
				m_Parent.RemoveChild(this);
			}
			
			return;
		}
		else
		{
			if (m_Parent)
			{
				m_Parent.RemoveChild(this);
			}
		}
		
		m_Parent = parent;
		m_LocalPos = local_pos;
		m_LocalOri = local_ori;
		SetOrientation(local_ori);
		SetPosition(local_pos);
		parent.AddChild(this, -1);
		parent.Update();
	}
	
	//! Returns attachment parent
	Object GetAttachmentParent()
	{
		return m_Parent;
	}
	
	//! Attaches this light on the parent entity's memory point, with optional direction target memory point.
	void AttachOnMemoryPoint(Object parent, string memory_point_start, string memory_point_target = "")
	{
		vector local_pos = parent.GetMemoryPointPos(memory_point_start);
		vector local_ori;
		if (memory_point_target != "")
		{
			vector target_pos = parent.GetSelectionPositionLS(memory_point_target);
			target_pos = vector.Direction(m_LocalPos, target_pos);
			local_ori = target_pos.VectorToAngles();
		}
		
		AttachOnObject(parent, local_pos, local_ori);
	}
	
	//! Detaches this light from its parent entity.
	void DetachFromParent()
	{
		if (!m_Parent)
		{
			m_Parent = Object.Cast( GetParent() );
		}
		
		if (m_Parent)
		{
			m_Parent.RemoveChild(this);
		}
		
		m_Parent = null;
		m_LocalPos = Vector(0,0,0);
		m_LocalOri = Vector(0,0,0);
	}
	
	//! Creates an instance of light on the given position. Optionally, use fade_in_time_in_s parameter to make the light fade into existence.
	static ScriptedLightBase CreateLight(typename name, vector global_pos, float fade_in_time_in_s = 0)
	{
		ScriptedLightBase light_instance;
		
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
		{
			light_instance = ScriptedLightBase.Cast( GetGame().CreateObject(name.ToString(), global_pos, true) );
			
			if (!light_instance)
			{
				Error("Error! Light entity of name " + name.ToString() + " cannot be spawned! This name is incorrect or not inherited from ScriptedLightBase." );
				return null;
			}
			
			if (fade_in_time_in_s != 0)
			{
				light_instance.FadeIn(fade_in_time_in_s);
			}
		}
		else // Server side
		{
			Error("An instance of ScriptedLightBase was attempted to spawn on server side! Lights are CLIENT SIDE ONLY!");
		}
		
		return light_instance;
	}
	
	//! Sets the brightness of the light
	void SetBrightnessTo(float value)
	{
		m_Brightness = value;
		m_BrightnessTarget = value;
		SetBrightness(m_Brightness);
		CorrectLightPulseDuringDaylight();
	}
	
	//! Call this after using SetBrightness(...) to fix light's intensity during daytime
	void CorrectLightPulseDuringDaylight()
	{
		if (m_Brightness < 100)
		{
			float v = m_Brightness * 0.01;
			
			if (v > 0)
			{
				float brightness_compesation = 1 / v;
				float compenset_brightness = m_Brightness * brightness_compesation;
				SetBrightness(compenset_brightness);
				SetPulseCoef(v);
			}
		}
		else
		{
			SetPulseCoef(1);
		}
	}
	
	//! Fades the brightness of the light to the given value.
	void FadeBrightnessTo( float value, float time_in_s )
	{
		m_BrightnessTarget = value;
		
		if (time_in_s == 0)
		{
			m_BrightnessSpeedOfChange = 9999;
		}
		else
		{
			m_BrightnessSpeedOfChange = Math.AbsFloat(m_Brightness - m_BrightnessTarget) / time_in_s;
		}
	}
	
	//! Sets the radius of the light
	void SetRadiusTo(float value)
	{
		m_Radius = value;
		m_RadiusTarget = value;
		SetRadius(m_Radius);
	}
	
	//! Fades the radius of the light to the given value.
	void FadeRadiusTo( float value, float time_in_s )
	{
		m_RadiusTarget = value;
		
		if (time_in_s == 0)
		{
			m_RadiusSpeedOfChange = 9999;
		}
		else
		{
			m_RadiusSpeedOfChange = Math.AbsFloat(m_Radius - m_RadiusTarget) / time_in_s;
		}
		
		
	}
	
	//! Switches off the light and deletes it from memory
	void Destroy()
	{
		ClearEventMask(EntityEvent.FRAME);
		SetEnabled(false);
		GetGame().ObjectDelete(this);
	}
	
	//! Makes the light destroy itself after the given time in seconds. The light will fade out if it's set to do so with SetFadeOutTime(...)
	void SetLifetime(float life_in_s)
	{
		m_LifetimeEnd = GetGame().GetTime() + life_in_s * 1000;
	}
	
	//! Sets the fade out time in seconds. Fade out begins automatically as the light nears the end of its life time.
	void SetFadeOutTime(float time_in_s)
	{
		m_FadeOutTime = time_in_s * 1000;
	}
	
	//! Starts the fade out process and destroys the light when its done. Optional parameter allows you to set time of this fade out in seconds. If not set, then default value (from SetFadeOutTime(...)) is used.
	void FadeOut(float time_in_s = -1)
	{
		float time_in_ms = time_in_s * 1000;
		
		if (time_in_s == -1)
		{
			float kill_time_in_s = m_FadeOutTime*0.001;
			
			FadeBrightnessTo(0, kill_time_in_s);
			FadeRadiusTo(0, kill_time_in_s);
			SetLifetime(kill_time_in_s);
		}
		else
		{
			FadeBrightnessTo(0, time_in_s);
			FadeRadiusTo(0, time_in_s);
			SetLifetime(time_in_s);
		}
	}
	
	//! Makes the light fade into existence. Works only at the moment the light is created. Consider using FadeBrightnessTo(...) at anytime later during lifetime.
	void FadeIn(float time_in_s)
	{
		float brightness = m_Brightness;
		SetBrightnessTo(0);
		FadeBrightnessTo(brightness, time_in_s);
	}
	
	//! Prolongs the lifetime of the light in ms. Use negative number to shorten its lifetime.
	void AddLifetime(float life_in_s)
	{
		m_LifetimeEnd += life_in_s * 1000;
	}
	
	//! override this for custom functionality
	void OnFrameLightSource(IEntity other, float timeSlice)
	{
		// ... insert your code here. No need to call super.
	}
	
	//! On frame event. If you want to control your light within your own rules then override the event OnFrameLightSource and put your code there.
	override void EOnFrame(IEntity other, float timeSlice)
	{
		// Control lifetime of the light
		int current_time = GetGame().GetTime();
		
		if ( CheckLifetime(current_time) )
		{
			SetRadius(m_Radius);
		}
		else
		{
			return;
		}
		
		CheckFadeOut(current_time);
		HandleBrightnessFadeing(timeSlice);
		HandleRadiusFadeing(timeSlice);
		
		OnFrameLightSource(other, timeSlice);
		CheckIfparentIsInCargo();
		TryShadowOptimization();
	}
	
	//! Optimizes shadows by disabling them on this light source while it's within the given radius around the camera.
	void TryShadowOptimization()
	{
		if (m_OptimizeShadowsRadius > 0)
		{
			float distance_to_camera = vector.Distance( GetPosition(), GetGame().GetCurrentCameraPosition() );
			
			if (distance_to_camera < m_OptimizeShadowsRadius)
			{
				SetCastShadow(false);
			}
			else
			{
				SetCastShadow(true);
			}
		}
	}
	
	//! When the light source gets within this radius (radius_in_m) around the camera, then it's shadows are disabled.
	void SetDisableShadowsWithinRadius(float radius_in_m)
	{
		m_OptimizeShadowsRadius = radius_in_m;
	}
	
	//! Returns the range you put inside SetDisableShadowsWithinRadius(...)
	float GetDisableShadowsWithinRadius()
	{
		return m_OptimizeShadowsRadius;
	}
	
	void CheckIfparentIsInCargo()
	{
		// TO DO: OPTIMIZE AND REFACTOR! THIS MUST BE HANDLED IN AN EVENT, NOT PER FRAME!
		
		if (m_Parent)
		{
			EntityAI parent_EAI = EntityAI.Cast( m_Parent );
			
			if (parent_EAI) // Check if the Cast was successfull
			{
				GameInventory GI = parent_EAI.GetInventory();
				
				if (GI) // Prevents handling of light on the parent item when it's projected in inventory as the item in inventory character's hands.
				{
					bool is_in_cargo = GI.IsInCargo();
					
					if (!is_in_cargo)
					{
						EntityAI parent2 = parent_EAI.GetHierarchyParent();
						
						if (parent2  &&  parent2.GetInventory())
						{
							is_in_cargo = parent2.GetInventory().IsInCargo();
						}
					}
					
					if ( is_in_cargo )
					{
						SetEnabled(false);
					}
					else
					{
						SetEnabled(true);
					}
				}
			}
		}
	}
	
	// Destroys this light if it's past it lifetime
	private bool CheckLifetime(int current_time)
	{
		if ( current_time > m_LifetimeEnd  &&  m_LifetimeEnd != -1 )
		{
			Destroy();
			return false;
		}
		
		return true;
	}
	
	// Handles fade out effect at the end of lifetime
	private void CheckFadeOut( int current_time)
	{
		// Control fade out of the light
		if ( m_FadeOutTime != -1  &&  m_LifetimeEnd != -1  &&  current_time > m_LifetimeEnd - m_FadeOutTime )
		{
			m_FadeOutTime = -1;
			m_FadeInTime = -1; // Stop fade in process
			float time_left_in_s = (m_LifetimeEnd - current_time) * 0.001;
			FadeBrightnessTo(0, time_left_in_s);
			FadeRadiusTo(0, time_left_in_s);
		}
	}
	
	// handles fading of brightness
	private void HandleBrightnessFadeing(float timeSlice)
	{
		if ( m_Brightness != m_BrightnessTarget )
		{
			float brightness_difference = m_Brightness - m_BrightnessTarget;
			
			if (brightness_difference > m_BrightnessSpeedOfChange*timeSlice)
				brightness_difference = m_BrightnessSpeedOfChange*timeSlice;
			
			if (brightness_difference < -m_BrightnessSpeedOfChange*timeSlice)
				brightness_difference = -m_BrightnessSpeedOfChange*timeSlice;
			
			m_Brightness -= brightness_difference;
			
			if ( m_Brightness > 0  ||  m_BrightnessTarget > 0)
			{
				SetBrightness(m_Brightness);
				CorrectLightPulseDuringDaylight();
			}
			else
			{
				Destroy();
				return;
			}
		}
		else
		{
			SetBrightness(m_Brightness);
			CorrectLightPulseDuringDaylight();
		}
	}
	
	// handles fading of radius
	private void HandleRadiusFadeing(float timeSlice)
	{
		if ( m_Radius != m_RadiusTarget )
		{
			float radius_difference = m_Radius - m_RadiusTarget;
			
			if (radius_difference > m_RadiusSpeedOfChange*timeSlice)
				radius_difference = m_RadiusSpeedOfChange*timeSlice;
			
			if (radius_difference < -m_RadiusSpeedOfChange*timeSlice)
				radius_difference = -m_RadiusSpeedOfChange*timeSlice;
			
			m_Radius -= radius_difference;
			
			if ( m_Radius > 0  ||  m_RadiusTarget > 0)
			{
				SetRadius(m_Radius);
			}
			else
			{
				Destroy();
				return;
			}
		}
		else
		{
			SetRadius(m_Radius);
		}
	}
};