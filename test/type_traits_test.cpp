// <copyright file="type_traits_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <array>
#include <list>
#include <vector>

#include <CppUnitTest.h>

#include "visus/lhs/is_iterable.h"
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

    };

}
