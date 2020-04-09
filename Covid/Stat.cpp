#include "Stat.h"
#include <random>

Stat::Statistic Stat::Statistic::operator+(const Stat::Statistic &rhs) const {
	return {
		num_susceptible + rhs.num_susceptible,
		num_removed + rhs.num_removed,
		num_steps + rhs.num_steps,

	};
}

Stat::Statistic Stat::Statistic::operator-(const Stat::Statistic &rhs) const {
	return {
		num_susceptible - rhs.num_susceptible,
		num_removed - rhs.num_removed,
		num_steps - rhs.num_steps,

	};
}

Stat::Statistic Stat::Statistic::operator*(const Stat::Statistic &rhs) const {
	return {
		num_susceptible * rhs.num_susceptible,
		num_removed * rhs.num_removed,
		num_steps * rhs.num_steps,

	};
}

Stat::Statistic Stat::Statistic::operator*(const f32 &rhs) const {
	return {
		num_susceptible * rhs,
		num_removed * rhs,
		num_steps * rhs,

	};
}

Stat::Statistic Stat::sqrt(const Stat::Statistic &s) {
	return {
		std::sqrt(s.num_susceptible),
		std::sqrt(s.num_removed),
		std::sqrt(s.num_steps)
	};
}

Stat::Statistic Stat::sample_mean(const std::vector<Stat::Statistic> &stats) {
	const auto sum = std::reduce(stats.begin(), stats.end(), Stat::Statistic());
	return sum / stats.size();
}

Stat::Statistic Stat::sample_variance(const Stat::Statistic &sample_mean, const std::vector<Stat::Statistic> &stats) {
	const auto square_error = [sample_mean](const auto &value) {
		const auto delta = value - sample_mean;
		return delta * delta;
	};

	const auto reduce = [&](const auto prev, const auto s2) {
		const auto error = square_error(s2);
		return prev + error;
	};

	const auto total_square_error = std::accumulate(stats.begin(), stats.end(), Stat::Statistic(), reduce);
	return total_square_error / (stats.size() - 1);
}

void Stat::print_stat(const Statistic &s) {
	std::cout << "susceptible: " << s.num_susceptible << " removed: " << s.num_removed << " steps: " << s.num_steps << '\n';
}