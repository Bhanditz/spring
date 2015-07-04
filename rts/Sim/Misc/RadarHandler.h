/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef RADARHANDLER_H
#define RADARHANDLER_H

#include <boost/noncopyable.hpp>

#include "Sim/Misc/LosMap.h"
#include "Sim/Units/Unit.h"
#include "System/myMath.h"

// Because submerged units are only given LOS if they are also
// in sonar range (see LosHandler.h), sonar stealth and sonar
// jammed units can not be detected (probably why those 2 features
// are not being used by most mods). Uncommenting the following
// line will allow the LOS display mode to differentiate between
// radar and sonar coverage, and radar and sonar jammer coverage.

// #define RADARHANDLER_SONAR_JAMMER_MAPS


class CRadarHandler : public boost::noncopyable
{
	CR_DECLARE_STRUCT(CRadarHandler)


public:
	CRadarHandler(bool circularRadar);
	~CRadarHandler();

	void MoveUnit(CUnit* unit);
	void RemoveUnit(CUnit* unit);

	inline int GetSquare(const float3& pos) const
	{
		const int gx = pos.x * invRadarDiv;
		const int gz = pos.z * invRadarDiv;
		const int colIdx = Clamp(gx, 0, xsize - 1);
		const int rowIdx = Clamp(gz, 0, zsize - 1);
		return (rowIdx * xsize) + colIdx;
	}

	bool InRadar(const float3 pos, int allyTeam) const;
	bool InRadar(const CUnit* unit, int allyTeam) const;


	// returns whether a square is being radar- or sonar-jammed
	// (even when the square is not in radar- or sonar-coverage)
	bool InJammer(const float3 pos, int allyTeam) const;
	bool InJammer(const CUnit* unit, int allyTeam) const {
		return (InJammer(unit->pos, allyTeam));
	}


	bool InSeismicDistance(const CUnit* unit, int allyTeam) const {
		return (seismicMaps[allyTeam][GetSquare(unit->pos)] != 0);
	}

	// default operations for targeting-facilities
	void IncreaseAllyTeamRadarErrorSize(int allyTeam) { radarErrorSizes[allyTeam] *= baseRadarErrorMult; }
	void DecreaseAllyTeamRadarErrorSize(int allyTeam) { radarErrorSizes[allyTeam] /= baseRadarErrorMult; }

	// API functions
	void SetAllyTeamRadarErrorSize(int allyTeam, float size) { radarErrorSizes[allyTeam] = size; }
	float GetAllyTeamRadarErrorSize(int allyTeam) const { return radarErrorSizes[allyTeam]; }

	void SetBaseRadarErrorSize(float size) { baseRadarErrorSize = size; }
	void SetBaseRadarErrorMult(float mult) { baseRadarErrorMult = mult; }
	float GetBaseRadarErrorSize() const { return baseRadarErrorSize; }
	float GetBaseRadarErrorMult() const { return baseRadarErrorMult; }

public:
	int radarMipLevel;
	int radarDiv;
	float invRadarDiv;
	bool circularRadar;

	std::vector<CLosMap> radarMaps;
	std::vector<CLosMap> airRadarMaps;
	std::vector<CLosMap> sonarMaps;
	std::vector<CLosMap> jammerMaps;
#ifdef RADARHANDLER_SONAR_JAMMER_MAPS
	std::vector<CLosMap> sonarJammerMaps;
#endif
	std::vector<CLosMap> seismicMaps;
	CLosMap commonJammerMap;
	CLosMap commonSonarJammerMap;
	std::vector<float> radarErrorSizes;

	int xsize;
	int zsize;

private:
	CLosAlgorithm radarAlgo;

	float baseRadarErrorSize;
	float baseRadarErrorMult;
};

extern CRadarHandler* radarHandler;

#endif /* RADARHANDLER_H */
