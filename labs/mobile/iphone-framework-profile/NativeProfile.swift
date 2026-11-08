// -----------------------------------------------------------------------------
// Umicom Bits2Banking
// File: labs/mobile/iphone-framework-profile/NativeProfile.swift
//
// PURPOSE:
//   Own bounded Swift buffers around a synchronous call to the shared Framework C policy.
//
// AUTHOR AND ORGANISATION:
// Sammy Hegab
// Umicom Foundation
//
// LICENCE:
// MIT
// -----------------------------------------------------------------------------

// Swift is the iOS language boundary. The naming algorithm stays in C.
enum NativeProfile {
    static func canonical(_ input: String) -> String? {
        let capacity = Int(UMI_LOCAL_PROFILE_NAME_CAPACITY)
        // Collect one byte beyond the largest allowed name. Long input must be
        // refused, never accepted as a shortened prefix; scratch storage stays bounded.
        let bytes = Array(input.utf8.prefix(capacity))
        var output = [CChar](repeating: 0, count: capacity)
        let accepted = bytes.withUnsafeBufferPointer { inputBuffer in
            output.withUnsafeMutableBufferPointer { outputBuffer in
                BtbProfileCanonical(inputBuffer.baseAddress, inputBuffer.count,
                                    outputBuffer.baseAddress)
            }
        }
        guard accepted == 1 else { return nil }
        // C publishes terminated ASCII only on success. Copy into a Swift value
        // after the borrow ends; no pointer escapes either closure.
        let canonicalBytes = output.prefix(while: { $0 != 0 }).map { UInt8(truncatingIfNeeded: $0) }
        return String(decoding: canonicalBytes, as: UTF8.self)
    }
}
