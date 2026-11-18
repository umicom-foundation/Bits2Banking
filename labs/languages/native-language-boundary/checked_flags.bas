'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/checked_flags.bas
'
' PURPOSE:
'   Demonstrate bounded option masks and unchanged output when unknown bits are refused.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------
Const As ULong ReadOption = 1
Const As ULong WriteOption = 2
Const As ULong AuditOption = 4
Const As ULong KnownOptions = ReadOption Or WriteOption Or AuditOption

Function HasAll(ByVal flags As ULong, ByVal required As ULong) As Boolean
    Return (flags And required) = required
End Function

Function TrySetOptions(ByVal current As ULong, ByVal requested As ULong, _
                       ByVal enabled As Boolean, ByRef result As ULong) As Boolean
    ' Validate both inputs before publishing a replacement value.
    If ((current Or requested) And Not KnownOptions) <> 0 Then Return False
    Dim candidate As ULong
    If enabled Then
        candidate = current Or requested
    Else
        candidate = current And Not requested
    End If
    result = candidate
    Return True
End Function

Sub Require(ByVal condition As Boolean, ByVal message As String)
    If Not condition Then
        Print message
        End 1
    End If
End Sub

Dim As ULong options = ReadOption
Require(TrySetOptions(options, AuditOption, True, options), "Enable refused")
Require(options = 5, "Expected read plus audit")
Require(HasAll(options, ReadOption Or AuditOption), "Missing option")
Require(Not HasAll(options, WriteOption), "Write unexpectedly enabled")
Print "Read plus audit: "; Bin(options, 3)

Require(TrySetOptions(options, ReadOption, False, options), "Disable refused")
Require(options = AuditOption, "Expected only audit")
Print "Only audit: "; Bin(options, 3)

' Bits outside the declared contract are errors, not ignored extensions.
Dim As ULong sentinel = 123
Require(Not TrySetOptions(options, 8, True, sentinel), "Unknown request accepted")
Require(sentinel = 123, "Failed request changed output")
Require(Not TrySetOptions(8, ReadOption, True, sentinel), "Unknown current bit accepted")
Require(sentinel = 123, "Invalid state changed output")
Require(TrySetOptions(options, 0, True, sentinel), "Empty change refused")
Require(sentinel = options, "Empty change changed bits")
Require(HasAll(options, 0), "Empty requirement must be explained as vacuously true")

' Toggling is a different operation from enabling or disabling.
Dim As ULong toggled = options Xor AuditOption
Require(toggled = 0, "Toggle did not clear the set bit")
Require((toggled Xor AuditOption) = options, "Second toggle did not restore it")
Print "Checked flag examples passed"
