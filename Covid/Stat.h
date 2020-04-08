#pragma once

#include "common.h"
#include <vector>
#include <numeric>
#include <iostream>


namespace Stat {
	struct Statistic {
		f32 num_susceptible = 0;
		f32 num_removed = 0;
		f32 num_steps = 0;

		Statistic operator+ (const Statistic &rhs);
		Statistic operator- (const Statistic &rhs);
		Statistic operator* (const Statistic &rhs);

		template<typename gentype>
		Statistic operator/ (const gentype &t) {
			return {
				num_susceptible / t,
				num_removed / t,
				num_steps / t,

			};
		}
	};

	Statistic addStat(const Statistic &s1, const Statistic &s2);
	Statistic subStat(const Statistic &s1, const Statistic &s2);
	Statistic mulStat(const Statistic &s1, const Statistic &s2);
	Statistic divStat(const Statistic &s1, const Statistic &s2);
	Statistic divStat(const Statistic &s1, int d);

	Statistic sample_mean(const std::vector<Statistic> &stats);
	Statistic sample_variance(const Statistic &sample_mean, const std::vector<Statistic> &stats);
	
	Statistic t_dist() {
		std::student_t_distribution<f32> dist{};
	}

	void print_stat(const Statistic &s);
}