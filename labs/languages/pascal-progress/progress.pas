(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/progress.pas
 *
 * PURPOSE:
 *   Validate a lesson count and display an ordered progress list.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)
program Progress;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
uses LessonProgress;
var
  Completed, Remaining, Item: Integer;
  Code: Integer;

(* The original local implementation is retained for comparison. LessonProgress
   now supplies this operation to the terminal and record examples, keeping
   one active arithmetic contract while preserving the earlier lesson source.
function RemainingLessons(Total, Done: Integer): Integer;
begin
  if (Total < 0) or (Done < 0) or (Done > Total) then
    RemainingLessons := -1
  else
    RemainingLessons := Total - Done;
end;
*)

begin
  if ParamCount <> 1 then
  begin
    WriteLn('Usage: progress COMPLETED (0 to 5)');
    Halt(1);
  end;
  Val(ParamStr(1), Completed, Code);
  (* Val leaves its output undefined on failure. Do not inspect Completed
     until Code is zero; this separates conversion from domain validation. *)
  if Code <> 0 then
  begin
    WriteLn('Enter a whole number.');
    Halt(1);
  end;
  Remaining := RemainingLessons(5, Completed);
  if Remaining < 0 then
  begin
    WriteLn('Completed must be from 0 to 5.');
    Halt(1);
  end;
  WriteLn('Remaining: ', Remaining);
  for Item := 1 to Remaining do
    WriteLn('Practice item ', Item);
end.
