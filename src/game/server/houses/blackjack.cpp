// made by fokkonaut

#include "blackjack.h"
#include <game/server/gamecontext.h>

CBlackjack::CBlackjack(CGameContext *pGameServer) : CHouse(pGameServer, HOUSE_BLACKJACK)
{
}

const char *CBlackjack::GetWelcomeMessage(int ClientID)
{
	static char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Welcome to the blackjack table, %s! Press F4 to set a bet.", Server()->ClientName(ClientID));
	return aBuf;
}

const char *CBlackjack::GetConfirmMessage(int ClientID)
{
	return "Are you sure you want to buy a grog?";
}

const char *CBlackjack::GetEndMessage(int ClientID)
{
	return "You canceled the purchase.";
}

void CBlackjack::OnSuccess(int ClientID)
{
	CPlayer *pPlayer = GameServer()->m_apPlayers[ClientID];
	int GrogPrice = GameServer()->Config()->m_SvGrogPrice;
	if (pPlayer->GetWalletMoney() < GrogPrice)
	{
		GameServer()->SendChatTarget(ClientID, "You don't have enough money in your wallet to set that bet.");
		return;
	}

	if (pPlayer->GetCharacter() && pPlayer->GetCharacter()->AddGrog())
	{
		pPlayer->WalletTransaction(-GrogPrice, "set blackjack bet");
		GameServer()->SendChatTarget(ClientID, "You set a bet in blackjack");
	}
}

void CBlackjack::OnPageChange(int ClientID)
{
	const char *pFooter = "Press F3 to confirm your assignment.";
	char aMsg[256];
	str_format(aMsg, sizeof(aMsg), "Welcome to the tavern!\n\nIf you would like to buy a grog for %d money, please press F3.", GameServer()->Config()->m_SvGrogPrice);
	SendWindow(ClientID, aMsg, pFooter);
	m_aClients[ClientID].m_LastMotd = Server()->Tick();
}
