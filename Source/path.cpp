//HEADER_GOES_HERE

#include "../types.h"

// preallocated nodes, search is terminated after 300 nodes are visited
PATHNODE path_nodes[MAXPATHNODES];
// size of the pnode_tblptr stack
int gdwCurPathStep;
// the number of in-use nodes in path_nodes
int gdwCurNodes;
/* for reconstructing the path after the A* search is done. The longest
 * possible path is actually 24 steps, even though we can fit 25
 */
int pnode_vals[25];
// a linked list of all visited nodes
PATHNODE *pnode_ptr;
// a stack for recursively searching nodes
PATHNODE *pnode_tblptr[MAXPATHNODES];
// a linked list of the A* frontier, sorted by distance
PATHNODE *path_2_nodes;

// for iterating over the 8 possible movement directions
const char pathxdir[8] = { -1, -1, 1, 1, -1, 0, 1, 0 };
const char pathydir[8] = { -1, 1, -1, 1, 0, -1, 0, 1 };

/* data */

/* each step direction is assigned a number like this:
 *       dx
 *     -1 0 1
 *     +-----
 *   -1|5 1 6
 * dy 0|2 0 3
 *    1|8 4 7
 */
char path_directions[9] = { 5, 1, 6, 2, 0, 3, 8, 4, 7 };

/* find the shortest path from (sx,sy) to (dx,dy), using PosOk(PosOkArg,x,y) to
 * check that each step is a valid position. Store the step directions (see
 * path_directions) in path, which must have room for 24 steps
 */
int FindPath(BOOL(*PosOk)(int, int, int), int PosOkArg, int sx, int sy, int dx, int dy, char *path)
{
	PATHNODE *path_start; // esi
	char initial_h;       // al
	PATHNODE *next_node;  // eax
	int result;           // eax
	PATHNODE *current;    // edx
	PATHNODE **previous;  // eax
	int path_length;      // edi
	BOOLEAN path_is_full; // zf
	int *step_ptr;        // ecx
	char step;            // dl

	// clear all nodes, create root nodes for the visited/frontier linked lists
	gdwCurNodes = 0;
	path_2_nodes = path_new_step();
	gdwCurPathStep = 0;
	pnode_ptr = path_new_step();
	path_start = path_new_step();
	path_start->g = 0;
	initial_h = path_get_h_cost(sx, sy, dx, dy);
	path_start->h = initial_h;
	path_start->x = sx;
	path_start->f = initial_h + path_start->g;
	path_start->y = sy;
	path_2_nodes->NextNode = path_start;
	// A* search until we find (dx,dy) or fail
	while (TRUE) {
		next_node = GetNextPath();
		// frontier is empty, no path!
		if (!next_node)
			return 0;
		// reached the end, success!
		if (next_node->x == dx && next_node->y == dy)
			break;
		// ran out of nodes, abort!
		if (!path_get_path(PosOk, PosOkArg, next_node, dx, dy))
			return 0;
	}
	current = next_node;
	previous = &next_node->Parent;
	path_length = 0;
	if (*previous) {
		while (TRUE) {
			path_is_full = path_length == 25;
			if (path_length >= 25)
				break;
			pnode_vals[++path_length - 1] = path_directions[3 * (current->y - (*previous)->y) - (*previous)->x + 4 + current->x];
			current = *previous;
			previous = &(*previous)->Parent;
			if (!*previous) {
				path_is_full = path_length == 25;
				break;
			}
		}
		if (path_is_full)
			return 0;
	}
	result = 0;
	if (path_length > 0) {
		step_ptr = &pnode_vals[path_length - 1];
		do {
			step = *(_BYTE *)step_ptr;
			--step_ptr;
			path[result++] = step;
		} while (result < path_length);
	}
	return result;
}

/* heuristic, estimated cost from (sx,sy) to (dx,dy) */
int path_get_h_cost(int sx, int sy, int dx, int dy)
{
	int delta_x = abs(sx - dx);
	int delta_y = abs(sy - dy);

	int min = delta_x < delta_y ? delta_x : delta_y;
	int max = delta_x > delta_y ? delta_x : delta_y;

	// see path_check_equal for why this is times 2
	return 2 * (min + max);
}

