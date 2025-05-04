// <copyright file="type_traits_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <array>
#include <cinttypes>
#include <list>
#include <vector>

#include <CppUnitTest.h>

#include "visus/lhs/is_iterable.h"
#include "visus/lhs/is_range.h"
#include "visus/lhs/make_floating_point.h"
#include "visus/lhs/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(type_traits_test) {

        TEST_METHOD(test_is_iterable) {
            Assert::IsTrue(is_iterable_v<std::vector<int>>, L"vector<int>", LINE_INFO());
            Assert::IsTrue(is_iterable_v<std::vector<float>>, L"vector<float>", LINE_INFO());
            Assert::IsTrue(is_iterable_v<std::array<float, 3>>, L"std::array<float, 3>", LINE_INFO());
            Assert::IsTrue(is_iterable_v<matrix<float>>, L"matrix<float>", LINE_INFO());
            Assert::IsFalse(is_iterable_v<int>, L"int", LINE_INFO());
        }

        TEST_METHOD(test_is_range) {
            Assert::IsTrue(is_range_v<range<float>>, L"range<float>", LINE_INFO());
            Assert::IsTrue(is_range_v<range<int>>, L"range<int>", LINE_INFO());
            Assert::IsFalse(is_range_v<float>, L"float", LINE_INFO());
            Assert::IsFalse(is_range_v<int>, L"int", LINE_INFO());
        }

        TEST_METHOD(test_make_float) {
            Assert::IsTrue(std::is_same_v<float, make_floating_point_t<float>>, L"float", LINE_INFO());
            Assert::IsTrue(std::is_same_v<double, make_floating_point_t<double>>, L"double", LINE_INFO());
            Assert::IsTrue(std::is_same_v<float, make_floating_point_t<std::uint16_t>>, L"uint16_t", LINE_INFO());
            Assert::IsTrue(std::is_same_v<float, make_floating_point_t<std::uint32_t>>, L"uint32_t", LINE_INFO());
            Assert::IsTrue(std::is_same_v<double, make_floating_point_t<std::uint64_t>>, L"uint64_t", LINE_INFO());
            Assert::IsTrue(std::is_same_v<float, make_floating_point_t<std::int16_t>>, L"int16_t", LINE_INFO());
            Assert::IsTrue(std::is_same_v<float, make_floating_point_t<std::int32_t>>, L"int32_t", LINE_INFO());
            Assert::IsTrue(std::is_same_v<double, make_floating_point_t<std::int64_t>>, L"int64_t", LINE_INFO());
        }
    };

}
