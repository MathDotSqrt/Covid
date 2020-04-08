#include "Stat.h"
#include <random>

Stat::Statistic Stat::Statistic::operator+(const Stat::Statistic &rhs) {
	return {
		num_susceptible + rhs.num_susceptible,
		num_removed + rhs.num_removed,
		num_steps + rhs.num_steps,

	};
}

Stat::Statistic Stat::Statistic::operator-(const Stat::Statistic &rhs) {
	return {
		num_susceptible - rhs.num_susceptible,
		num_removed - rhs.num_removed,
		num_steps - rhs.num_steps,

	};
}

Stat::Statistic Stat::Statistic::operator*(const Stat::Statistic &rhs) {
	return {
		num_susceptible * rhs.num_susceptible,
		num_removed * rhs.num_removed,
		num_steps * rhs.num_steps,

	};
}

Stat::Statistic Stat::addStat(const Stat::Statistic &s1, const Stat::Statistic &s2) {
	const Stat::Statistic out{
			s1.num_susceptible + s2.num_susceptible,
			s1.num_removed + s2.num_removed,
			s1.num_steps + s2.num_steps
	};
	return out;
}

Stat::Statistic Stat::subStat(const Stat::Statistic &s1, const Stat::Statistic &s2) {
	const Stat::Statistic out{
		s1.num_susceptible - s2.num_susceptible,
		s1.num_removed - s2.num_removed,
		s1.num_steps - s2.num_steps
	};
	return out;
}

Stat::Statistic Stat::mulStat(const Statistic &s1, const Statistic &s2) {
	const Stat::Statistic out{
		s1.num_susceptible * s2.num_susceptible,
		s1.num_removed * s2.num_removed,
		s1.num_steps * s2.num_steps
	};
	return out;
}

Stat::Statistic Stat::divStat(const Statistic &s1, const Statistic &s2) {
	const Stat::Statistic out{
		s1.num_susceptible / s2.num_susceptible,
		s1.num_removed / s2.num_removed,
		s1.num_steps / s2.num_steps
	};
	return out;
}

Stat::Statistic Stat::divStat(const Statistic &s1, int d) {
	const Stat::Statistic out{
		s1.num_susceptible / d,
		s1.num_removed / d,
		s1.num_steps / d
	};
	return out;
}

Stat::Statistic Stat::sample_mean(const std::vector<Stat::Statistic> &stats) {
	const auto sum = std::reduce(stats.begin(), stats.end(), Stat::Statistic(), Stat::addStat);
	return divStat(sum, stats.size());
}

Stat::Statistic Stat::sample_variance(const Stat::Statistic &sample_mean, const std::vector<Stat::Statistic> &stats) {
	const auto square_error = [sample_mean](const auto &value) {
		const auto delta = Stat::subStat(value, sample_mean);
		std::cout << "sample_mean ";  Stat::print_stat(sample_mean);
		std::cout << "value ";  Stat::print_stat(value);
		std::cout << "delta ";  Stat::print_stat(delta);
		return Stat::mulStat(delta, delta);
	};

	const auto reduce = [&](const auto s1, const auto s2) {
		const auto error = square_error(s2);
		return addStat(s1, error);
	};

	const auto total_square_error = std::accumulate(stats.begin(), stats.end(), Stat::Statistic(), reduce);
	std::cout << stats.size() << '\n';
	std::cout << "total_square_error: ";
	Stat::print_stat(total_square_error);

	return divStat(total_square_error, stats.size()-1);
}

void Stat::print_stat(const Statistic &s) {
	std::cout << "susceptible: " << s.num_susceptible << " removed: " << s.num_removed << " steps: " << s.num_steps << '\n';
}