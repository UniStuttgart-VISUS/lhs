// <copyright file="matrix_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(matrix_test) {

        TEST_METHOD(test_dimensions) {
            {
                matrix<float> m(3, 4);
                Assert::AreEqual(static_cast<std::size_t>(3), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(4), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
            }

            {
                matrix<float> m(4, 3);
                Assert::AreEqual(static_cast<std::size_t>(4), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(3), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
            }
        }

        TEST_METHOD(test_indexers_row_major) {
            matrix<float, matrix_layout::row_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::row_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(0.1f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(0.2f, m[2], L"2", LINE_INFO());
            Assert::AreEqual(0.3f, m[3], L"3", LINE_INFO());

            Assert::AreEqual(1.0f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(1.1f, m[5], L"5", LINE_INFO());
            Assert::AreEqual(1.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.3f, m[7], L"7", LINE_INFO());

            Assert::AreEqual(2.0f, m[8], L"8", LINE_INFO());
            Assert::AreEqual(2.1f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(2.2f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_indexers_colum_major) {
            matrix<float, matrix_layout::column_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::column_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(1.0f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(2.0f, m[2], L"2", LINE_INFO());

            Assert::AreEqual(0.1f, m[3], L"3", LINE_INFO());
            Assert::AreEqual(1.1f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(2.1f, m[5], L"5", LINE_INFO());

            Assert::AreEqual(0.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.2f, m[7], L"7", LINE_INFO());
            Assert::AreEqual(2.2f, m[8], L"8", LINE_INFO());

            Assert::AreEqual(0.3f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(1.3f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_fill) {
            matrix<float> m(3, 4);
            m.fill(42.0f);

            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 3), L"2, 3", LINE_INFO());
        }

        TEST_METHOD(test_equality) {
            matrix<float> m1(3, 4);
            m1.fill(42.0f);

            matrix<float> m2(3, 4);
            Assert::IsFalse(m1 == m2, L"m1 == m2", LINE_INFO());

            m2 = m1;
            Assert::IsTrue(m1 == m2, L"m1 == m2", LINE_INFO());

            matrix<float> m3(4, 3);
            m3.fill(42.0f);
            Assert::IsFalse(m1 == m3, L"m1 == m3", LINE_INFO());
        }

        TEST_METHOD(test_row) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }
        }

        TEST_METHOD(test_column) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }
        }

        TEST_METHOD(test_diagonal) {
            auto m = matrix<float>::diagonal(4, 42.0f);
            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(3, 3), L"3, 3", LINE_INFO());
        }

        TEST_METHOD(test_identity) {
            auto m = matrix<float>::identity(4);
            Assert::AreEqual(1.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(1.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(1.0f, m(3, 3), L"3, 3", LINE_INFO());
        }
    };

}
