// <copyright file="maximin_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/maximin.h"
#include "visus/lhs/random.h"

#include "reference_distribution.h"

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

        TEST_METHOD(test_build_against_r) {
            reference_distribution dist(1976, 1968);
            matrix<std::size_t> lhs(4, 3);
            maximin(lhs, 5, std::mt19937(42), dist);
            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

            // Expected values from https://github.com/bertcarnell/lhslib/blob/557bec455c5bf2d20438bbace2096c2a7e3823ff/src/lhstest/maximinLHS_RTest.cpp#L43-L46
            // Note that R uses one-based indices whereas we use zero-based ones.
            Assert::AreEqual(std::size_t(3), lhs[0], L"0", LINE_INFO());
            Assert::AreEqual(std::size_t(0), lhs[1], L"1", LINE_INFO());
            Assert::AreEqual(std::size_t(2), lhs[2], L"2", LINE_INFO());
            Assert::AreEqual(std::size_t(1), lhs[3], L"3", LINE_INFO());
            Assert::AreEqual(std::size_t(3), lhs[4], L"4", LINE_INFO());
            Assert::AreEqual(std::size_t(0), lhs[5], L"5", LINE_INFO());
            Assert::AreEqual(std::size_t(0), lhs[6], L"6", LINE_INFO());
            Assert::AreEqual(std::size_t(2), lhs[7], L"7", LINE_INFO());
            Assert::AreEqual(std::size_t(3), lhs[8], L"8", LINE_INFO());
            Assert::AreEqual(std::size_t(2), lhs[9], L"9", LINE_INFO());
            Assert::AreEqual(std::size_t(1), lhs[10], L"10", LINE_INFO());
            Assert::AreEqual(std::size_t(1), lhs[11], L"11", LINE_INFO());
        }
    };

}
