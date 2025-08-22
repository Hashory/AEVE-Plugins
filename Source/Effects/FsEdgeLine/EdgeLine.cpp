/*
	F's Plugins for VS2010/VS2012
*/

// clang-format off
#include "EdgeLine.h"
// clang-format on

// Communicate parameters to After Effects
// Refer to Param_Utils.h
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;

	// Color specification
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_TARGET, 
					0xFF,
					0x00,
					0x00,
					ID_TARGET_COL
					);
	// Color specification
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_SAMPLE, 
					0x00,
					0xFF,
					0x00,
					ID_SAMPLE_COL
					);

	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_LEVEL,	//Name
						0,						//VALID_MIN
						100,						//VALID_MAX
						0,						//SLIDER_MIN
						10,						//SLIDER_MAX
						1,						//CURVE_TOLERANCE
						0,						//DFLT
						1,						//PREC
						0,						//DISP
						0,						//WANT_PHASE
						ID_LEVEL
						);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_LENGTH,	//Parameter name
					0, 		//Minimum value for numeric input
					200,			//Maximum value for numeric input
					0,				//Slider minimum value 
					20,			//Slider maximum value
					10,				//Default value
					ID_LENGTH
					);
	// Color specification
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_DRAW, 
					0x00,
					0x00,
					0xFF,
					ID_DRAW_COL
					);
	out_data->num_params = 	ID_NUM_PARAMS; 

	return err;
}
static PF_Err
HandleChangedParam(
	PF_InData					*in_data,
	PF_OutData					*out_data,
	PF_ParamDef					*params[],
	PF_LayerDef					*outputP,
	PF_UserChangedParamExtra	*extraP)
{
	return PF_Err_NONE;
}
static PF_Err
QueryDynamicFlags(	
	PF_InData		*in_data,	
	PF_OutData		*out_data,	
	PF_ParamDef		*params[],	
	void			*extra)	
{
	PF_Err 	err 	= PF_Err_NONE;
	return err;
}
static PF_Err GetParams(CFsAE *ae, ParamInfo8 *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->GetCOLOR(ID_TARGET_COL,&infoP->targetCol));
	ERR(ae->GetCOLOR(ID_SAMPLE_COL,&infoP->sampleCol));
	PF_FpLong v;
	ERR(ae->GetFLOAT(ID_LEVEL,&v));
	if(!err){
		infoP->level  = (A_u_char)((double)PF_MAX_CHAN8 * v/100);
	}
	ERR(ae->GetADD(ID_LENGTH,&infoP->length));
	if (infoP->length>0){
		infoP->length = ae->downScale(infoP->length);
	}
	ERR(ae->GetCOLOR(ID_DRAW_COL,&infoP->drawCol));
	
	return err;
}
static ParamInfo16 convTo16(ParamInfo8 *info)
{
	ParamInfo16 ret;
	AEFX_CLR_STRUCT(ret);
	ret.targetCol	= info->targetCol;
	ret.sampleCol	= info->sampleCol;
	ret.level		= info->level;
	ret.length		= info->length;
	ret.drawCol		= CONV8TO16(info->drawCol);
	ret.w			= info->w;
	ret.h			= info->h;

	ret.ae			= info->ae;
	return ret;
}
static ParamInfo32 convTo32(ParamInfo8 *info)
{
	ParamInfo32 ret;
	AEFX_CLR_STRUCT(ret);
	ret.targetCol	= info->targetCol;
	ret.sampleCol	= info->sampleCol;
	ret.level		= info->level;
	ret.length		= info->length;
	ret.drawCol		= CONV8TO32(info->drawCol);
	ret.w			= info->w;
	ret.h = info->h;
	ret.ae			= info->ae;
	return ret;
}
static PF_Err 
FilterImage8 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo8 *	niP		= reinterpret_cast<ParamInfo8*>(refcon);
	if (compPix8Lv(*inP,niP->targetCol,niP->level)==FALSE) return err;

	int x0 = xL - niP->length;
	if (x0<0) x0=0;
	int x1 = xL + niP->length;
	if (x1>=niP->w) x1 = niP->w -1;
	int y0 = yL - niP->length;
	if (y0<0) x0=0;
	int y1 = yL + niP->length;
	if (y1>=niP->h) y1 = niP->h -1;

	for ( int y = y0; y<=y1; y++){
		for ( int x = x0; x<=x1; x++){
			if (compPix8Lv(niP->ae->in->getPixel8(x,y),niP->sampleCol,niP->level)==TRUE) {
				*outP = niP->drawCol;
				break;
			}
		}
	}


	return err;
}
static PF_Err 
FilterImage16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo16 *	niP		= reinterpret_cast<ParamInfo16*>(refcon);
	PF_Pixel t = CONV16TO8(*inP);
	if (compPix8Lv(t,niP->targetCol,niP->level)==FALSE) return err;

	int x0 = xL - niP->length;
	if (x0<0) x0=0;
	int x1 = xL + niP->length;
	if (x1>=niP->w) x1 = niP->w -1;
	int y0 = yL - niP->length;
	if (y0<0) x0=0;
	int y1 = yL + niP->length;
	if (y1>=niP->h) y1 = niP->h -1;

	for ( int y = y0; y<=y1; y++){
		for ( int x = x0; x<=x1; x++){
			PF_Pixel t2 = CONV16TO8(niP->ae->in->getPixel16(x, y));
			if (compPix8Lv(t2,niP->sampleCol,niP->level)==TRUE) {
				*outP = niP->drawCol;
				break;
			}
		}
	}


	return err;
}
static PF_Err 
FilterImage32 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_PixelFloat	*inP, 
	PF_PixelFloat	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo32 *	niP		= reinterpret_cast<ParamInfo32*>(refcon);
	if (compPix32_8Lv(*inP,niP->targetCol,niP->level)==FALSE) return err;

	int x0 = xL - niP->length;
	if (x0<0) x0=0;
	int x1 = xL + niP->length;
	if (x1>=niP->w) x1 = niP->w -1;
	int y0 = yL - niP->length;
	if (y0<0) x0=0;
	int y1 = yL + niP->length;
	if (y1>=niP->h) y1 = niP->h -1;

	for ( int y = y0; y<=y1; y++){
		for ( int x = x0; x<=x1; x++){
			if (compPix32_8Lv(niP->ae->in->getPixel32(x,y),niP->sampleCol,niP->level)==TRUE) {
				*outP = niP->drawCol;
				break;
			}
		}
	}


	return err;
}
static PF_Err 
	Exec (CFsAE *ae , ParamInfo8 *infoP)
{
	PF_Err	err = PF_Err_NONE;

	// Copy screen
	ERR(ae->CopyInToOut());
	
	if ( infoP->length<=0)
	{
		return err;
	}
	infoP->ae = ae;
	infoP->w = ae->in->width();
	infoP->h = ae->in->height();
	switch(ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		ParamInfo32 info32;
		info32 = convTo32(infoP);
		ERR(ae->iterate32((refconType)&info32,FilterImage32));
		break;
	case PF_PixelFormat_ARGB64:
		ParamInfo16 info16;
		info16 = convTo16(infoP);
		ERR(ae->iterate16((refconType)&info16,FilterImage16));
		break;
	case PF_PixelFormat_ARGB32:
		ERR(ae->iterate8((refconType)infoP,FilterImage8));
		break;
	}


	return err;
}