/* return 2 if pPath is horizontally/vertically aligned with (dx,dy), else 3
 *
 * This approximates that diagonal movement on a square grid should have a cost
 * of sqrt(2). That's approximately 1.5, so they multiply all step costs by 2,
 * except diagonal steps which are times 3
 */
int path_check_equal(PATHNODE *pPath, int dx, int dy)
{
	if (pPath->x == dx || pPath->y == dy)
		return 2;

	return 3;
}

/* get the next node on the A* frontier to explore (estimated to be closest to
 * the goal), mark it as visited, and return it
 */
PATHNODE *GetNextPath()
{
	PATHNODE *result;

	result = path_2_nodes->NextNode;
	if (result == NULL) {
		return result;
	}

	path_2_nodes->NextNode = result->NextNode;
	result->NextNode = pnode_ptr->NextNode;
	pnode_ptr->NextNode = result;
	return result;
}

/* check if stepping from pPath to (dx,dy) cuts a corner. If you step from A to
 * B, both Xs need to be clear:
 *
 *  AX
 *  XB
 *
 *  return true if step is allowed
 */
BOOL path_solid_pieces(PATHNODE *pPath, int dx, int dy)
{
	BOOL rv = TRUE;
	switch (path_directions[3 * (dy - pPath->y) + 3 - pPath->x + 1 + dx]) {
	case 5:
		rv = !nSolidTable[dPiece[dx][dy + 1]] && !nSolidTable[dPiece[dx + 1][dy]];
		break;
	case 6:
		rv = !nSolidTable[dPiece[dx][dy + 1]] && !nSolidTable[dPiece[dx - 1][dy]];
		break;
	case 7:
		rv = !nSolidTable[dPiece[dx][dy - 1]] && !nSolidTable[dPiece[dx - 1][dy]];
		break;
	case 8:
		rv = !nSolidTable[dPiece[dx + 1][dy]] && !nSolidTable[dPiece[dx][dy - 1]];
		break;
	}
	return rv;
}

/* perform a single step of A* bread-first search by trying to step in every
 * possible direction from pPath with goal (x,y). Check each step with PosOk
 *
 * return 0 if we ran out of preallocated nodes to use, else 1
 */
BOOL path_get_path(BOOL(*PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y)
{
	int dx, dy;
	int i;
	BOOL ok;

	for (i = 0; i < 8; i++) {
		dx = pPath->x + pathxdir[i];
		dy = pPath->y + pathydir[i];
		ok = PosOk(PosOkArg, dx, dy);
		if (ok && path_solid_pieces(pPath, dx, dy) || !ok && dx == x && dy == y) {
			if (!path_parent_path(pPath, dx, dy, x, y))
				return FALSE;
		}
	}

	return TRUE;
}

/* add a step from pPath to (dx,dy), return 1 if successful, and update the
 * frontier/visited nodes accordingly
 *
 * return 1 if step successfully added, 0 if we ran out of nodes to use
 */
BOOL path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy)
{
	int next_g;
	PATHNODE *dxdy;
	int i;

	next_g = pPath->g + path_check_equal(pPath, dx, dy);

	// 3 cases to consider
	// case 1: (dx,dy) is already on the frontier
	dxdy = path_get_node1(dx, dy);
	if (dxdy != NULL) {
		for (i = 0; i < 8; i++) {
			if (pPath->Child[i] == NULL)
				break;
		}
		pPath->Child[i] = dxdy;
		if (next_g < dxdy->g) {
			if (path_solid_pieces(pPath, dx, dy)) {
				// we'll explore it later, just update
				dxdy->Parent = pPath;
				dxdy->g = next_g;
				dxdy->f = next_g + dxdy->h;
			}
		}
	} else {
		// case 2: (dx,dy) was already visited
		dxdy = path_get_node2(dx, dy);
		if (dxdy != NULL) {
			for (i = 0; i < 8; i++) {
				if (pPath->Child[i] == NULL)
					break;
			}
			pPath->Child[i] = dxdy;
			if (next_g < dxdy->g && path_solid_pieces(pPath, dx, dy)) {
				// update the node
				dxdy->Parent = pPath;
				dxdy->g = next_g;
				dxdy->f = next_g + dxdy->h;
				// already explored, so re-update others starting from that node
				path_set_coords(dxdy);
			}
		} else {
			// case 3: (dx,dy) is totally new
			dxdy = path_new_step();
			if (dxdy == NULL)
				return FALSE;
			dxdy->Parent = pPath;
			dxdy->g = next_g;
			dxdy->h = path_get_h_cost(dx, dy, sx, sy);
			dxdy->f = next_g + dxdy->h;
			dxdy->x = dx;
			dxdy->y = dy;
			// add it to the frontier
			path_next_node(dxdy);

			for (i = 0; i < 8; i++) {
				if (pPath->Child[i] == NULL)
					break;
			}
			pPath->Child[i] = dxdy;
		}
	}
	return TRUE;
}

