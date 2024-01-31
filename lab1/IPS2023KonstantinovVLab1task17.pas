PROGRAM Raspisanie(INPUT, OUTPUT);
{ 17. На   узловой   станции  необходимо  менять  направления
движения всех  поездов.  Для  этого  предназначен  специальный
тупик.  Зашедший  в  тупик  последний  поезд  выходит  из него
первым.  Известны  моменты  прихода   поездов   и   минимально
необходимое   время   стоянки (одинаковое  для всех  поездов).
Требуется:
   1) составить расписание стоянки поездов на станции с учетом
смены направления движения;
   2) поменять   между   собой   моменты   прихода   скорых  и
пассажирских  поездов   так,   чтобы   скорые   поезда   имели
минимальное суммарное время простоя в тупике (9)
КОНСТАНТИНОВ ВАЛЕНТИН ИГОРЕВИЧ 
}
TYPE
  TrainData = ^TrainLine;
  TData = RECORD
            TrainNumber: INTEGER;
            TrainType: CHAR;
            InTime: INTEGER;
            OutTime: INTEGER;
            StopTime: INTEGER;
          END;
  TrainLine = RECORD
                Data: TData;
                Next: TrainData;
              END;
VAR
  Head, Pointer: TrainData; 
  InF: Text;
  OutF: Text;
  H, M, TempInTime, TempOutTime, Stop: INTEGER;
  Ch: CHAR;

PROCEDURE Print(Pointer: TrainData);
BEGIN
  WRITE(Pointer^.Data.TrainNumber, ' ');
  WRITE(Pointer^.Data.TrainType, ' ');
  H := Pointer^.Data.InTime DIV 60;
  M := Pointer^.Data.InTime MOD 60;
  IF H < 10
  THEN
    WRITE('0');    
  WRITE(H, ':');
  IF M < 10
  THEN
    WRITE('0');
  WRITE(M, ' ');
  H := Pointer^.Data.OutTime DIV 60;
  M := Pointer^.Data.OutTime MOD 60;
  IF H < 10
  THEN
    WRITE('0');
  WRITE(H, ':');
  IF M < 10
  THEN
    WRITE('0');
  WRITE(M, ' ');
  WRITELN(Pointer^.Data.StopTime);
END;
  
PROCEDURE SortBublStop(Nach:TrainData);
VAR
  Tmp,Tmps,Rab: TrainData;
  Sort: BOOLEAN;
BEGIN
  NEW(Tmp);
  NEW(Tmps);
  NEW(Rab);
  Sort := FALSE;
  WHILE NOT Sort DO
  BEGIN
    Rab := Nach;
    Sort := TRUE;
    WHILE (Rab <> NIL) DO
    BEGIN
      Tmp:=Rab^.Next;
      WHILE Tmp<>NIL DO
      BEGIN
        {WRITELN('Проверка');
        Print(Tmp);
        Print(Rab);}
        IF ((Tmp^.Data.StopTime < Rab^.Data.StopTime) AND (Rab^.Data.TrainType = 'C') AND (Tmp^.Data.TrainType <> 'C')) OR ((Tmp^.Data.StopTime > Rab^.Data.StopTime) AND (Tmp^.Data.TrainType = 'C') AND (Rab^.Data.TrainType <> 'C')) THEN
        BEGIN
          {WRITELN('Обмен');
          Print(Tmp);
          Print(Rab);}
          Tmps^.Data.TrainNumber:=Tmp^.Data.TrainNumber;
          Tmp^.Data.TrainNumber:=Rab^.Data.TrainNumber;
          Rab^.Data.TrainNumber:=Tmps^.Data.TrainNumber;
          Tmps^.Data.TrainType:=Tmp^.Data.TrainType;
          Tmp^.Data.TrainType:=Rab^.Data.TrainType;
          Rab^.Data.TrainType:=Tmps^.Data.TrainType;
          Sort := FALSE;
        END;
        Tmp:=Tmp^.Next
      END;
      Rab:=Rab^.Next
    END
  END
END;
 
PROCEDURE OutRaspisanie(Pointer: TrainData); {выводим список}
BEGIN
  Pointer := Pointer^.Next; 
  IF Pointer^.Next <> NIL THEN
  OutRaspisanie(Pointer);
  Print(Pointer);
END;
  
BEGIN
  WRITE('введите время стоянки ');
  READ(Stop);
  TempInTime := 1500;
  ASSIGN(InF, 'IN.TXT');
  RESET(InF);
  Head := NIL;
  WHILE NOT EOF(InF) DO {Формируем список}
    BEGIN
      New(Pointer);
      READ(InF, Pointer^.Data.TrainNumber);
      READ(InF, Ch);
      READ(InF, Pointer^.Data.TrainType);
      READ(InF, Ch);
      READ(InF, H);
      READ(InF, Ch);
      READ(InF, M);
      Pointer^.Data.InTime := H * 60 + M;
      Pointer^.Data.OutTime := 0;
      Pointer^.Data.StopTime := Stop; 
      READLN(InF);
      Pointer^.Next := Head;
      Head := Pointer
    END;
    
  Pointer := Head; {считаем время выезда и простоя в тупике}
  WHILE Pointer <> NIL
  DO
    BEGIN
      
      IF TempInTime > (Pointer^.Data.InTime + Stop)
      THEN
        begin
        TempInTime := Pointer^.Data.InTime;
        Pointer^.Data.OutTime := Pointer^.Data.InTime + Stop;
        TempOutTime := Pointer^.Data.OutTime
        end
      ELSE
        Begin
          Pointer^.Data.OutTime := TempOutTime;
          TempInTime := Pointer^.Data.InTime
        END;
  
      Pointer^.Data.StopTime := Pointer^.Data.OutTime - Pointer^.Data.InTime;
      Pointer := Pointer^.Next;
    END;
    
  SortBublStop(Head);
  
  Pointer := Head;
  OutRaspisanie(Pointer); 
  Print(Head);

END.
