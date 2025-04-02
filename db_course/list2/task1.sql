DROP FUNCTION IF EXISTS GetReaders;
GO

CREATE FUNCTION GetReaders(@Days INT)
RETURNS TABLE
AS
RETURN
(
    SELECT
        C.PESEL,
        COUNT(W.Egzemplarz_ID) AS Specimens
    FROM Czytelnik C
    JOIN Wypozyczenie W ON C.Czytelnik_ID = W.Czytelnik_ID
    WHERE DATEDIFF(day, W.Data, GETDATE()) >= @Days
	GROUP BY C.PESEL
);
GO

SELECT * FROM GetReaders(23);
