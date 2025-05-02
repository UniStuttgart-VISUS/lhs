// <copyright file="order_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <random>

#include <CppUnitTest.h>

#include "visus/lhs/order.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(order_test) {

        TEST_METHOD(test_order_by_inc_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
            order_by(indices, values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(0), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_by_dec_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
            order_by(indices, values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(4), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_by_rnd_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 4.0f, 5.0f, 2.0f, 1.0f, 3.0f };
            order_by(indices, values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(3), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_inc_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
            order(indices, values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_dec_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
            order(indices, values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_rnd_float) {
            std::vector<std::size_t> indices;
            std::vector<float> values = { 4.0f, 5.0f, 2.0f, 1.0f, 3.0f };
            order(indices, values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_by_inc_float_alloc) {
            std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
            auto indices = order_by(values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(0), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_by_dec_float_alloc) {
            std::vector<float> values = { 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
            auto indices = order_by(values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(4), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_by_rnd_float_alloc) {
            std::vector<float> values = { 4.0f, 5.0f, 2.0f, 1.0f, 3.0f };
            auto indices = order_by(values.begin(), values.end(), [](const float lhs, const float rhs) {
                return lhs < rhs;
            });
            Assert::AreEqual(static_cast<std::size_t>(3), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_inc_float_alloc) {
            std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
            auto indices = order(values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_dec_float_alloc) {
            std::vector<float> values = { 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
            auto indices = order(values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_order_rnd_float_alloc) {
            std::vector<float> values = { 4.0f, 5.0f, 2.0f, 1.0f, 3.0f };
            auto indices = order(values.begin(), values.end());
            Assert::AreEqual(static_cast<std::size_t>(3), indices[0], L"0", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(2), indices[1], L"1", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(4), indices[2], L"2", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(0), indices[3], L"3", LINE_INFO());
            Assert::AreEqual(static_cast<std::size_t>(1), indices[4], L"4", LINE_INFO());
        }

        TEST_METHOD(test_random_order_by_dist) {
            std::vector<std::size_t> indices(5);
            std::vector<float> buffer;
            random_order_by(indices, buffer, std::less<float>(), std::mt19937(0), std::uniform_real_distribution<float>());
            Assert::IsTrue(indices[0] < indices.size(), L"0", LINE_INFO());
            Assert::IsTrue(indices[1] < indices.size(), L"1", LINE_INFO());
            Assert::IsTrue(indices[2] < indices.size(), L"2", LINE_INFO());
            Assert::IsTrue(indices[3] < indices.size(), L"3", LINE_INFO());
            Assert::IsTrue(indices[4] < indices.size(), L"4", LINE_INFO());
        }

        TEST_METHOD(test_random_order_dist) {
            std::vector<std::size_t> indices(5);
            std::vector<float> buffer;
            random_order(indices, buffer, std::mt19937(0), std::uniform_real_distribution<float>());
            Assert::IsTrue(indices[0] < indices.size(), L"0", LINE_INFO());
            Assert::IsTrue(indices[1] < indices.size(), L"1", LINE_INFO());
            Assert::IsTrue(indices[2] < indices.size(), L"2", LINE_INFO());
            Assert::IsTrue(indices[3] < indices.size(), L"3", LINE_INFO());
            Assert::IsTrue(indices[4] < indices.size(), L"4", LINE_INFO());
        }

        TEST_METHOD(test_int_permuation) {
            {
                std::vector<std::size_t> indices;
                std::mt19937 rng(0);
                random_order(indices, 5, rng);
                Assert::AreEqual(static_cast<std::size_t>(5), indices.size(), L"size", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 0) != indices.end(), L"0", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 1) != indices.end(), L"1", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 2) != indices.end(), L"2", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 3) != indices.end(), L"3", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 4) != indices.end(), L"4", LINE_INFO());
            }

            {
                auto indices = random_order<std::size_t>(5);
                Assert::AreEqual(static_cast<std::size_t>(5), indices.size(), L"size", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 0) != indices.end(), L"0", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 1) != indices.end(), L"1", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 2) != indices.end(), L"2", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 3) != indices.end(), L"3", LINE_INFO());
                Assert::IsTrue(std::find(indices.begin(), indices.end(), 4) != indices.end(), L"4", LINE_INFO());
            }
        }

    };

}
