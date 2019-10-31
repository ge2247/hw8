// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include <vector>

namespace fms::instrument {

	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	template<class U = double, class C = double>
	auto make_time(U frequency, U n) {
		int i = 0;
		std::vector<U> times;

		//Defining times
		for (i = 0; i < n + 1; i++) {
			times.emplace_back(i / frequency);//Adds elements to the end of the vector
		}

		return times;
	}

	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	template<class U = double, class C = double>
	auto make_cash(U frequency, C c, U n) {
		int i = 1;
		std::vector<C> cash;

		//Defining cash flows
		cash.emplace_back(-1);//First element
		for (i = 1; i < n; i++) {
			cash.emplace_back(c / frequency);//Adds elements to end of the vector
		}
		cash.emplace_back(1 + c / frequency);//Adds final element

		return cash;
	}

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.

	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(frequency, maturity * frequency)), fms::sequence::list<C>(make_cash(frequency, coupon, maturity * frequency))
				)
		{ }
	};
}