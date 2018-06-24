//HEADER_GOES_HERE

#include "../types.h"

PATHNODE path_nodes[300];
int gdwCurPathStep;
int pnode_vals[26];
PATHNODE *pnode_ptr;
PATHNODE *pnode_tblptr[300];
PATHNODE path_2_nodes[300];

// Diablo is on a square grid, so the player can move in 8 different directions
#define NUM_DIRS 8

char pathxdir[NUM_DIRS] = { -1, -1, 1, 1, -1, 0, 1, 0 };
char pathydir[NUM_DIRS] = { -1, 1, -1, 1, 0, -1, 0, 1 };

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
	// see path_check_equal for why this is times 2
	return 2 * (delta_x + delta_y);
}

/* return 2 if pPath is horizontally/vertically aligned with (dx, dy), else 3.
 *
 * This is to approximate that diagonal movement should have a cost of sqrt(2).
 * That's approx. 1.5, so they multiply all step costs by 2 except diagonals
 * which are multiplied by 3
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

/* Extend pPath towards (x,y) by running a single step of A* breadth-first
 * search. Return 1 if pPath is a dead end
 */
int __fastcall path_get_path(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y)
{
	int dx;
	int dy;

	// try moving every direction from the path's current end
	for (int i = 0; i < NUM_DIRS; ++i)
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
			/* if (dx,dy) is where we want to go we don't care that it's not OK
			 * TODO could probably safely combine this whole thing into one check:
			 * if (((ok && solid) || equal) && !parent) return 0
			 */
			if ( dx != x || dy != y ) continue;
		}

		// this direction could work, try to extend pPath in that direction
		if ( !path_parent_path(pPath, dx, dy, x, y) ) return 0;
	}

	// no path in any direction
	return 1;
}

/* add a step to (dx,dy) to pPath, return 1 if successful */
int __fastcall path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy)
{
	PATHNODE *next_node;
	int empty_slot;

	// current path cost plus next step to get to (dx,dy)
	int g_next = pPath->g + path_check_equal(pPath, dx, dy);

	// if the search has already visited this node?
	if ( next_node = path_get_node1(dx, dy) )
	{
		// find the next open child slot
		/* TODO no point in checking empty_slot < NUM_DIRS. It should
		 * always be true, and if it isn't that's probably a crash!
		 */
		for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
		pPath->Child[empty_slot] = next_node;

		// if we just found a faster path to (dx,dy)
		if ( g_next < next_node->g && path_solid_pieces(pPath, dx, dy) )
		{
			// update the path/cost for getting there
			next_node->Parent = pPath;
			next_node->g = g_next;
			next_node->f = next_node->g + next_node->h;
		}

		return 1;
	}

	// if we have a leftover node from a previous search?
	if ( next_node = path_get_node2(dx, dy) )
	{
		for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
		pPath->Child[empty_slot] = next_node;

		if ( g_next < next_node->g && path_solid_pieces(pPath, dx, dy) )
		{
			next_node->Parent = pPath;
			next_node->g = g_next;
			next_node->f = next_node->g + next_node->h;
			// clear (dx,dy)'s old info???
			path_set_coords(next_node);
		}

		return 1;
	}

	// else we need a new node
	next_node = path_new_step();
	if ( !next_node ) return 0;

	next_node->Parent = pPath;
	next_node->g = g_next;
	next_node->h = path_get_h_cost(dx, dy, sx, sy);
	next_node->f = next_node->g + next_node->h;
	next_node->x = dx;
	next_node->y = dy;
	path_next_node(next_node);

	for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
	pPath->Child[empty_slot] = next_node;

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
	pnode_tblptr[gdwCurPathStep++] = pPath;
}

PATHNODE *__cdecl path_pop_active_step()
{
	return pnode_tblptr[--gdwCurPathStep];
}

PATHNODE *__cdecl path_new_step()
{
	if ( pnode_vals[0] == 300 ) return 0;
	PATHNODE* new_node = &path_nodes[pnode_vals[0]++];
	memset(new_node, 0, sizeof(struct PATHNODE));
	return new_node;
}
