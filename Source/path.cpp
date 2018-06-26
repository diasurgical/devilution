//HEADER_GOES_HERE

#include "../types.h"

// preallocated nodes, all searches are terminated after visiting 300 nodes
PATHNODE path_nodes[300];

int pnode_vals[26];

// all visited nodes
PATHNODE *pnode_ptr;
// a stack for recursively processing nodes
PATHNODE *pnode_tblptr[300];
// the stack size
int gdwCurPathStep;

// the A* frontier sorted by distance, so we can just keep popping the next node to explore off the front
PATHNODE* frontier_ptr;

// Diablo is on a square grid, so the player can move in 8 different directions
#define NUM_DIRS 8

// these are for iterating through the 8 adjacent directions
char pathxdir[NUM_DIRS] = { -1, -1, 1, 1, -1, 0, 1, 0 };
char pathydir[NUM_DIRS] = { -1, 1, -1, 1, 0, -1, 0, 1 };

/* rdata */
char path_directions[9] = { 5, 1, 6, 2, 0, 3, 8, 4, 7 };

int __fastcall FindPath(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, int sx, int sy, int dx, int dy, char *path)
{
	pnode_vals[0] = 0; // empty the preallocated path nodes
	gdwCurPathStep = 0; // empty the pnode_tableptr stack
	// create dummy nodes for the two node lists?
	frontier_ptr = path_new_step();
	pnode_ptr = path_new_step();

	// create a node for the path's starting position
	PATHNODE* path_start = path_new_step();
	path_start->g = 0;
	path_start->h = path_get_h_cost(sx, sy, dx, dy);
	path_start->x = sx;
	path_start->f = path_start->g + path_start->h;
	path_start->y = sy;
	// it is our frontier
	frontier_ptr->NextNode = path_start;

	PATHNODE *current;
	while ( true )
	{
		// get the next frontier node
		current = GetNextPath();
		// frontier is empty, no path
		if ( !current ) return 0;
		// we've reached our destination, we're done
		if ( current->x == dx && current->y == dy ) break;
		// we ran out of preallocated nodes while searching, no path
		if ( !path_get_path(PosOk, PosOkArg, current, dx, dy) ) return 0;
	}
	PATHNODE* destination = current;
	PATHNODE* previous = destination->Parent;

	int v15 = 0;
	if ( previous )
	{
		bool v16;
		while ( 1 )
		{
			v16 = v15 == 25;
			if ( v15 >= 25 )
				break;
			pnode_vals[++v15] = path_directions[
				3 * (destination->y - previous->y + 1) + (destination->x - previous->x + 1)
			];
			destination = previous;
			previous = destination->Parent;
			if ( !previous )
			{
				v16 = v15 == 25;
				break;
			}
		}
		if ( v16 )
			return 0;
	}

	int result = 0;
	int *v17;
	if ( v15 > 0 )
	{
		v17 = &pnode_vals[v15];
		do
		{
			char v18 = *(_BYTE *)v17;
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

/* if the frontier is not empty, remove the first node (shortest distance),
 * insert it at the head of pnode's list, and return it
 */
PATHNODE *__cdecl GetNextPath()
{
	PATHNODE* result = frontier_ptr->NextNode;
	if ( result )
	{
		frontier_ptr->NextNode = result->NextNode;
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

/* Extend pPath towards (x,y) by expanding in every possible direction i.e. a
 * single step of A* breadth-first search.
 *
 * return 0 if we're out of preallocated nodes to use, else 1
 */
int __fastcall path_get_path(bool (__fastcall *PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y)
{
	// try moving every direction from the path's current end
	for (int i = 0; i < NUM_DIRS; ++i)
	{
		int dx = pPath->x + pathxdir[i];
		int dy = pPath->y + pathydir[i];

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

		/* This direction could work, extend pPath in that direction.
		 * This only fails if we're out of path nodes to use, so abort
		 * in that case
		 */
		if ( !path_parent_path(pPath, dx, dy, x, y) ) return 0;
	}

	// successfully expanded in every possible direction
	return 1;
}

/* add a step from pPath to (dx,dy), return 1 if successful, update the
 * frontier/visited nodes accordingly
 */
int __fastcall path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy)
{
	PATHNODE *dxdy_node;
	int empty_slot;

	// current path cost plus next step to get to (dx,dy)
	int g_next = pPath->g + path_check_equal(pPath, dx, dy);

	/* if (dx,dy) is on the frontier it's easy: just update that one node
	 * because we haven't explored from it yet
	 */
	if ( dxdy_node = path_get_node1(dx, dy) )
	{
		for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
		pPath->Child[empty_slot] = dxdy_node;

		// it is a shortcut
		if ( g_next < dxdy_node->g && path_solid_pieces(pPath, dx, dy) )
		{
			// update the path/cost for getting there
			dxdy_node->Parent = pPath;
			dxdy_node->g = g_next;
			dxdy_node->f = dxdy_node->g + dxdy_node->h;
		}

		return 1;
	}

	/* if (dx,dy) has already been visited, it's hard: we need to
	 * recursively update nodes starting from (dx,dy) because we might have
	 * found a new shortcut
	 */
	if ( dxdy_node = path_get_node2(dx, dy) )
	{
		for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
		pPath->Child[empty_slot] = dxdy_node;

		// it is a shortcut
		if ( g_next < dxdy_node->g && path_solid_pieces(pPath, dx, dy) )
		{
			dxdy_node->Parent = pPath;
			dxdy_node->g = g_next;
			dxdy_node->f = dxdy_node->g + dxdy_node->h;
			// update all of this node's neighbors
			path_set_coords(dxdy_node);
		}

		return 1;
	}

	// else just get a new node
	dxdy_node = path_new_step();
	if ( !dxdy_node ) return 0;

	dxdy_node->Parent = pPath;
	dxdy_node->g = g_next;
	dxdy_node->h = path_get_h_cost(dx, dy, sx, sy);
	dxdy_node->f = dxdy_node->g + dxdy_node->h;
	dxdy_node->x = dx;
	dxdy_node->y = dy;
	// and add it to the frontier
	path_next_node(dxdy_node);

	for (empty_slot = 0; empty_slot < NUM_DIRS && pPath->Child[empty_slot]; ++empty_slot);
	pPath->Child[empty_slot] = dxdy_node;

	return 1;
}

// return a node for (dx,dy) on the frontier, or NULL if not found
PATHNODE *__fastcall path_get_node1(int dx, int dy)
{
	for (PATHNODE* result = frontier_ptr->NextNode; result; result = result->NextNode )
	{
		if ( result->x == dx && result->y == dy )
		{
			return result;
		}
	}
	return NULL;
}

// return an already visited node for (dx,dy), or NULL if not found
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

/* Insert pPath into the frontier list such that the total path costs are in
 * ascending order
 */
void __fastcall path_next_node(PATHNODE *pPath)
{
	PATHNODE* current = frontier_ptr;
	PATHNODE* next = frontier_ptr->NextNode;
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

/* push pPath onto the pnode_tblptr stack */
void __fastcall path_push_active_step(PATHNODE *pPath)
{
	pnode_tblptr[gdwCurPathStep++] = pPath;
}

/* pop and return a node from the pnode_tblptr stack */
PATHNODE *__cdecl path_pop_active_step()
{
	return pnode_tblptr[--gdwCurPathStep];
}

/* zero one of the 300 preallocated path nodes and return a pointer to it, or
 * NULL if none are available
 */
PATHNODE *__cdecl path_new_step()
{
	if ( pnode_vals[0] == 300 ) return NULL;
	PATHNODE* new_node = &path_nodes[pnode_vals[0]++];
	memset(new_node, 0, sizeof(struct PATHNODE));
	return new_node;
}
