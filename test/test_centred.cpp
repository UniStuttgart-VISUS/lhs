// <copyright file="test_centred.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/centred.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(test_centred) {

        TEST_METHOD(test_unit) {
            const auto lhs = centred(4, 3, std::mt19937(0), std::uniform_real_distribution<float>(0.0f, 1.0f));

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

    };

}
