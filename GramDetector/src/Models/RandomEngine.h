#pragma once
#include <random>

namespace GramDetector {
	namespace Models {
		class RandomEngine {
		private:
			std::random_device dev;
			std::default_random_engine _dre;
		public:
			RandomEngine();

			std::default_random_engine& getInstance();
		};
	}
}