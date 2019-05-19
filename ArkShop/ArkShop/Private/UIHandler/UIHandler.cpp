/**
* \file UIHandler.cpp
* \author Matthias Birnthaler
* \date 19 May 2019
* \brief Implementation UI logic for shop interface mod 
*
*/


/* =================================================[includes]================================================= */
#include "UIHandler.h"
#include "json.hpp"
#include "Store.h"


namespace UIHandler
{
	/* ===================================== [prototype of local functions] ======================================= */
	static void  Hook_AShooterGameState_HTTPPostRequest(AShooterGameState* _this, FString InURL, FString Content);


	/* ===================================== [definition of local functions] ====================================== */

	/**
	* \brief Hooks AShooterGameState_HTTPPostRequest 
	*
	* This function counts all slots of a tribe that are not expired
	*
	* \param[in] AShooterGameState; not used 
	* \param[in] InURL target url 
	* \param[in] Content content
	* \return void 
	*/
	static void  Hook_AShooterGameState_HTTPPostRequest(AShooterGameState* _this, FString InURL, FString Content)
	{
		Log::GetLog()->error("PostRequest: ", InURL.ToString(), Content.ToString());

		nlohmann::json content = Content.ToString();


		const uint64 steam64 = (int)content["SteamID"];
		AShooterPlayerController* player_controller = ArkApi::GetApiUtils().FindPlayerFromSteamId(steam64);

		FString itemId = FString(ArkApi::Tools::Utf8Decode(content["ItemID"]).c_str());

		if (nullptr != player_controller)
		{
			ArkShop::Store::Buy(player_controller, itemId, 1 );
		
		}
		else
		{
			Log::GetLog()->error("PostRequest SteamId wrong steam64 {}", steam64);
		}

		AShooterGameState_HTTPPostRequest_original(_this, InURL, Content);
	}


	/* ===================================== [definition of global functions] ===================================== */

	/**
	* \brief Initialisation of the needed hooks for the ui interface 
	*
	* This function intialisze all hooks for the interface logic
	*
	* \return void
	*/
	void UIHandler_InitHooks(void)
	{
		ArkApi::GetHooks().SetHook("AShooterGameState.HTTPPostRequest",
			&Hook_AShooterGameState_HTTPPostRequest,
			&AShooterGameState_HTTPPostRequest_original);
	}


	/**
	* \brief Remove of the needed hooks for the ui interface
	*
	* This function removes all hooks for the interface logic
	*
	* \return void
	*/
	void UIHandler_RemoveHooks(void)
	{
		ArkApi::GetHooks().DisableHook("AShooterGameState.HTTPPostRequest",
			&Hook_AShooterGameState_HTTPPostRequest);

	}

} /* namespace UIHandler */