// <copyright file="test_random.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(test_random) {

        TEST_METHOD(test_indices) {
            const auto lhs = random(4, 3, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));

            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[1] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[2] < 4, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[1] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[2] < 4, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[1] < 4, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[2] < 4, L"Output in valid range", LINE_INFO());
            }
        }

        TEST_METHOD(test_unit) {
            const auto lhs = random(4, 3, false, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));

            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

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

        TEST_METHOD(test_unit_preserve_draw) {
            const auto lhs = random(4, 3, true, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));

            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

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

        TEST_METHOD(test_unit_preserve_draw_uniform) {
            const auto lhs = random<float>(4, 3, true, std::mt19937(0));

            Assert::IsTrue(valid(lhs), L"Sample is valid", LINE_INFO());

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

        TEST_METHOD(test_range) {
            std::vector<range<float>> parameters{
                make_range(0.0f, 1.0f),
                make_range(1.0f, 2.0f),
                make_range(2.0f, 3.0f)
            };
            const auto lhs = random(4,
                parameters.begin(),
                parameters.end(),
                false,
                std::mt19937(0),
                std::uniform_real_distribution<float>(0.0f, 1.0f));

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }
        }

        TEST_METHOD(test_range_initialiser) {
            const auto lhs = random(4,
                { make_range(0.0f, 1.0f), make_range(1.0f, 2.0f), make_range(2.0f, 3.0f) },
                false,
                std::mt19937(0),
                std::uniform_real_distribution<float>(0.0f, 1.0f));

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Values for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Values for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Values for all parameters", LINE_INFO());
                Assert::IsTrue((sample[0] >= 0.0f) && (sample[0] <= 1.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[1] >= 1.0f) && (sample[1] <= 2.0f), L"Output in valid range", LINE_INFO());
                Assert::IsTrue((sample[2] >= 2.0f) && (sample[2] <= 3.0f), L"Output in valid range", LINE_INFO());
            }
        }

        TEST_METHOD(test_discrete_range) {
            std::vector<std::size_t> parameter_expressions { 3, 42, 9 };
            const auto lhs = random(4,
                parameter_expressions.begin(),
                parameter_expressions.end(),
                false,
                std::mt19937(0),
                std::uniform_real_distribution<float>(0.0f, 1.0f));

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }
        }

        TEST_METHOD(test_discrete_range_initialiser) {
            const auto lhs = random(4,
                { 3, 42, 9 },
                false,
                std::mt19937(0),
                std::uniform_real_distribution<float>(0.0f, 1.0f));

            {
                const auto sample = lhs.row(0);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(1);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }

            {
                const auto sample = lhs.row(2);
                Assert::AreEqual(std::size_t(3), sample.size(), L"Indices for all parameters", LINE_INFO());
                Assert::IsTrue(sample[0] < 3, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 42, L"Output in valid range", LINE_INFO());
                Assert::IsTrue(sample[0] < 9, L"Output in valid range", LINE_INFO());
            }
        }

    };

}
