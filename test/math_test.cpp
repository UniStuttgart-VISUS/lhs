// <copyright file="math_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>

#include <CppUnitTest.h>

#include "visus/lhs/matrix.h"
#include "visus/lhs/distance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;
using namespace visus::lhs::detail;


namespace test {

    TEST_CLASS(math_test) {

        TEST_METHOD(test_square) {
            Assert::AreEqual(0, square(0), L"0", LINE_INFO());
            Assert::AreEqual(1, square(1), L"1", LINE_INFO());
            Assert::AreEqual(4, square(2), L"2", LINE_INFO());
            Assert::AreEqual(2.25f, square(1.5f), 0.001f, L"1.5", LINE_INFO());
        }

        TEST_METHOD(test_square_difference) {
            Assert::AreEqual(0, square_difference(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(1, square_difference(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1, square_difference(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(4, square_difference(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(4, square_difference(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(2.25f, square_difference(2.5f, 1.0f), 0.001f, L"2.5, 1.0", LINE_INFO());
            Assert::AreEqual(2.25f, square_difference(1.0f, 2.5f), 0.001f, L"1.0, 2.5", LINE_INFO());
        }

        TEST_METHOD(test_vector_square_distance) {
            {
                std::vector<float> lhs = { 0.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(0.0f, square_distance(lhs, rhs), L"0, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 1.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(1.0f, square_distance(lhs, rhs), L"1, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 1.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 1.0f };
                Assert::AreEqual(2.0f, square_distance(lhs, rhs), L"1, 0; 0, 1", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 2.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(4.0f, square_distance(lhs, rhs), L"2, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 2.0f, 0.0f };
                std::vector<float> rhs = { 1.0f, 1.0f };
                Assert::AreEqual(2.0f, square_distance(lhs, rhs), L"2, 0; 1, 1", LINE_INFO());
            }
        }

        TEST_METHOD(test_iterator_square_distance) {
            {
                std::vector<float> lhs = { 0.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(0.0f, square_distance(lhs.begin(), lhs.end(), rhs.begin()), L"0, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 1.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(1.0f, square_distance(lhs.begin(), lhs.end(), rhs.begin()), L"1, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 1.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 1.0f };
                Assert::AreEqual(2.0f, square_distance(lhs.begin(), lhs.end(), rhs.begin()), L"1, 0; 0, 1", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 2.0f, 0.0f };
                std::vector<float> rhs = { 0.0f, 0.0f };
                Assert::AreEqual(4.0f, square_distance(lhs.begin(), lhs.end(), rhs.begin()), L"2, 0; 0, 0", LINE_INFO());
            }

            {
                std::vector<float> lhs = { 2.0f, 0.0f };
                std::vector<float> rhs = { 1.0f, 1.0f };
                Assert::AreEqual(2.0f, square_distance(lhs.begin(), lhs.end(), rhs.begin()), L"2, 0; 1, 1", LINE_INFO());
            }
        }

        TEST_METHOD(test_matrix_square_distance) {
            {
                matrix<float> lhs(3, 3, 0.0f);
                matrix<float> rhs(3, 3, 0.0f);
                Assert::AreEqual(0.0f, square_distance(lhs.begin_row(0), lhs.end_row(0), rhs.begin_row(0)), L"0, 0, 0; 0, 0, 0", LINE_INFO());
            }

            {
                matrix<float> lhs(3, 3, 0.0f);
                matrix<float> rhs(3, 3, 1.0f);
                Assert::AreEqual(3.0f, square_distance(lhs.begin_row(1), lhs.end_row(1), rhs.begin_row(1)), L"0, 0, 0; 1, 1, 1", LINE_INFO());
            }

            {
                matrix<float> lhs(3, 3, 0.0f);
                matrix<float> rhs(3, 3, 2.0f);
                Assert::AreEqual(12.0f, square_distance(lhs.begin_row(2), lhs.end_row(2), rhs.begin_row(2)), L"0, 0, 0; 2, 2, 2", LINE_INFO());
            }
        }

        TEST_METHOD(test_matrix_row_distances) {
            {
                matrix<float> mat(3, 3, 0.0f);
                std::vector<float> result;
                square_row_distances(result, mat);
                Assert::AreEqual(static_cast<std::size_t>(3), result.size(), L"# of distances", LINE_INFO());
                Assert::IsTrue(std::all_of(result.begin(), result.end(), [](float d) { return (d == 0.0f); }), L"All zero", LINE_INFO());
            }

            {
                matrix<float> mat(5, 1, [](std::size_t r, std::size_t c) { return static_cast<float>(r); });
                std::vector<float> result;
                square_row_distances(result, mat);
                Assert::AreEqual(static_cast<std::size_t>(10), result.size(), L"# of distances", LINE_INFO());

                Assert::AreEqual(1.0f, result[0], L"0 -> 1", LINE_INFO());
                Assert::AreEqual(4.0f, result[1], L"0 -> 2", LINE_INFO());
                Assert::AreEqual(9.0f, result[2], L"0 -> 3", LINE_INFO());
                Assert::AreEqual(16.0f, result[3], L"0 -> 4", LINE_INFO());

                Assert::AreEqual(1.0f, result[4], L"1 -> 2", LINE_INFO());
                Assert::AreEqual(4.0f, result[5], L"1 -> 3", LINE_INFO());
                Assert::AreEqual(9.0f, result[6], L"1 -> 4", LINE_INFO());

                Assert::AreEqual(1.0f, result[7], L"2 -> 3", LINE_INFO());
                Assert::AreEqual(4.0f, result[8], L"2 -> 4", LINE_INFO());

                Assert::AreEqual(1.0f, result[9], L"3 -> 4", LINE_INFO());
            }

            {
                matrix<float> mat(3, 2, [](std::size_t r, std::size_t c) { return static_cast<float>(r); });
                std::vector<float> result;
                square_row_distances(result, mat);
                Assert::AreEqual(static_cast<std::size_t>(3), result.size(), L"# of distances", LINE_INFO());

                Assert::AreEqual(2.0f, result[0], L"0 -> 1", LINE_INFO());
                Assert::AreEqual(8.0f, result[1], L"0 -> 2", LINE_INFO());

                Assert::AreEqual(2.0f, result[0], L"1 -> 1", LINE_INFO());
            }
        }
    };

}
