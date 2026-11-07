/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/rust-activity/activity.rs
 *
 * PURPOSE:
 *   Wrap the existing C activity bridge in a checked Rust result.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


use std::ffi::c_int;

unsafe extern "C" {
    fn BtbActivityNext(current: c_int) -> c_int;
}

#[derive(Debug, PartialEq, Eq)]
pub enum ActivityError {
    Refused,
}

/// The C bridge owns the counting rule; this function translates its result.
pub fn advance(current: c_int) -> Result<c_int, ActivityError> {
    // SAFETY: the linked declaration matches bridge.h: one C int in and out.
    // There are no pointers, retained buffers, callbacks or shared mutable state.
    // The bridge accepts every int and reports invalid values with -1.
    let result = unsafe { BtbActivityNext(current) };
    if result < 0 { Err(ActivityError::Refused) } else { Ok(result) }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ordinary_and_final_success() {
        assert_eq!(advance(0), Ok(1));
        assert_eq!(advance(41), Ok(42));
        assert_eq!(advance(999), Ok(1000));
    }

    #[test]
    fn refuses_capacity_and_invalid_values() {
        for value in [-1, c_int::MIN, 1000, 1001, c_int::MAX] {
            assert_eq!(advance(value), Err(ActivityError::Refused));
        }
    }

    #[test]
    fn each_call_is_independent() {
        assert_eq!(advance(41), Ok(42));
        assert_eq!(advance(1000), Err(ActivityError::Refused));
        assert_eq!(advance(41), Ok(42));
    }
}

