#ifndef Rainbow_h
#define Rainbow_h

#include "Game.h"
#include "ffft.h"


class Rainbow : public Game{
public:
	Rainbow(NESController *controller, Adafruit_WS2801 *strip);
	~Rainbow();
	void run();
	void resume();
        
        


private:
	int red;
	int green;
	int blue;
	int colorMode;
        int geschw;
        int col;
        boolean ledState[10];
        const static int xOffset;
        int  pixel[20][10]={
                {0,1,2,3,4,5,6,7,8,9},
                {19,18,17,16,15,14,13,12,11,10},
                {20,21,22,23,24,25,26,27,28,29},
                {39,38,37,36,35,34,33,32,31,30},
                {40,41,42,43,44,45,46,47,48,49},
                {59,58,57,56,55,54,53,52,51,50},
                {60,61,62,63,64,65,66,67,68,69},
                {79,78,77,76,75,74,73,72,71,70},
                {	80,	81,	82,	83,	84,	85,	86,	87,	88,	89	}	,
                {	99,	98,	97,	96,	95,	94,	93,	92,	91,	90	}	,
                {	100	,	101	,	102	,	103	,	104	,	105	,	106	,	107	,	108	,	109	}	,
                {	119	,	118	,	117	,	116	,	115	,	114	,	113	,	112	,	111	,	110	}	,
                {	120	,	121	,	122	,	123	,	124	,	125	,	126	,	127	,	128	,	129	}	,
                {	139	,	138	,	137	,	136	,	135	,	134	,	133	,	132	,	131	,	130	}	,
                {	140	,	141	,	142	,	143	,	144	,	145	,	146	,	147	,	148	,	149	}	,
                {	159	,	158	,	157	,	156	,	155	,	154	,	153	,	152	,	151	,	150	}	, 
                {	160	,	161	,	162	,	163	,	164	,	165	,	166	,	167	,	168	,	169	}	,
                {	179	,	178	,	177	,	176	,	175	,	174	,	173	,	172	,	171	,	170	}	,
                {	180	,	181	,	182	,	183	,	184	,	185	,	186	,	187	,	188	,	189	}	,
                {	199	,	198	,	197	,	196	,	195	,	194	,	193	,	192	,	191	,	190	}	,
               };




};
#endif
