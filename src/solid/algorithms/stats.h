#ifndef __STATS_H3D
#define __STATS_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#define _STATS 1

#ifdef _STATS

class CClassifyStats
{
public:
	long nVertsA;
	long nVertsB;
	long nVertsV;
	long nEdgesA;
	long nEdgesB;
	long vf_neighbors;
	long vf_wide;
	long vf_onsectors;
	long vf_onedges;
	long vf_nocrossings;
	long vf_crossings;
	long vf_dangling;
	long vf_sameface;
	long vv_neighbors;
	long vv_wide;
	long vv_onsectors;
	long vv_onedges;
	long vv_nocrossings;

		CClassifyStats(void)
			{
				nVertsA = 0; nVertsB = 0; nVertsV = 0; nEdgesA = 0; nEdgesB = 0;
				vf_neighbors = 0; vf_wide = 0; vf_onsectors = 0; vf_onedges = 0; vf_nocrossings = 0; vf_crossings = 0; vf_dangling = 0; vf_sameface = 0;
				vv_neighbors = 0; vv_wide = 0; vv_onsectors = 0; vv_onedges = 0; vv_nocrossings = 0;
			}
};

class CGenerateStats
{
public:
	long edgesA;
	long edgesB;
	long facesA;
	long facesB;
	long tests;
	long edgefacecross;
	long ef_contains;
	long ef_facehits;
	long ef_edgehits;
	long ef_verthits;
	long ef_loophits;
	long vertonface;
	long vf_contains;
	long vf_facehits;
	long vf_edgehits;
	long vf_verthits;
	long vf_loophits;
	long vf_calls;
	long vv_calls;
	long vf_addsA;
	long vf_addsB;
	long vv_addsA;
	long vv_addsB;
		CGenerateStats(void)
			{
				edgesA = 0;        edgesB = 0;      facesA = 0;      facesB = 0;      tests = 0;
				edgefacecross = 0; ef_contains = 0; ef_facehits = 0; ef_edgehits = 0; ef_verthits = 0; ef_loophits = 0;
				vertonface = 0;    vf_contains = 0; vf_facehits = 0; vf_edgehits = 0; vf_verthits = 0; vf_loophits = 0;
				vf_calls = 0;      vv_calls = 0;    vf_addsA = 0;    vf_addsB = 0;    vv_addsA = 0;    vv_addsB = 0;
			}
};

class CConnectStats
{
	long i;
};

class CFinishStats
{
	long i;
};

class CCompleteStats
{
	long i;
};

class CStatistics
{
public:
	CGenerateStats gen;
	CClassifyStats cl;
	CConnectStats  con;
	CFinishStats   fin;
	CCompleteStats com;
};

#endif

#endif