/* return a node for (dx,dy) on the frontier, or NULL if not found */
PATHNODE *path_get_node1(int dx, int dy)
{
	PATHNODE *result = path_2_nodes;
	while (result != NULL && (result->x != dx || result->y != dy))
		result = result->NextNode;
	return result;
}

/* return a node for (dx,dy) if it was visited, or NULL if not found */
PATHNODE *path_get_node2(int dx, int dy)
{
	PATHNODE *result = pnode_ptr;
	while (result != NULL && (result->x != dx || result->y != dy))
		result = result->NextNode;
	return result;
}

/* insert pPath into the frontier (keeping the frontier sorted by total
 * distance) */
void path_next_node(PATHNODE *pPath)
{
	PATHNODE *current; // edx
	PATHNODE *next;    // eax

	current = path_2_nodes;
	next = path_2_nodes->NextNode;
	if (next != NULL) {
		do {
			if (next->f >= pPath->f)
				break;
			current = next;
			next = next->NextNode;
		} while (next != NULL);
		pPath->NextNode = next;
	}
	current->NextNode = pPath;
}

/* update all path costs using depth-first search starting at pPath */
void path_set_coords(PATHNODE *pPath)
{
	PATHNODE *PathOld;
	PATHNODE *PathAct;
	int i;

	path_push_active_step(pPath);
	while (gdwCurPathStep) {
		PathOld = path_pop_active_step();
		for (i = 0; i < 8; i++) {
			PathAct = PathOld->Child[i];
			if (PathAct == NULL)
				break;

			if (PathOld->g + path_check_equal(PathOld, PathAct->x, PathAct->y) < PathAct->g) {
				if (path_solid_pieces(PathOld, PathAct->x, PathAct->y)) {
					PathAct->Parent = PathOld;
					PathAct->g = PathOld->g + path_check_equal(PathOld, PathAct->x, PathAct->y);
					PathAct->f = PathAct->g + PathAct->h;
					path_push_active_step(PathAct);
				}
			}
		}
	}
}

/* push pPath onto the pnode_tblptr stack */
void path_push_active_step(PATHNODE *pPath)
{
	int stack_index = gdwCurPathStep;
	gdwCurPathStep++;
	pnode_tblptr[stack_index] = pPath;
}

/* pop and return a node from the pnode_tblptr stack */
PATHNODE *path_pop_active_step()
{
	gdwCurPathStep--;
	return pnode_tblptr[gdwCurPathStep];
}

/* zero one of the preallocated nodes and return a pointer to it, or NULL if
 * none are available */
PATHNODE *path_new_step()
{
	PATHNODE *new_node;

	if (gdwCurNodes == MAXPATHNODES)
		return NULL;

	new_node = &path_nodes[gdwCurNodes];
	gdwCurNodes++;
	memset(new_node, 0, sizeof(PATHNODE));
	return new_node;
}
