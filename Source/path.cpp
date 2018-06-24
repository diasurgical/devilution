//HEADER_GOES_HERE

#include "../types.h"

PATHNODE path_nodes[300];
int gdwCurPathStep;
int pnode_vals[26];
PATHNODE *pnode_ptr;
PATHNODE *pnode_tblptr[300];
PATHNODE path_2_nodes[300];

char pathxdir[8] = { -1, -1, 1, 1, -1, 0, 1, 0 };
char pathydir[8] = { -1, 1, -1, 1, 0, -1, 0, 1 };

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

int __fastcall path_check_equal(PATHNODE *pPath, int dx, int dy)
{
	int v4; // [esp-4h] [ebp-4h]

	if ( pPath->x == dx || pPath->y == dy )
		v4 = 2;
	else
		v4 = 3;
	return v4;
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

int __fastcall path_get_path(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y)
{
	int v5; // eax
	int dx; // esi
	int dy; // edi
	int i; // [esp+14h] [ebp-4h]

	v5 = 0;
	for ( i = 0; ; v5 = i )
	{
		dx = pPath->x + pathxdir[v5];
		dy = pPath->y + pathydir[v5];
		if ( !PosOk(PosOkArg, dx, dy) )
			break;
		if ( path_solid_pieces(pPath, dx, dy) )
			goto LABEL_8;
LABEL_9:
		if ( ++i >= 8 )
			return 1;
	}
	if ( dx != x || dy != y )
		goto LABEL_9;
LABEL_8:
	if ( path_parent_path(pPath, dx, dy, x, y) )
		goto LABEL_9;
	return 0;
}

int __fastcall path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy)
{
	PATHNODE *v5; // edi
	int v6; // ebx
	PATHNODE *v7; // esi
	signed int v8; // eax
	struct PATHNODE **v9; // ecx
	char v10; // al
	PATHNODE *v11; // esi
	signed int v12; // eax
	struct PATHNODE **v13; // ecx
	char v14; // al
	PATHNODE *result; // eax
	PATHNODE *v16; // esi
	char v17; // al
	signed int v18; // ecx
	struct PATHNODE **v19; // eax
	int a1; // [esp+Ch] [ebp-4h]

	a1 = dx;
	v5 = pPath;
	v6 = pPath->g + path_check_equal(pPath, dx, dy);
	v7 = path_get_node1(a1, dy);
	if ( v7 )
	{
		v8 = 0;
		v9 = v5->Child;
		do
		{
			if ( !*v9 )
				break;
			++v8;
			++v9;
		}
		while ( v8 < 8 );
		v5->Child[v8] = v7;
		if ( v6 < v7->g )
		{
			if ( path_solid_pieces(v5, a1, dy) )
			{
				v10 = v7->h;
				v7->Parent = v5;
				v7->g = v6;
				v7->f = v6 + v10;
			}
		}
	}
	else
	{
		v11 = path_get_node2(a1, dy);
		if ( v11 )
		{
			v12 = 0;
			v13 = v5->Child;
			do
			{
				if ( !*v13 )
					break;
				++v12;
				++v13;
			}
			while ( v12 < 8 );
			v5->Child[v12] = v11;
			if ( v6 < v11->g && path_solid_pieces(v5, a1, dy) )
			{
				v14 = v6 + v11->h;
				v11->Parent = v5;
				v11->g = v6;
				v11->f = v14;
				path_set_coords(v11);
			}
		}
		else
		{
			result = path_new_step();
			v16 = result;
			if ( !result )
				return 0;
			result->Parent = v5;
			result->g = v6;
			v17 = path_get_h_cost(a1, dy, sx, sy);
			v16->h = v17;
			v16->f = v6 + v17;
			v16->x = a1;
			v16->y = dy;
			path_next_node(v16);
			v18 = 0;
			v19 = v5->Child;
			do
			{
				if ( !*v19 )
					break;
				++v18;
				++v19;
			}
			while ( v18 < 8 );
			v5->Child[v18] = v16;
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
