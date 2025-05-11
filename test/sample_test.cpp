// <copyright file="sample_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/random.h"
#include "visus/lhs/sample.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(sample_test) {

        TEST_METHOD(test_ranges) {
            auto lhs = sample(
                [](const std::size_t p) { return random<float>(4, p); },
                make_range(0.0f, 1.0f),
                make_range(1, 100));

            Assert::IsTrue((std::get<0>(lhs[0]) >= 0.0f) && (std::get<0>(lhs[0]) <= 1.0f), L"0, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[0]) >= 1) && (std::get<1>(lhs[0]) < 100), L"0, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[1]) >= 0.0f) && (std::get<0>(lhs[1]) <= 1.0f), L"1, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[1]) >= 1) && (std::get<1>(lhs[1]) < 100), L"1, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[2]) >= 0.0f) && (std::get<0>(lhs[2]) <= 1.0f), L"2, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[2]) >= 1) && (std::get<1>(lhs[2]) < 100), L"2, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[3]) >= 0.0f) && (std::get<0>(lhs[3]) <= 1.0f), L"3, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[3]) >= 1) && (std::get<1>(lhs[3]) < 100), L"3, 1", LINE_INFO());
        }

        TEST_METHOD(test_vector_range) {
            auto lhs = sample(
                [](const std::size_t p) { return random<float>(4, p); },
                std::vector<std::string>({ "horst", "hugo" }),
                make_range(1, 100));

            Assert::IsTrue((std::get<0>(lhs[0]) == "horst") || (std::get<0>(lhs[0]) == "hugo"), L"0, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[0]) >= 1) && (std::get<1>(lhs[0]) < 100), L"0, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[1]) == "horst") || (std::get<0>(lhs[1]) == "hugo"), L"1, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[1]) >= 1) && (std::get<1>(lhs[1]) < 100), L"1, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[2]) == "horst") || (std::get<0>(lhs[2]) == "hugo"), L"2, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[2]) >= 1) && (std::get<1>(lhs[2]) < 100), L"2, 1", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[3]) == "horst") || (std::get<0>(lhs[3]) == "hugo"), L"3, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[3]) >= 1) && (std::get<1>(lhs[3]) < 100), L"3, 1", LINE_INFO());
        }

        TEST_METHOD(test_initialisers) {
            auto lhs = sample(
                [](const std::size_t p) { return random<float>(2, p); },
                std::initializer_list<int> { 1, 2, 3 },
                std::initializer_list<float> { 1.0f, 2.0f, 3.0f },
                std::initializer_list<bool> { true, false });

            Assert::IsTrue((std::get<0>(lhs[0]) >= 1) || (std::get<0>(lhs[0]) <= 3), L"0, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[0]) >= 1.0f) && (std::get<1>(lhs[0]) <= 3.0f), L"0, 1", LINE_INFO());
            Assert::IsTrue(std::get<2>(lhs[0]) || !std::get<2>(lhs[0]), L"0, 2", LINE_INFO());

            Assert::IsTrue((std::get<0>(lhs[1]) >= 1) || (std::get<0>(lhs[1]) <= 3), L"1, 0", LINE_INFO());
            Assert::IsTrue((std::get<1>(lhs[1]) >= 1.0f) && (std::get<1>(lhs[1]) <= 3.0f), L"1, 1", LINE_INFO());
            Assert::IsTrue(std::get<2>(lhs[1]) || !std::get<2>(lhs[1]), L"1, 2", LINE_INFO());
        }
    };

}
