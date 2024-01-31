program ROOTUKAZ(INPUT, OUTPUT);
{Общими требованиями к лабораторной работе являются:
   1) вводить   исходное   дерево  из  файла  в  понятной  для
пользователя форме, а не с клавиатуры;
   2) по требованию прользователя показывать дерево на экране;
   3) обрабатывать  дерево  в  оперативной памяти,  а не путем
многократного обращения к файлу;
   4) обеспечить   возможность   многократных   запросов   без
повторного запуска программы.
№15
Задано бинарное  дерево.  Построить  прошитое   дерево,
соответствующее обходу сверху вниз. Составить программу удале-
ния поддерева с  корнем  в  заданной  вершине  без  повторного
построения дерева. Конечное дерево должно оставаться прошитым. 
Выдать информацию о нитях исходного и конечного деревьев (12).
КОНСТАНТИНОВ ВАЛЕНТИН ИГОРЕВИЧ ИПС-2023}
TYPE
  ukaz=^uzel;
  uzel=RECORD
    name: STRING;
    left, right: ukaz;
    fath: ukaz;
    urov: INTEGER;
    rightNitFlag: BOOLEAN;
  END;
VAR
  root: ukaz;
  FIn, FOut: TEXT;
  komanda: CHAR;

Procedure FromFile(var F: text; var ro: ukaz);
Var
  i, m, k, Len: integer;
  R, S: string;   {для формирования строки выдачи}
  p, t, kon: ukaz;
Begin
  While not Eof(F) do
    begin
      ReadLn(F, S);
      k := 0;
      Len := Length(S);
      While S[k+1] = '.' do k := k+1;  
      {k - уровень вершины, начиная с 0}
      R := Copy(S, k+1, Len-k);         
      {имя вершины без точек}
      New(kon);
      kon^.name := R;
      kon^.left := nil;
      kon^.right := nil;
      kon^.urov := k;
      kon^.rightNitFlag := FALSE;
      if k = 0 then             {нулевой уровень - корень}
        begin
          ro := kon;       {корень - для возврата в вызывающую}
          kon^.fath := nil;
          m := 0;            {уровень предыдущей вершины}
          t := kon;          {указатель на предыдущую вершину }
         continue;
        end;
      if k > m then       {переход на следующий уровень}
        begin
          t^.left := kon;
          kon^.fath := t;
        end
      else                    { k<>0 и k<=m }
        if k = m 
          then     { уровень, как у предыдущей}
            begin
              t^.right := kon;
              t^.rightNitFlag := TRUE;
              t := t^.fath; {меняем брата на отца}
              t^.right := kon;
              kon^.fath := t;         {отец тот же, что у брата}
            end
          else                  { k < m - подъем по дереву на m-k уровней }
            begin
              p := t;
              For i := 1 to m-k do
                p := p^.fath;
                { p-предыдущая вершина того же уровня }
              kon^.fath := p^.fath; 
                  { отец в исходном дереве тот же, что у брата }
              //p^.right := kon;
              t^.right := kon;
              t^.rightNitFlag := TRUE;
            end;
      m := k;        { запомнили текущий уровень }
      t := kon;      {для работы со следующей вершиной}
    end;              {конец While}
    WRITELN('Дерево создано')
End;

Procedure ToFile(var F: text; t: ukaz);
{ выдача в файл в порядке сверху вниз }
Var
  j: integer;
  St: string;   { для формирования строки выдачи }
  p: ukaz;
Begin
  While t <> nil do
    Begin
      St := t^.name;   { имя без точек }
      p := t;
      FOR j := 1 TO t^.urov DO  { отступ в зависимости от уровня }
        BEGIN
        //  p := p^.fath;
          St := '.' + St;
        END;
      WRITELN(F, St);
      WRITELN(St);
      IF t^.left <> nil THEN
      t := t^.left
      ELSE 
        t := t^.right;
     // ToFile(F, t^.left);
     // ToFile(F, t^.right);
    END
END;

PROCEDURE NitiInf(t: ukaz);
{ вывод нитей}
BEGIN
  WHILE t <> nil DO
    BEGIN
      IF t^.rightNitFlag AND (t^.right <> nil)
      THEN
        WRITELN(t^.name, ' --> ', t^.right^.name);
      IF t^.left <> nil THEN
      t := t^.left
      ELSE 
        t := t^.right;
    END
END;

PROCEDURE DelElements(t: ukaz);
VAR
  DelElement: String;
  j: integer;
  St: string;   
  p, d, r: ukaz;
  exitUnderTheTree: BOOLEAN;
BEGIN
  WRITELN('какое поддерево удалить? ');
  READ(DelElement);
  IF t^.name = DelElement THEN
    BEGIN
      WRITELN('вы удалили все дерево');
      root := NIL
    END
  ELSE
    BEGIN
      r := t;
      WHILE t <> nil DO
        BEGIN
          p := t;
          IF DelElement = t^.name
          THEN
            BEGIN
              IF p^.fath^.left = t THEN p^.fath^.left := NIL;
              IF p^.fath^.right = t THEN p^.fath^.right := NIL;
              
              exitUnderTheTree := FALSE;
              WHILE NOT exitUnderTheTree DO
                BEGIN
                  IF p^.left <> nil THEN
                  p := p^.left
                  ELSE IF p^.right <> nil 
                  THEN
                    IF p^.right^.urov <= t^.urov
                    THEN
                      exitUnderTheTree := TRUE
                    ELSE
                      p := p^.right
                  ELSE exitUnderTheTree := TRUE
                END;
              r^.right := p^.right;
              r^.rightNitFlag := TRUE;
              t := p^.right;
              
            END
          ELSE
            BEGIN
              r := t;
              IF t^.left <> nil THEN t := t^.left
              ELSE t := t^.right
            END
        END
    END;
    WRITELN('поддерево ', DelElement, ' удалено')
END;

BEGIN
    ASSIGN(FIn, 'IN.TXT');
    ASSIGN(FOut,'Out.TXT');

    root:= NIL;    
    WRITELN('МЕНЮ:');
    WRITELN('Нажмите 1 чтобы ввести новое дерево из файла');
    WRITELN('Нажмите 2 чтобы удалить поддерево');
    WRITELN('Нажмите 3 чтобы вывести дерево на экран');
    WRITELN('Нажмите 4 чтобы показать нити');
    WRITELN('Нажмите 5 чтобы закончить работу');
    WHILE komanda <> '5' DO
      BEGIN
        READLN(komanda);
        IF komanda = '1' THEN 
          BEGIN
            RESET(FIn);
            FromFile(FIn, root)
          END;
        IF komanda = '2' THEN
           DelElements(root);
        IF komanda = '3' THEN 
        BEGIN    
          REWRITE(FOut);
          ToFile(FOut, root);
          CLOSE(FOut)
        END;
        IF komanda = '4' THEN
          NitiInf(root);
      END;
END.