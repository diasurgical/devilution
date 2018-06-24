//HEADER_GOES_HERE

#include "../types.h"

PATHNODE path_nodes[300];
int gdwCurPathStep;
int pnode_vals[26];
PATHNODE *pnode_ptr;
PATHNODE *pnode_tblptr[300];
PATHNODE path_2_nodes[300];

#define DIRECTIONS 8

char pathxdir[DIRECTIONS] = { -1, -1, 1, 1, -1, 0, 1, 0 };
char pathydir[DIRECTIONS] = { -1, 1, -1, 1, 0, -1, 0, 1 };

/* rdata */
char path_directions[9] = { 5, 1, 6, 2, 0, 3, 8, 4, 7 };

int __fastcall FindPath(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, int sx, int sy, int dx, int dy, char *path)
{
	PATHNODE *v8; // esi
	char v9; // al
	PATHNODE *v11; // eax
	int result; // eax
	PATHNODE *v13; // edx
	int v14; // eax
	int v15; // edi
	bool v16; // zf
	int *v17; // ecx
	char v18; // dl

	pnode_vals[0] = 0;
	*(_DWORD *)&path_2_nodes[0].f = (unsigned int)path_new_step();
	gdwCurPathStep = 0;
	pnode_ptr = path_new_step();
	v8 = path_new_step();
	v8->g = 0;
	v9 = path_get_h_cost(sx, sy, dx, dy);
	v8->h = v9;
	v8->x = sx;
	v8->f = v9 + v8->g;
	v8->y = sy;
	*(_DWORD *)(*(_DWORD *)&path_2_nodes[0].f + 48) = (unsigned int)v8;
	while ( 1 )
	{
		v11 = GetNextPath();
		if ( !v11 )
			return 0;
		if ( v11->x == dx && v11->y == dy )
			break;
		if ( !path_get_path(PosOk, PosOkArg, v11, dx, dy) )
			return 0;
	}
	v13 = v11;
	v14 = (int)&v11->Parent;
	v15 = 0;
	if ( *(_DWORD *)v14 )
	{
		while ( 1 )
		{
			v16 = v15 == 25;
			if ( v15 >= 25 )
				break;
			pnode_vals[++v15] = path_directions[3 * (v13->y - *(_DWORD *)(*(_DWORD *)v14 + 8))
													- *(_DWORD *)(*(_DWORD *)v14 + 4)
													+ 4
													+ v13->x];
			v13 = *(PATHNODE **)v14;
			v14 = *(_DWORD *)v14 + 12;
			if ( !*(_DWORD *)v14 )
			{
				v16 = v15 == 25;
				break;
			}
		}
		if ( v16 )
			return 0;
	}
	result = 0;
	if ( v15 > 0 )
	{
		v17 = &pnode_vals[v15];
		do
		{
			v18 = *(_BYTE *)v17;
			--v17;
			path[result++] = v18;
		}
		while ( result < v15 );
	}
	return result;
}

/* heuristic, estimated cost from (sx,sy) to (dx,dy) */
int __fastcall path_get_h_cost(int sx, int sy, int dx, int dy)
{
	int delta_x = abs(sx - dx);
	int delta_y = abs(sy - dy);
	return 2 * (delta_x + delta_y);
}

/* return 2 if pPath's destination is in a straight line with (dx, dy), else 3
 *
 * I think this is to approximate that diagonal movement should have a cost of
 * sqrt(2). That's approx. 1.5, so they multiply all step costs by 2 except
 * diagonals which are multiplied by 3
 */
int __fastcall path_check_equal(PATHNODE *pPath, int dx, int dy)
{
	return ( pPath->x == dx || pPath->y == dy ) ? 2 : 3;
}

PATHNODE *__cdecl GetNextPath()
{
	PATHNODE *result; // eax

	result = *(PATHNODE **)(*(_DWORD *)&path_2_nodes[0].f + 48);
	if ( result )
	{
		*(_DWORD *)(*(_DWORD *)&path_2_nodes[0].f + 48) = (unsigned int)result->NextNode;
		result->NextNode = pnode_ptr->NextNode;
		pnode_ptr->NextNode = result;
	}
	return result;
}

bool __fastcall path_solid_pieces(PATHNODE *pPath, int dx, int dy)
{
	bool result; // eax
	int dir; // ecx
	int v8; // ecx
	int v10; // edx

	result = 1;
	dir = path_directions[3 * (dy - pPath->y) - pPath->x + 4 + dx] - 5;
	if ( !dir )
	{
		result = 0;
		if ( nSolidTable[dPiece[dx][dy + 1]] )
			return result;
		v8 = dPiece[dx + 1][dy];
		goto LABEL_13;
	}
	dir--;
	if ( !dir )
	{
		v10 = dPiece[dx][dy + 1];
		goto LABEL_9;
	}
	dir--;
	if ( !dir )
	{
		v10 = dPiece[dx][dy-1]; /* check */
LABEL_9:
		result = 0;
		if ( nSolidTable[v10] )
			return result;
		v8 = dPiece[dx-4][dy]; /* check */
		goto LABEL_13;
	}
	if ( dir == 1 )
	{
		result = 0;
		if ( !nSolidTable[dPiece[dx + 1][dy]] )
		{
			v8 = dPiece[dx][dy-1]; /* check */
LABEL_13:
			if ( nSolidTable[v8] == result )
				result = 1;
			return result;
		}
	}
	return result;
}

/* get path from (x,y) to pPath's destination, using PosOk to check each step
 * return 1 if no path was found
 */
