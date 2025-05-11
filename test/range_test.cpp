// <copyright file="range_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/range.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(range_test) {

        TEST_METHOD(test_float_ctor) {
            {
                range<float> r;
                Assert::AreEqual(0.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(0.0f, r.end(), L"end", LINE_INFO());
                Assert::IsTrue(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(0.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(0.0f, 1.0f);
                Assert::AreEqual(0.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(1.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(1.0f, 2.0f);
                Assert::AreEqual(1.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(2.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(2.0f, 1.0f);
                Assert::AreEqual(1.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(2.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }
        }

        TEST_METHOD(test_int_ctor) {
            {
                range<int> r;
                Assert::AreEqual(0, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(0, r.end(), L"end", LINE_INFO());
                Assert::IsTrue(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(0, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(0, 100);
                Assert::AreEqual(0, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(100, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(100, 200);
                Assert::AreEqual(100, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(200, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = make_range(200, 100);
                Assert::AreEqual(100, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(200, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100, r.distance(), L"distance", LINE_INFO());
            }
        }

        TEST_METHOD(test_init_ctor) {
            {
                range<int> r { 0, 0 };
                Assert::AreEqual(0, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(0, r.end(), L"end", LINE_INFO());
                Assert::IsTrue(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(0, r.distance(), L"distance", LINE_INFO());
            }

            {
                range<float> r { 0.0f, 100.0f };
                Assert::AreEqual(0.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(100.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                range<double> r { 100.0, 200.0 };
                Assert::AreEqual(100.0, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(200.0, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100.0, r.distance(), L"distance", LINE_INFO());
            }

            {
                range<int> r { 200, 100 };
                Assert::AreEqual(100, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(200, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(100, r.distance(), L"distance", LINE_INFO());
            }

            Assert::ExpectException<std::invalid_argument>([](void) {
                range<int> r = { 1 };
            }, L"Too short initialiser", LINE_INFO());
        }

        TEST_METHOD(test_float_from_dist) {
            {
                auto r = range_from_distance(0.0f, 1.0f);
                Assert::AreEqual(0.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(1.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = range_from_distance(1.0f, 1.0f);
                Assert::AreEqual(1.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(2.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }

            {
                auto r = range_from_distance(0.0f, -1.0f);
                Assert::AreEqual(-1.0f, r.begin(), L"begin", LINE_INFO());
                Assert::AreEqual(0.0f, r.end(), L"end", LINE_INFO());
                Assert::IsFalse(r.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(1.0f, r.distance(), L"distance", LINE_INFO());
            }
        }

    };

}
