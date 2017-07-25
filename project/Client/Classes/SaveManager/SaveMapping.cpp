#include "SaveMapping.h"

//index 0 model   1 dress  2 eye   8-3  necklace   9-4 hair  10-5 earring  11-6 tiara   bodyArr
//item  0 hair 1 eye  2 liner  5 shadow  44 earring  45 necklace  46 dress  47 tiara  
//index 3-0 shadow   4-1 liner  5-2 lash  6-3 blusher  7-4 lip     bodySpriteArr

char* em_save_mapping[] = 
{
	"IS_ADFREE_ON",
	"IS_MUSIC_ON",
	"IS_SOUND_ON",
	"IS_CUR_ROLE",
	"IS_CUR_ROOM",
	"IS_BOOL_RATE",
};


char* SaveMapping::getSaveKey(SAVE_ID saveID)
{
	return em_save_mapping[saveID];
}



