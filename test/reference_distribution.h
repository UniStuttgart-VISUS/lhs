// <copyright file="reference_distribution.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <random>


namespace test {

    /// <summary>
    /// Implements the distribution used by the R implementation for reference.
    /// </summary>
    /// <remarks>
    /// This is very hacky. Do not use in production.
    /// </remarks>
    class reference_distribution final {

    public:

        typedef double result_type;
        struct param_type {

            inline explicit param_type(
                    _In_ const unsigned int seed1 = 1234,
                    _In_ const unsigned int seed2 = 5678)
                : seed1(seed1), seed2(seed2) { }

            unsigned int seed1;
            unsigned int seed2;
        };

        inline explicit reference_distribution(
                _In_ const unsigned int seed1 = 1234,
                _In_ const unsigned int seed2 = 5678)
            : _params(seed1, seed2) { }

        inline explicit reference_distribution(_In_ const param_type& params)
            : _params(params) { }

        inline result_type max() const noexcept {
            return 1.0;
        }

        inline result_type min() const noexcept {
            return 0.0;
        }

        template<class TRng> inline result_type operator ()(TRng& rng) {
            this->_params.seed1 = 36969 * (this->_params.seed1 & 0177777) + (this->_params.seed1 >> 16);
            this->_params.seed2 = 18000 * (this->_params.seed2 & 0177777) + (this->_params.seed2 >> 16);
            return ((this->_params.seed1 << 16) ^ (this->_params.seed2 & 0177777)) * 2.328306437080797e-10; /* in [0,1) */
        }

    private:

        param_type _params;
    };

}
