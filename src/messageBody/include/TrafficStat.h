

#ifndef _TrafficStat_H
#define _TrafficStat_H


#define  MSG_NewTifficStatLenght 8*8*2*14*4
struct CarClass
{
	char   Class[8];
};
struct CarGroup
{
	char Total[8];
	struct CarClass CarClassGroup[7];
};
struct CarAllGroup
{
	struct CarGroup Traffic;
	struct CarGroup Paid;
};
struct Group
{
	struct CarAllGroup Stat[14];
};
struct MSG_NewTifficStat
{
	struct Group Total;
	struct Group Five;
	struct Group Truck;
	struct Group Truck_Five;
};

#endif
