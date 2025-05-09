// <copyright file="maximin_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/maximin.h"
#include "visus/lhs/random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(maximin_test) {

        TEST_METHOD(test_optimise_unit) {
            auto lhs = random(4, 3, false, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));
            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

            std::vector<float> distances;
            square_row_distances(distances, lhs);
            const auto reference  = *std::min_element(distances.begin(), distances.end());

            maximin(lhs);
            Assert::IsTrue(valid(lhs), L"Optimised sample is still valid", LINE_INFO());

            square_row_distances(distances, lhs);
            const auto optimised = *std::min_element(distances.begin(), distances.end());
            Assert::IsTrue(optimised >= reference, L"Optimised distance is not smaller", LINE_INFO());

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 0.0f) && (sample[1] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 0.0f) && (sample[2] <= 1.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 0.0f) && (sample[1] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 0.0f) && (sample[2] <= 1.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 0.0f) && (sample[1] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 0.0f) && (sample[2] <= 1.0f), L"Output in valid range", LINE_INFO());
            }
        }

        TEST_METHOD(test_build) {
            {
                matrix<std::size_t> lhs(4, 3);
                maximin(lhs, 5, std::mt19937(42), std::uniform_real_distribution<float>(0.0f, 1.0f));
                Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());
            }

            {
                auto lhs = maximin(4, 3, 5, std::mt19937(42), std::uniform_real_distribution<float>(0.0f, 1.0f));
                Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());
            }

            {
                auto lhs = maximin(4, 3, 5, std::mt19937(42));
                Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());
            }

            {
                auto lhs = maximin(4, 3, 5);
                Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());
            }
        }
    };

}
