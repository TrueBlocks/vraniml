#ifndef __IMPORTING_H
#define __IMPORTING_H

extern vrNode *parse_nff(FILE *in, vrAxisAlignedBox& box);
extern vrNode *parse_tbl(FILE *in, vrAxisAlignedBox& box);
extern vrNode *parse_geo(FILE *in, vrAxisAlignedBox& box);

#endif