int __fastcall path_get_path(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y)
{
	int dx;
	int dy;

	// try moving every direction from the path's destination
	for (int i = 0; i < DIRECTIONS; ++i)
	{
		dx = pPath->x + pathxdir[i];
		dy = pPath->y + pathydir[i];

		// if position is OK
		if ( PosOk(PosOkArg, dx, dy) )
		{
			// check that it is a solid piece of path?
			if ( !path_solid_pieces(pPath, dx, dy) ) continue;
		}
		else
		{
			// otherwise it's OK if that's our starting point
			// TODO it would probably be okay if the previous conditions were an &&
			if ( dx != x || dy != y ) continue;
		}

		// this direction could work, try getting the rest of the path?
		if ( !path_parent_path(pPath, dx, dy, x, y) ) return 0;
	}

	// no path in any direction
	return 1;
}


int __fastcall path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy)
{
	PATHNODE *v7; // esi

	// current path cost plus next step
	int g_next = pPath->g + path_check_equal(pPath, dx, dy);

	if ( v7 = path_get_node1(dx, dy) )
	{
		int v8 = 0;
		struct PATHNODE** v9 = pPath->Child;
		do
		{
			if ( !*v9 )
				break;
			++v8;
			++v9;
		}
		while ( v8 < 8 );
		pPath->Child[v8] = v7;
		if ( g_next < v7->g )
		{
			if ( path_solid_pieces(pPath, dx, dy) )
			{
				v7->Parent = pPath;
				v7->g = g_next;
				v7->f = v7->g + v7->h;
			}
		}
	}
	else
	{
		PATHNODE* v11 = path_get_node2(dx, dy);
		if ( v11 )
		{
			int v12 = 0;
			struct PATHNODE** v13 = pPath->Child;
			do
			{
				if ( !*v13 )
					break;
				++v12;
				++v13;
			}
			while ( v12 < 8 );
			pPath->Child[v12] = v11;
			if ( g_next < v11->g && path_solid_pieces(pPath, dx, dy) )
			{
				v11->Parent = pPath;
				v11->g = g_next;
				v11->f = v11->g + v11->h;
				path_set_coords(v11);
			}
		}
		else
		{
			PATHNODE* result = path_new_step();
			PATHNODE* v16 = result;
			if ( !result )
				return 0;
			result->Parent = pPath;
			result->g = g_next;
			v16->h = path_get_h_cost(dx, dy, sx, sy);
			v16->f = g_next + v16->h;
			v16->x = dx;
			v16->y = dy;
			path_next_node(v16);
			int v18 = 0;
			struct PATHNODE** v19 = pPath->Child;
			do
			{
				if ( !*v19 )
					break;
				++v18;
				++v19;
			}
			while ( v18 < 8 );
			pPath->Child[v18] = v16;
		}
	}
	return 1;
}

PATHNODE *__fastcall path_get_node1(int dx, int dy)
{
	PATHNODE *result; // eax

	result = *(PATHNODE **)&path_2_nodes[0].f;
	do
		result = result->NextNode;
	while ( result && (result->x != dx || result->y != dy) );
	return result;
}

PATHNODE *__fastcall path_get_node2(int dx, int dy)
{
	PATHNODE *result; // eax

	result = pnode_ptr;
	do
		result = result->NextNode;
	while ( result && (result->x != dx || result->y != dy) );
	return result;
}

void __fastcall path_next_node(PATHNODE *pPath)
{
	PATHNODE *v1; // edx
	PATHNODE *v2; // eax

	v1 = *(PATHNODE **)&path_2_nodes[0].f;
	v2 = *(PATHNODE **)(*(_DWORD *)&path_2_nodes[0].f + 48);
	if ( v2 )
	{
		do
		{
			if ( v2->f >= pPath->f )
				break;
			v1 = v2;
			v2 = v2->NextNode;
		}
		while ( v2 );
		pPath->NextNode = v2;
	}
	v1->NextNode = pPath;
}

void __fastcall path_set_coords(PATHNODE *pPath)
{
	PATHNODE *PathOld; // edi
	PATHNODE *PathAct; // esi
	char v6; // al
	int i; // [esp+0h] [ebp-8h]
	PATHNODE **v9; // [esp+4h] [ebp-4h]

	path_push_active_step(pPath);
	while ( gdwCurPathStep )
	{
		PathOld = path_pop_active_step();
		v9 = PathOld->Child;
		for(i = 0; i < 8; i++)
		{
			PathAct = *v9;
			if ( !*v9 )
				break;

			if ( PathOld->g + path_check_equal(PathOld, PathAct->x, PathAct->y) < PathAct->g )
			{
				if ( path_solid_pieces(PathOld, PathAct->x, PathAct->y) )
				{
					PathAct->Parent = PathOld;
					v6 = PathOld->g + path_check_equal(PathOld, PathAct->x, PathAct->y);
					PathAct->g = v6;
					PathAct->f = v6 + PathAct->h;
					path_push_active_step(PathAct);
				}
			}
			++v9;
		}
	}
}

void __fastcall path_push_active_step(PATHNODE *pPath)
{
	int v1; // eax

	v1 = gdwCurPathStep++;
	pnode_tblptr[v1] = pPath;
}

PATHNODE *__cdecl path_pop_active_step()
{
	return pnode_tblptr[--gdwCurPathStep];
}

PATHNODE *__cdecl path_new_step()
{
	PATHNODE *v1; // esi

	if ( pnode_vals[0] == 300 )
		return 0;
	v1 = &path_nodes[pnode_vals[0]++];
	memset(v1, 0, 0x34u);
	return v1;
}
