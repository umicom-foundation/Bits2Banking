// -----------------------------------------------------------------------------
// Umicom Bits2Banking
// File: labs/mobile/iphone-framework-activity/ActivityView.swift
//
// PURPOSE:
//   Present shared C activity results with SwiftUI on an iPhone target.
//
// AUTHOR AND ORGANISATION:
// Sammy Hegab
// Umicom Foundation
//
// LICENCE:
// MIT
// -----------------------------------------------------------------------------
import SwiftUI

struct ActivityView: View {
    @State private var completed: CInt = 0
    @State private var message = "Ready"

    var body: some View {
        VStack(spacing: 16) {
            Text("Completed exercises: \(completed)")
            Button("Complete exercise") {
                // Swift owns screen state; the existing C model decides the result.
                let next = BtbActivityNext(completed)
                if next >= 0 {
                    completed = next
                    message = "Exercise recorded"
                } else {
                    message = "No change: check the count or begin another activity"
                }
            }
            Text(message)
        }
        .padding()
    }
}

