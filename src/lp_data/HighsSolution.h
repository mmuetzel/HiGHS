/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file lp_data/HighsSolution.h
 * @brief Class-independent utilities for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef LP_DATA_HIGHSSOLUTION_H_
#define LP_DATA_HIGHSSOLUTION_H_

#include <vector>
#include <string>
//
#include "lp_data/HighsLp.h"
#include "ipm/IpxSolution.h"
#include "lp_data/HighsOptions.h"
#ifdef IPX_ON
#include "ipm/IpxStatus.h"
#include "ipm/ipx/include/ipx_status.h"
#include "ipm/ipx/src/lp_solver.h"
#endif

void zeroSolutionIterationCountParams(HighsSolutionParams& solution_params);

void zeroSolutionStatusParams(HighsSolutionParams& solution_params);
void zeroSolutionParams(HighsSolutionParams& solution_params);

void copyToSolutionParams(HighsSolutionParams& solution_params, const HighsOptions& options, const HighsSimplexInfo& simplex_info);

#ifdef IPX_ON
void copyToSolutionParams(HighsSolutionParams& solution_params, const HighsOptions& options, const ipx::Info& ipx_info);
#endif

void copyFromSolutionParams(HighsSimplexInfo& simplex_info, const HighsSolutionParams& solution_params);

void copyFromSolutionParams(HighsInfo& highs_info, const HighsSolutionParams& solution_params);
#ifdef IPX_ON
HighsStatus ipxToHighsBasicSolution(const HighsLp& lp,
				    const std::vector<double>& rhs,
				    const std::vector<char>& constraint_type,
				    const IpxSolution& ipx_solution,
				    HighsBasis& highs_basis,
				    HighsSolution& highs_solution);
#endif    

bool analyseVarBasicSolution(
			bool report,
			const double primal_feasibility_tolerance,
			const double dual_feasibility_tolerance,
			const HighsBasisStatus status,
			const double lower,
			const double upper,
			const double value,
			const double dual,
			int& num_non_basic_var,
			int& num_basic_var,
			double& off_bound_nonbasic,
			double& primal_infeasibility,
			double& dual_infeasibility);

std::string iterationsToString(const HighsSolutionParams& solution_params);

// Analyse the HiGHS basic solution of the given LP. Currently only
// used with the unscaled LP, but would work just as well with a
// scaled LP. The primal and dual feasibility tolerances are passed in
// via solution_params, which returns the int and double data obtained
// about the solution. The overall model status is returned in the
// argument.
HighsModelStatus analyseHighsBasicSolution(const HighsLp& lp,
					   const HighsBasis& basis,
					   const HighsSolution& solution,
					   HighsSolutionParams& solution_params,
					   const int report_level,
					   const string message);
#endif  // LP_DATA_HIGHSSOLUTION_H_
