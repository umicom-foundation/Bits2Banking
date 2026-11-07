/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/rust-activity/main.rs
 *
 * PURPOSE:
 *   Display results returned by the shared C activity model through Rust.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


mod activity;

fn main() {
    for current in [0, 41, 999, 1000] {
        match activity::advance(current) {
            Ok(next) => println!("{current} -> {next}"),
            Err(activity::ActivityError::Refused) => println!("{current} -> refused"),
        }
    }
}

