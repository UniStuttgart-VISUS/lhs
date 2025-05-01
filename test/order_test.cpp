// <copyright file="order_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

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

    };

}
