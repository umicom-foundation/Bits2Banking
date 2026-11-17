# Umicom Bits2Banking
# File: labs/languages/nim-activity/main.nim
# 
# PURPOSE:
# Keep the counting rule in C and expose it through a C-sized Nim interface.
# 
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
# 
# LICENCE:
# MIT
# 
proc activityNext(current: cint): cint {.importc: "BtbActivityNext", cdecl.}
let inputs = [-1.cint, 0.cint, 41.cint, 999.cint, 1000.cint]
let expected = [-1.cint, 1.cint, 42.cint, 1000.cint, -1.cint]
for index, current in inputs:
  let next = activityNext(current)
  # No Nim string, sequence or garbage-collected address crosses this boundary.
  if next != expected[index]:
    quit("C bridge returned an unexpected value", 1)
  echo current, " -> ", next
