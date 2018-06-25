//HEADER_GOES_HERE

#include "../types.h"

PATHNODE path_nodes[300];
int gdwCurPathStep;
int pnode_vals[26];
PATHNODE *pnode_ptr;
PATHNODE *pnode_tblptr[300];
PATHNODE* global_node;

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
	global_node = path_new_step();
	gdwCurPathStep = 0;
	pnode_ptr = path_new_step();
	v8 = path_new_step();
	v8->g = 0;
	v9 = path_get_h_cost(sx, sy, dx, dy);
	v8->h = v9;
	v8->x = sx;
	v8->f = v9 + v8->g;
	v8->y = sy;
	global_node->NextNode = v8;
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

/* if global is not empty, remove the first node, insert it at the head of
 * pnode's list, and return it
 */
PATHNODE *__cdecl GetNextPath()
{
	PATHNODE* result = global_node->NextNode;
	if ( result )
	{
		global_node->NextNode = result->NextNode;
		result->NextNode = pnode_ptr->NextNode;
		pnode_ptr->NextNode = result;
	}
	return result;
}

/* Make sure the path isn't cutting a corner. If you want to move from
 * A to B, both Xs need to be clear:
 *
 *    XA
 *    BX
 *
 * return true if the path is allowed.
 */
bool __fastcall path_solid_pieces(PATHNODE *pPath, int dx, int dy)
{
	if (path_check_equal(pPath, dx, dy) == 2) return 1;
	return !(nSolidTable[dPiece[dx][pPath->y]] || nSolidTable[dPiece[pPath->x][dy]]);
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
			// check that we aren't cutting a corner
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

// return a node in the global list at (dx,dy), or NULL if not found
PATHNODE *__fastcall path_get_node1(int dx, int dy)
{
	for (PATHNODE* result = global_node->NextNode; result; result = result->NextNode )
	{
		if ( result->x == dx && result->y == dy )
		{
			return result;
		}
	}
	return NULL;
}

// return a node in the pnode list at (dx,dy), or NULL if not found
PATHNODE *__fastcall path_get_node2(int dx, int dy)
{
	for (PATHNODE* result = pnode_ptr->NextNode; result; result = result->NextNode )
	{
		if ( result->x == dx && result->y == dy )
		{
			return result;
		}
	}
	return NULL;
}

/* Insert pPath into the global list such that the total path costs are in
 * ascending order
 */
void __fastcall path_next_node(PATHNODE *pPath)
{
	PATHNODE* current = global_node;
	PATHNODE* next = global_node->NextNode;
	if ( next )
	{
		while ( next && next->f < pPath->f )
		{
			current = next;
			next = current->NextNode;
		}
		pPath->NextNode = next;
	}
	current->NextNode = pPath;
}

/* update all path costs using depth-first search starting at pPath */
void __fastcall path_set_coords(PATHNODE *pPath)
{
	path_push_active_step(pPath);
	// while stack is nonempty
	while ( gdwCurPathStep )
	{
		PATHNODE* PathOld = path_pop_active_step();
		// iterate over next node's children
		PATHNODE* PathAct;
		for (int i = 0; i < 8 && (PathAct = PathOld->Child[i]); ++i)
		{
			short g_next = PathOld->g + path_check_equal(PathOld, PathAct->x, PathAct->y);
			// if we found a faster path to the child
			if ( g_next < PathAct->g && path_solid_pieces(PathOld, PathAct->x, PathAct->y) )
			{
				// update it
				PathAct->Parent = PathOld;
				PathAct->g = g_next;
				PathAct->f = g_next + PathAct->h;
				// add it to the stack
				path_push_active_step(PathAct);
			}
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
