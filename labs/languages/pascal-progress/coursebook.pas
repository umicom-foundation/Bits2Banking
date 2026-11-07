(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/coursebook.pas
 *
 * PURPOSE:
 *   Compose checked progress records into a bounded course list for Pascal learners.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

unit CourseBook;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
interface
uses LessonProgress;
const
  CourseCapacity = 8;
  CourseNameLimit = 40;
type
  TCourseEntry = record
    Name: String[CourseNameLimit];
    Progress: TLessonProgress;
  end;
  TCourseBook = record
    Count: Integer;
    Entries: array[0..CourseCapacity - 1] of TCourseEntry;
  end;
procedure InitialiseBook(var Book: TCourseBook);
function TryAddCourse(var Book: TCourseBook; const Name: String;
  Total: Integer; var CourseNumber: Integer): Boolean;
function TryCompleteCourseLesson(var Book: TCourseBook; CourseNumber: Integer): Boolean;
function TryReadRemaining(const Book: TCourseBook; CourseNumber: Integer;
  var Remaining: Integer): Boolean;
implementation

procedure InitialiseBook(var Book: TCourseBook);
var I: Integer;
begin
  Book.Count := 0;
  for I := Low(Book.Entries) to High(Book.Entries) do
  begin
    Book.Entries[I].Name := '';
    Book.Entries[I].Progress.Total := 0;
    Book.Entries[I].Progress.Completed := 0;
  end;
end;

function ValidName(const Name: String): Boolean;
var I: Integer; HasVisibleCharacter: Boolean;
begin
  Result := False;
  if (Length(Name) = 0) or (Length(Name) > CourseNameLimit) then Exit;
  HasVisibleCharacter := False;
  for I := 1 to Length(Name) do
  begin
    if (Ord(Name[I]) < 32) or (Ord(Name[I]) > 126) then Exit;
    if Name[I] <> ' ' then HasVisibleCharacter := True;
  end;
  Result := HasVisibleCharacter;
end;

function TryAddCourse(var Book: TCourseBook; const Name: String;
  Total: Integer; var CourseNumber: Integer): Boolean;
var I: Integer; Candidate: TLessonProgress;
begin
  Result := False;
  if (Book.Count < 0) or (Book.Count >= CourseCapacity) then Exit;
  if not ValidName(Name) then Exit;
  for I := 0 to Book.Count - 1 do
    if Book.Entries[I].Name = Name then Exit;
  if not TryCreateProgress(Total, 0, Candidate) then Exit;
  (* Reuse the progress unit's arithmetic contract. All refusal paths run
     before publication, so both the book and returned number are retained. *)
  Book.Entries[Book.Count].Name := Name;
  Book.Entries[Book.Count].Progress := Candidate;
  Inc(Book.Count);
  CourseNumber := Book.Count;
  Result := True;
end;

function TryCompleteCourseLesson(var Book: TCourseBook; CourseNumber: Integer): Boolean;
begin
  Result := False;
  if (Book.Count < 0) or (Book.Count > CourseCapacity) then Exit;
  if (CourseNumber < 1) or (CourseNumber > Book.Count) then Exit;
  Result := TryCompleteLesson(Book.Entries[CourseNumber - 1].Progress);
end;

function TryReadRemaining(const Book: TCourseBook; CourseNumber: Integer;
  var Remaining: Integer): Boolean;
var Candidate: Integer;
begin
  Result := False;
  if (Book.Count < 0) or (Book.Count > CourseCapacity) then Exit;
  if (CourseNumber < 1) or (CourseNumber > Book.Count) then Exit;
  Candidate := RemainingLessons(Book.Entries[CourseNumber - 1].Progress.Total,
    Book.Entries[CourseNumber - 1].Progress.Completed);
  if Candidate < 0 then Exit;
  Remaining := Candidate;
  Result := True;
end;
end.