// Main rendering function
/*
	Hosts that do not support SmartFX (After Effects 7 and earlier) call this function for rendering
	Writing this function provides basic v6.5 compatibility
*/
static PF_Err 
Render ( 
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{

	PF_Err	err = PF_Err_NONE;
	PF_Handle		pixelTable = NULL;
	
	CFsAE ae(in_data,out_data,params,output,ID_NUM_PARAMS);
	err =ae.resultErr();
	if (!err){
		ERR(ae.CopyInToOut());
		ParamInfo8 info;
		ERR(GetParams(&ae,&info));
		ERR(Exec(&ae,&info));
	}
	return err;
}
/*
	For SmartFX support, this function is called first to acquire parameters
*/
#if defined(SUPPORT_SMARTFX)
static PF_Err
PreRender(
	PF_InData			*in_data,
	PF_OutData			*out_data,
	PF_PreRenderExtra	*extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	CFsAE ae(in_data,out_data,extraP,sizeof(ParamInfo8),ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){

		ParamInfo8 *infoP = reinterpret_cast<ParamInfo8*>(ae.LockPreRenderData());
		if (infoP){
			ae.SetHostPreRenderData();
			ERR(GetParams(&ae,infoP));
			ERR(ae.UnSetPreRenderData());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}
#endif

#if defined(SUPPORT_SMARTFX)
static PF_Err
SmartRender(
	PF_InData				*in_data,
	PF_OutData				*out_data,
	PF_SmartRenderExtra		*extraP)
{
	PF_Err			err		= PF_Err_NONE,
					err2 	= PF_Err_NONE;

	CFsAE ae(in_data,out_data,extraP,ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){
		ParamInfo8 *infoP = reinterpret_cast<ParamInfo8*>(ae.LockPreRenderData());
		if (infoP){
			ERR(Exec(&ae,infoP));
			ERR2(ae.UnsetSmartRender());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}
#endif

#include "Fs_Entry.h"
