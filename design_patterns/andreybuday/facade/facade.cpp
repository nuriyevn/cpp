#include <iostream>
using namespace std;
// Renting boots and other stuff

class SkiRent
{
public:
	int RentBoots(int feetSize, int skierLevel)
	{
		return 20;
	}
	int RentSki(int weight, int skierLevel)
	{
		return 40;
	}
	int RentPole(int height)
	{	
		return 5;
	}
};

// Buying tickets
class SkiResortTicketSystem
{
public:
	int BuyOneDayTicket()
	{
		return 115;
	}
	int BuyHalfDayTicket()
	{
		return 60;
	}
};

//
class HotelBookingSystem
{
public:
	int BookRoom(int roomQuality)
	{
		switch (roomQuality)
		{
		case 3:
			return 250;
		case 4:
			return 500;
		case 5:
			return 900;
		default:
			break;
		}
	}
};

class SkiResortFacade
{
public:
	int HaveGoodRest(int height, int weight, int feetSize, int skierLevel, int roomQuality)
	{
		int skiPrice = mSkiRent.RentSki(weight, skierLevel);
		int skiBootsPrice= mSkiRent.RentBoots(feetSize, skierLevel);
		int polePrice = mSkiRent.RentPole(height);
		int oneDayTicketPr = mTicketSystem.BuyOneDayTicket();
		int hotelPrice = mBookingSystem.BookRoom(roomQuality);
		return skiPrice + skiBootsPrice + polePrice + oneDayTicketPr + hotelPrice;
	}
	int HaveRestWithOwnSkis()
	{
		int oneDayTicketPrice = mTicketSystem.BuyOneDayTicket();
		return oneDayTicketPrice;	
	}
private:
	SkiRent mSkiRent;
	SkiResortTicketSystem mTicketSystem;
	HotelBookingSystem mBookingSystem;
};

int main()
{
	SkiResortFacade resortFacade;
	int total = resortFacade.HaveGoodRest(176, 80, 44, 0, 4);

	cout << "The total price is " << total << endl;
	return 0;
		
}
