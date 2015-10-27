#include "SwipeCard.h"
#include "Manager.h"

// implement smart pointer for reference counting of SwipeCards

int main()
{
	SwipeCard *nusratsCard = new SwipeCard(); //Both classes have their own life cycle
	string nusratsCardId  = nusratsCard->MakeOfSwipeCard();  

	Manager *nusrat = new Manager("Nusrat Nuriyev"); // They are independent of each other
	nusrat->HowIsTheManager(true);
	nusrat->Logon(nusratsCard);

	cout << nusrat->Logon(nusratsCard) << " has been logged on with swipcard id: " << nusratsCardId << endl;


	bool nusratIsGood = false;
	nusrat->HowIsTheManager(nusratIsGood);

	if (!nusratIsGood)
	{
		delete nusrat;
		nusrat = 0;
	}


	SwipeCard *alexsCard = nusratsCard;
	string alexsCardId(nusratsCardId);
	

	Manager *alex = new Manager("Alexander Naumkin");
	alex->HowIsTheManager(true);
	cout << alex->Logon(alexsCard) << " has been logged on with swipecard id: " << alexsCardId << endl;



	if (alex) delete alex;
	if (nusrat) delete nusrat;

	delete nusratsCard;
}
