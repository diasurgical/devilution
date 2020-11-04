/**
 * @file path.h
 *
 * Interface of the path finding algorithms.
 */
#ifndef __PATH_H__
#define __PATH_H__

int FindPath(BOOL (*PosOk)(int, int, int), int PosOkArg, int sx, int sy, int dx, int dy, char *path);
int path_get_h_cost(int sx, int sy, int dx, int dy);
PATHNODE *GetNextPath();
BOOL path_get_path(BOOL (*PosOk)(int, int, int), int PosOkArg, PATHNODE *pPath, int x, int y);
BOOL path_parent_path(PATHNODE *pPath, int dx, int dy, int sx, int sy);
PATHNODE *path_get_node1(int dx, int dy);
PATHNODE *path_get_node2(int dx, int dy);
void path_next_node(PATHNODE *pPath);
void path_set_coords(PATHNODE *pPath);
void path_push_active_step(PATHNODE *pPath);
PATHNODE *path_pop_active_step();
PATHNODE *path_new_step();

#endif /* __PATH_H__ */
