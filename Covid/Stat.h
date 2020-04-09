#pragma once

#include "common.h"
#include <vector>
#include <numeric>
#include <iostream>


namespace Stat {
	struct Statistic {
		f64 num_susceptible = 0;
		f64 num_removed = 0;
		f64 num_steps = 0;

		Statistic operator+ (const Statistic &rhs) const;
		Statistic operator- (const Statistic &rhs) const;
		Statistic operator* (const Statistic &rhs) const;
		Statistic operator* (const f32 &rhs) const ;

		template<typename gentype>
		Statistic operator/ (const gentype &t) const {
			return {
				num_susceptible / t,
				num_removed / t,
				num_steps / t,

			};
		}
	};

	Statistic sqrt(const Statistic &s);
	
	Statistic sample_mean(const std::vector<Statistic> &stats);
	Statistic sample_variance(const Statistic &sample_mean, const std::vector<Statistic> &stats);
	
	template<typename T>
	T t_half_interval(f32 t_value, T std, int n) {
		return (std / std::sqrt(n)) * t_value;
	}

	void print_stat(const Statistic &s);
}