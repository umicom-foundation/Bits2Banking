(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/progress_checks.pas
 *
 * PURPOSE:
 *   Check record preservation, independent state and arithmetic limits.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

program ProgressChecks;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
uses LessonProgress;

procedure Require(Condition: Boolean; const Description: String);
begin
  if not Condition then
  begin
    WriteLn(StdErr, 'FAIL: ', Description);
    Halt(1);
  end;
end;

var
  First, Second, Before: TLessonProgress;
begin
  Require(TryCreateProgress(3, 1, First), 'create first');
  Require(TryCreateProgress(5, 2, Second), 'create second');
  Require(TryCompleteLesson(First), 'advance first');
  Require(First.Completed = 2, 'first count');
  Require(Second.Completed = 2, 'independent second count');

  Before := First;
  Require(not TryCreateProgress(-1, 0, First), 'reject negative total');
  Require((First.Total = Before.Total) and
          (First.Completed = Before.Completed), 'creation preserves fields');
  Require(not TryCreateProgress(3, -1, First), 'reject negative completed');
  Require(not TryCreateProgress(3, 4, First), 'reject completed above total');
  Require((First.Total = Before.Total) and
          (First.Completed = Before.Completed), 'all rejected creations preserve fields');

  Require(TryCreateProgress(0, 0, First), 'empty course');
  Require(not TryCompleteLesson(First), 'empty course cannot advance');
  Require(First.Completed = 0, 'empty count preserved');
  Require(TryCreateProgress(High(Integer), High(Integer) - 1, First), 'large course');
  Require(TryCompleteLesson(First), 'last representable increment');
  Require(First.Completed = High(Integer), 'upper count');
  Require(not TryCompleteLesson(First), 'full course cannot advance');

  (* Records are publicly writable in this teaching unit. Check invalid state
     at each operation rather than relying only on the creation function. *)
  First.Total := 2;
  First.Completed := 3;
  Require(not TryCompleteLesson(First), 'reject damaged state');
  Require((First.Total = 2) and (First.Completed = 3), 'damaged state preserved');
  Require(RemainingLessons(Low(Integer), 0) = -1, 'smallest total rejected');
  WriteLn('Progress record checks passed');
end.

