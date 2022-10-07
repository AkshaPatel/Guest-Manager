#include <iostream>
#include <vector>
#include "GuestManager.h"
#include <climits>


Guest::Guest()
{

}

Guest::Guest(GuestType customer, RoomType room, int numberofdays)
{
    guest = customer;
    Room = room;
    StayDuration = numberofdays;
}

GuestType Guest::GetGuestType() const
{
    return guest;
}

RoomType Guest::GetRoomType() const
{
    return Room;
}

int Guest::GetBookedDays() const
{
    return StayDuration;
}

Guest::~Guest()
{

}



Family::Family()
{

}

Family::Family(RoomType room, int numberofdays)
    : Guest(GuestType::Family, room, numberofdays)
{

}

int Family::GetRoomBusyDays() const
{
    return StayDuration;
}

int Family::GetAdditionalIncome() const
{
    return 0;
}

Family::~Family()
{

}



Rockstar::Rockstar()
{

}

Rockstar::Rockstar(RoomType room, int numberofdays)
    :Guest(GuestType::Rockstar, room, numberofdays)
{

}

int Rockstar::GetRoomBusyDays() const
{
    return StayDuration + 10;
}

int Rockstar::GetAdditionalIncome() const
{
    return 0;
}

Rockstar::~Rockstar()
{

}



Businessman::Businessman()
{

}

Businessman::Businessman(RoomType room, int numberofdays, int extraincome)
    : Guest(GuestType::Businessman, room, numberofdays)
{
    AdditionalIncome = extraincome;
}

int Businessman::GetRoomBusyDays() const
{
    return StayDuration;
}

int Businessman::GetAdditionalIncome() const
{
    return AdditionalIncome;
}

Businessman::~Businessman()
{

}




GuestManager::GuestManager()
{

}

GuestManager::GuestManager(int StdRooms, int dayPriceStd, int CmftRooms, int dayPriceCmft)
{
    StandardRooms = StdRooms;
    dayPriceStandard = dayPriceStd;
    ComfortRooms = CmftRooms;
    dayPriceComfort = dayPriceCmft;
}

bool GuestManager::AddGuest(GuestType customer, RoomType room, int stayDays, int extraincome)
{

    if (IsAvailable(room) == false) {
        return false;
    }
    else if (customer == GuestType::Businessman) {
        class Guest *person = nullptr;
        person = new class Businessman::Businessman(room, stayDays, extraincome);
        clients.push_back(person);
    }
    else if (customer == GuestType::Rockstar) {
        class Guest *person = nullptr;
        person = new class Rockstar(room, stayDays);
        clients.push_back(person);
    }
    else {
        class Guest *person = nullptr;
        person = new class Family(room, stayDays);
        clients.push_back(person);   
    }

    return true;
}

bool GuestManager::IsAvailable(RoomType room, int inDays)
{
    int RoomsOccupied = 0;
    int leastDaysTillFree = INT_MAX;
    for (unsigned int i = 0; i < clients.size(); i++)
    {
        if (clients[i]->GetRoomType() == room) {
            RoomsOccupied++;
            if (clients[i]->GetRoomBusyDays() < leastDaysTillFree) {
                leastDaysTillFree = clients[i]->GetRoomBusyDays();
            }
        }
    }
    if (room == RoomType::Standard) {
        if (RoomsOccupied < StandardRooms)
            return true;
        else if (RoomsOccupied == StandardRooms && leastDaysTillFree <= inDays)
            return true;
    }
    else {
        if (RoomsOccupied < ComfortRooms)
            return true;
        else if (RoomsOccupied == ComfortRooms && leastDaysTillFree <= inDays)
            return true; 
    }
    return false;
}

int GuestManager::IncomingProfit() const
{
    int totalprofit = 0;

    for (unsigned int i = 0; i < clients.size(); i++) {
        if (clients[i]->GetRoomType() == RoomType::Standard) {
            if (clients[i]->GetGuestType() == GuestType::Family || clients[i]->GetGuestType() == GuestType::Rockstar)
                totalprofit += dayPriceStandard * clients[i]->GetBookedDays();
            else
                totalprofit += (dayPriceStandard + clients[i]->GetAdditionalIncome()) * clients[i]->GetBookedDays();
        }
        else {
            if (clients[i]->GetGuestType() == GuestType::Family || clients[i]->GetGuestType() == GuestType::Rockstar)
                totalprofit += dayPriceComfort * clients[i]->GetBookedDays();
            else
                totalprofit += (dayPriceComfort + clients[i]->GetAdditionalIncome()) * clients[i]->GetBookedDays();
        }
    }
    return totalprofit;
}

float GuestManager::EarningEfficiency()
{
    float max_per_day_income = (float)((StandardRooms * dayPriceStandard) + (ComfortRooms * dayPriceComfort));

    float current_per_day_income = 0;
    for (unsigned int i = 0; i < clients.size(); i++) {
        if (clients[i]->GetRoomType() == RoomType::Standard) {
            current_per_day_income += (float)dayPriceStandard;
        }
        else {
            current_per_day_income += (float)dayPriceComfort;
        }

        if (clients[i]->GetGuestType() == GuestType::Businessman) {
            current_per_day_income += (float)(clients[i]->GetAdditionalIncome());
        }
    }

    float earning_efficiency = current_per_day_income / max_per_day_income;

    return earning_efficiency;
}

bool GuestManager::operator<(GuestManager& hotel) const
{
    if (IncomingProfit() < hotel.IncomingProfit())
        return true;

    return false;
}

GuestManager::~GuestManager()
{
    for (unsigned int i = 0; i < clients.size(); i++) {
        delete clients[i];
        clients[i] = nullptr;
    }
}