// <copyright file="latin_hypercube_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(latin_hypercube_test) {

        TEST_METHOD(test_random) {
            const auto lhs = random(4, 3, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));

            {
                const auto sample = lhs.row(0);
                int x = 5;
            }

            {
                const auto sample = lhs.row(1);
                int x = 5;
            }

            {
                const auto sample = lhs.row(2);
                int x = 5;
            }

        }

    };

}
