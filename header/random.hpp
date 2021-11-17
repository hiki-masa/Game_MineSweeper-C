#pragma once

#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <random>

using namespace std;

/* メルセンヌ・ツイスタを乱数生成器として使用 */
random_device rnd_dev; /* シード値を決めるデバイス乱数 */
mt19937 mt(rnd_dev()); /* メルセンヌ・ツイスタ */
uniform_real_distribution<> dist(0, 1); /* [0, 1]の一様乱数 */

/* 一様乱数の生成 */
inline double rnd() {
	return dist(mt);
}

#endif