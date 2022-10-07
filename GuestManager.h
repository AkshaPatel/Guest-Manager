#ifndef GUESTMANAGER_H
#define GUESTMANAGER_H
#include <vector>

enum class RoomType { Standard, Comfort };

enum class GuestType { Family, Businessman, Rockstar };

class Guest
{
protected:
	RoomType Room;
	GuestType guest;
	int StayDuration;

public:
	Guest();
	Guest(GuestType customer, RoomType room, int numberofdays);


	GuestType GetGuestType() const;
	RoomType GetRoomType() const;
	int GetBookedDays() const;

	virtual int GetRoomBusyDays() const = 0;

	virtual int GetAdditionalIncome() const = 0;

	virtual ~Guest();
};


class Family : public Guest
{
public:
	Family();
	Family(RoomType room, int numberofdays);
	~Family();

	int GetRoomBusyDays() const override;

	int GetAdditionalIncome() const override;

};


class Rockstar : public Guest
{
public:
	Rockstar();
	Rockstar(RoomType room, int numberofdays);
	~Rockstar();

	int GetRoomBusyDays() const override;

	int GetAdditionalIncome() const override;

};


class Businessman : public Guest
{
private:
	int AdditionalIncome;

public:
	Businessman();
	Businessman(RoomType room, int numberofdays, int extraincome);

	~Businessman();

	int GetRoomBusyDays() const override;

	int GetAdditionalIncome() const override;

};



class GuestManager
{
private:
	int StandardRooms;
	int dayPriceStandard;

	int ComfortRooms;
	int dayPriceComfort;

	int totalextraincome = 0;
	std::vector<Guest*> clients;

public:
	GuestManager();
	GuestManager(int StdRooms, int dayPriceStd, int CmftRooms, int dayPriceCmft);

	~GuestManager();

	bool AddGuest(GuestType customer, RoomType room, int stayDays, int extraincome = 0);

	bool IsAvailable(RoomType room, int inDays = 0);

	int IncomingProfit() const;

	float EarningEfficiency();

	bool operator<(GuestManager& hotel) const;

};

#endif