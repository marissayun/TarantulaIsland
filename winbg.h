
//{{BLOCK(winbg)

//======================================================================
//
//	winbg, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 296 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 9472 + 2048 = 12032
//
//	Time-stamp: 2020-04-22, 22:36:47
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WINBG_H
#define GRIT_WINBG_H

#define winbgTilesLen 9472
extern const unsigned short winbgTiles[4736];

#define winbgMapLen 2048
extern const unsigned short winbgMap[1024];

#define winbgPalLen 512
extern const unsigned short winbgPal[256];

#endif // GRIT_WINBG_H

//}}BLOCK(winbg)
