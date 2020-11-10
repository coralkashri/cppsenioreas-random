#ifndef CPPSENIOREAS_RANDOM_MY_RANDOM_H
#define CPPSENIOREAS_RANDOM_MY_RANDOM_H

#include <iostream>
#include <random>
#include <map>

template <typename DistType>
class my_random {
public:
    template<typename ...DistArgs>
    my_random(DistArgs &&...dist_args) : eng(r()), uniform_dist(std::forward<DistArgs>(dist_args)...) {}

    typename DistType::result_type gen() { return uniform_dist(eng); }

    template<typename ...DistArgs>
    void new_dist(DistArgs &&...dist_args) {
        uniform_dist = DistType(std::forward<DistArgs>(dist_args)...);
    }

    void distribution_test(size_t repetitions = 10000000, double printing_ratio = 0.0001) {
        std::map<int, int> hist;
        size_t rel_prints = repetitions * printing_ratio;
        if (!rel_prints) rel_prints = 1;
        for (int n = 0; n < repetitions; ++n) {
            ++hist[std::round(gen())];
        }
        std::cout << "Distribution Test: \n";
        for (auto p : hist) {
            std::cout << p.first << ' ' << std::string(p.second / rel_prints, '*') << '\n';
        }
    }

private:
    std::random_device r;
    std::default_random_engine eng;
    DistType uniform_dist;
};

#endif //CPPSENIOREAS_RANDOM_MY_RANDOM_H