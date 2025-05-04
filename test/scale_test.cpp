// <copyright file="scale_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/scale.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(scale_test) {

        TEST_METHOD(test_scale_float) {
            {
                matrix<float> m(2, 2, 0.0f);
                std::initializer_list<range<float>> scales = { make_range(0.0f, 10.0f), make_range(0.0f, 100.0f) };
                scale(m, scales.begin(), scales.end());
                Assert::AreEqual(0.0f, m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(0.0f, m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(0.0f, m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(0.0f, m(0, 1), L"m(1, 1)", LINE_INFO());
            }

            {
                matrix<float> m(2, 2, 1.0f);
                std::initializer_list<range<float>> scales = { make_range(0.0f, 10.0f), make_range(0.0f, 100.0f) };
                scale(m, scales.begin(), scales.end());
                Assert::AreEqual(10.0f, m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(100.0f, m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(10.0f, m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(100.0f, m(0, 1), L"m(1, 1)", LINE_INFO());
            }
        }

        TEST_METHOD(test_scale_int) {
            {
                matrix<float> unit(2, 2, 0.0f);
                std::initializer_list<range<int>> scales = { make_range(0, 10), make_range(0, 10) };
                auto m = scale(unit, scales.begin(), scales.end());
                Assert::IsTrue(std::is_same_v<int, decltype(m)::value_type>, L"result type", LINE_INFO());
                Assert::AreEqual(0, m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(0, m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(0, m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(0, m(0, 1), L"m(1, 1)", LINE_INFO());
            }

            {
                matrix<float> unit(2, 2, 1.0f);
                std::initializer_list<range<int>> scales = { make_range(0, 10), make_range(0, 100) };
                auto m = scale(unit, scales.begin(), scales.end());
                Assert::IsTrue(std::is_same_v<int, decltype(m)::value_type>, L"result type", LINE_INFO());
                Assert::AreEqual(10, m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(100, m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(10, m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(100, m(0, 1), L"m(1, 1)", LINE_INFO());
            }
        }

        TEST_METHOD(test_scale_indices) {
            {
                matrix<float> unit(2, 2, 0.0f);
                std::initializer_list<std::uint64_t> sizes = { 10, 100 };
                auto m = scale(unit, sizes.begin(), sizes.end());
                Assert::IsTrue(std::is_same_v<uint64_t, decltype(m)::value_type>, L"result type", LINE_INFO());
                Assert::AreEqual(std::uint64_t(0), m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(0), m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(0), m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(0), m(0, 1), L"m(1, 1)", LINE_INFO());
            }

            {
                matrix<float> unit(2, 2, 1.0f);
                std::initializer_list<std::uint64_t> sizes = { 10, 100 };
                auto m = scale(unit, sizes.begin(), sizes.end());
                Assert::IsTrue(std::is_same_v<uint64_t, decltype(m)::value_type>, L"result type", LINE_INFO());
                Assert::AreEqual(std::uint64_t(9), m(0, 0), L"m(0, 0)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(99), m(0, 1), L"m(0, 1)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(9), m(1, 0), L"m(1, 0)", LINE_INFO());
                Assert::AreEqual(std::uint64_t(99), m(0, 1), L"m(1, 1)", LINE_INFO());
            }
        }
    };

}
