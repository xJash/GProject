

//-----------------------------------
// ���� Ÿ��� ��û. 
//-----------------------------------
class cltGameMsgRequest_RideOrUnrideHorse{
public:
	SI32 siHorseIndex;

	cltGameMsgRequest_RideOrUnrideHorse(SI32 horseindex)
	{
		siHorseIndex	 = horseindex;
	}
};

class cltGameMsgResponse_RideOrUnrideHorse{
public:
	SI32 siHorseIndex;

	cltGameMsgResponse_RideOrUnrideHorse(SI32 horseindex)
	{
		siHorseIndex = horseindex;
	}
};

