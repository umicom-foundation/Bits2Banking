(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/lessonprogress.pas
 *
 * PURPOSE:
 *   Share checked progress values and record operations between Pascal exercises.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

unit LessonProgress;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}

interface

type
  TLessonProgress = record
    Total: Integer;
    Completed: Integer;
  end;

function RemainingLessons(Total, Done: Integer): Integer;
function TryCreateProgress(Total, Done: Integer; var State: TLessonProgress): Boolean;
function TryCompleteLesson(var State: TLessonProgress): Boolean;

implementation

(* The original arithmetic contract is shared by terminal and record callers.
   A negative result means invalid inputs; zero is a valid completed course. *)
function RemainingLessons(Total, Done: Integer): Integer;
begin
  if (Total < 0) or (Done < 0) or (Done > Total) then
    RemainingLessons := -1
  else
    RemainingLessons := Total - Done;
end;

function TryCreateProgress(Total, Done: Integer; var State: TLessonProgress): Boolean;
begin
  Result := False;
  if RemainingLessons(Total, Done) < 0 then
    Exit;
  (* Publish both fields only after all checks succeed. A rejected creation
     preserves the caller's previous record. *)
  State.Total := Total;
  State.Completed := Done;
  Result := True;
end;

function TryCompleteLesson(var State: TLessonProgress): Boolean;
begin
  Result := False;
  if RemainingLessons(State.Total, State.Completed) <= 0 then
    Exit;
  (* A valid remaining count proves Completed < Total <= High(Integer),
     so the increment cannot exceed the representation's upper limit. *)
  Inc(State.Completed);
  Result := True;
end;

end.

