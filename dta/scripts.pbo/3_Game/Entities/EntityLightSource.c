enum LightSourceType
{
	NotDef,
	PointLight,
	SpotLight
};

class EntityLightSource extends Entity
{
	//---------------------------------------------------------------------------
	// Generic interface
	//---------------------------------------------------------------------------
	proto native void SetLightType(int pType);
	proto native int  GetLightType();

	proto native void SetEnabled(bool pState);
	proto native bool IsEnabled();

	proto native void SetCastShadow(bool pState);
	proto native bool GetCastShadow();

	proto native void SetVisibleDuringDaylight(bool pState);
	proto native bool IsVisibleDuringDaylight();

	proto native void SetRadius(float pValue);
	proto native float GetRadius();

	//---------------------------------------------------------------------------
	// colors & brightness
	//---------------------------------------------------------------------------
	proto native void   SetDiffuseColor(float pRed, float pGreen, float pBlue);
	proto native void   SetDiffuseColorV(vector pColorVector);
	proto native void   SetDiffuseAlpha(float pAlpha);
	proto native vector GetDiffuseColorV();
	proto native float  GetDiffuseAlpha();
	
	proto native void   SetAmbientColor(float pRed, float pGreen, float pBlue);
	proto native void   SetAmbientColorV(vector pColorVector);
	proto native void   SetAmbientAlpha(float pAlpha);
	proto native vector GetAmbientColorV();
	proto native float  GetAmbientAlpha();

	proto native void   SetBrightness(float pValue);
	proto native float  GetBrightness();
	
	//---------------------------------------------------------------------------
	// spot light specifics
	//---------------------------------------------------------------------------
	proto native void  SetSpotLightAngle(float pValue);
	proto native float GetSpotLightAngle();
};