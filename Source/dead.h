//HEADER_GOES_HERE

//dead
extern int spurtndx; // weak
extern DeadStruct dead[31];
extern int stonendx;

void __cdecl InitDead();
void __fastcall AddDead(int dx, int dy, char dv, int ddir);
void __cdecl SetDead();