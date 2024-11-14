// made by fokkonaut

#ifndef GAME_HOUSES_BLACKJACK_H
#define GAME_HOUSES_BLACKJACK_H

#include "house.h"
#include <engine/shared/protocol.h>

class CBlackjack : public CHouse
{
public:
	CBlackjack(CGameContext *pGameServer);
	virtual ~CBlackjack() {};

	virtual void OnPageChange(int ClientID);
	virtual void OnSuccess(int ClientID);
	virtual const char *GetWelcomeMessage(int ClientID);
	virtual const char *GetConfirmMessage(int ClientID);
	virtual const char *GetEndMessage(int ClientID);
};

#endif // GAME_HOUSES_BLACKJACK_H
